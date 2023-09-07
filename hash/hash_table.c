#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Data {
    char *str;
    struct Data *next;
} Data;

typedef struct HashTable {
    Data *data;
    int size;
    int cnt;
    int (*hash_func)(const char *);
} HashTable;

int APHash(const char *str) {
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        if (i & 1) {
            hash ^= (hash << 7) ^ str[i] ^ (hash >> 3);
        } else {
            hash ^= (~((hash << 11) ^ str[i] ^ (hash >> 5)));
        }
    }
    return hash & 0x7fffffff;
}

int BKDRHash(const char *str) {
    int hash = 0, seed = 131;
    for (int i = 0; str[i]; i++) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7fffffff;
}

int zobrist_table[50][256] = {0};

void init_zobrist_table() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 256; j++) {
            zobrist_table[i][j] = rand();
        }
    }
    return ;
}

int ZobristHash(const char *str) {
    static int flag = 1;
    if (flag) {
        flag = 0;
        init_zobrist_table();
    }
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        hash ^= zobrist_table[i][str[i]];
    }
    return hash & 0x7fffffff;
}

int MyHash(const char *str) {
    int hash = 1;
    for (int i = 0; str[i]; i++) {
        hash *= str[i];
    }
    return hash & 0x7fffffff;
}

HashTable *init(int size, int (*func)(const char *)) {
    HashTable *p = (HashTable *)malloc(sizeof(HashTable));
    p->data = (Data *)calloc(sizeof(Data), size);
    p->size = size;
    p->hash_func = func;
    p->cnt = 0;
    return p;
}

void clear(HashTable *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

int query(HashTable *h, const char *str) {
    int ind = h->hash_func(str) % h->size;
    Data *p = h->data[ind].next; 
    while (p) {
        if (strcmp(p->str, str) == 0) return -1;
        p = p->next;
        h->cnt += 1;
    }
    return ind;
}

void insert(HashTable *h, const char *str) {
    int ind = query(h, str);
    if (ind == -1) return ; 
    Data *data = (Data *)malloc(sizeof(Data));
    data->str = strdup(str);
    data->next = h->data[ind].next;
    h->data[ind].next = data;
    return ;
}

int main() {
    #define HASH_TABLE_SIZE 100000
    HashTable *apHashTable = init(HASH_TABLE_SIZE, APHash);
    HashTable *bkdrHashTable = init(HASH_TABLE_SIZE, BKDRHash);
    HashTable *zobristHashTable = init(HASH_TABLE_SIZE, ZobristHash);
    HashTable *myHashTable = init(HASH_TABLE_SIZE, MyHash);
    #define MAX_TEST_CNT 100000
    for (int i = 0; i < MAX_TEST_CNT; i++) {
        char str[7] = {0};
        for (int j = 0; j < 6; j++) {
            str[j] = rand() % 26 + 'a';
        }
        str[6] = 0;
        insert(apHashTable, str);
        insert(bkdrHashTable, str);
        insert(zobristHashTable, str);
        insert(myHashTable, str);
    }
    printf("APHash(%d) = %d\n", MAX_TEST_CNT, apHashTable->cnt);
    printf("BKDRHash(%d) = %d\n", MAX_TEST_CNT, bkdrHashTable->cnt);
    printf("ZobristHash(%d) = %d\n", MAX_TEST_CNT, zobristHashTable->cnt);
    printf("MyHash(%d) = %d\n", MAX_TEST_CNT, myHashTable->cnt);
    #undef MAX_TEST_CNT
    #undef HASH_TABLE_SIZE
    return 0;
}
