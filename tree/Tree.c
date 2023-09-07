#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define f(a) ((int)log2(a + 1))

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

Node *init(char data) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

void clear(Node *p) {
    if (!p) return ;
    if (p->lchild) clear(p->lchild);
    if (p->rchild) clear(p->rchild);
    free(p);
}

void output(Node *p) {
    if (!p) return ;
    printf("%c ", p->data);
    if (p->lchild == NULL && p->rchild == NULL) return ;
    printf("(");
    if (p->lchild != NULL) {
        output(p->lchild);
    }
    if (p->rchild != NULL) {
        printf(",");
        output(p->rchild);
    }
    printf(")");
}

int main() {
    char buff;
    char str[1000];
    int n = 0;
    while (scanf("%c ", &buff)) {
		if (buff == '$') break;
    	str[n++] = buff;
    }
    
    Node **node = (Node **)malloc(sizeof(Node *) * (n / 2 + 1));
    node[1] = init(str[0]);
	for (int i = 2; i < n; i++) {
        node[i] = init(str[i - 1]);
        if (i % 2) {
            //node[i / 2]->rchild = node[i];
            printf("%d ", i / 2);
        }
        else {
            //node[i / 2]->lchild = node[i];
            printf("%d ", i / 2);
        }
    }
    output(node);
    clear(node);
    free(str);
    return 0;
}