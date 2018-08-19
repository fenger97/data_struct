#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BASE 30

const int MAX_LEN = 1000000;

typedef struct BitData {
	int *data;
	int cnt;
} BitData;

BitData *init(int n) {
	BitData *p = (BitData *)malloc(sizeof(BitData));
	p->data = (int *)calloc(sizeof(int), n / BASE + 1);
	p->cnt = n / BASE + 1;
	return p;
}

void clear(BitData *d) {
	if (d == NULL) return ;
	free(d->data);
	free(d);
}

void operator_or(BitData *d, int n) {
	int x = n / BASE;
	int y = n % BASE;
	d->data[x] |= (1 << y);
	return ;
}

void operator_and(BitData *d1, BitData *d2) {
	int len = d1->cnt < d2->cnt ? d1->cnt : d2->cnt;
	for (int i = 0; i < len; ++i) {
		d1->data[i] &= d2->data[i];
	}
	for (int i = len; i < d1->cnt; ++i) {
		d1->data[i] = 0;
	}
	return ;
}

int operator_get(BitData *d, int n) {
	int x = n / BASE;
	int y = n % BASE;
	return d->data[x]& (1 << y);
}

// int operator_left(BitData *d, int n) {
// 	int x_cnt = n / BASE;
// 	int y_cnt = n % BASE;
// }

int operator_left(BitData *d) {
	for (int i = d->cnt - 1; i >= 0; --i) {
    	if (i != d->cnt - 1) {
    		d->data[i + 1] |= d->data[i] >> (BASE - 1);
    	}
    	d->data[i] <<= 1;
	}
	return 0;
}

int shift_and(char *text, char *pattern) {
	BitData *d[127] = {0};
	int n = strlen(pattern);
	for (int i = 0; i < 127; ++i) {
		d[i] = init(n);
	}
	for (int i = 0; i < n; ++i) {
		operator_or(d[pattern[i]], i);
	}
	BitData *p = init(n);
	for (int i = 0; text[i]; ++i) {
		operator_left(p);
		operator_or(p, 0);
		operator_and(p, d[text[i]]);
		if (operator_get(p, n - 1)) return 1;
	}
	clear(p);
	return 0;
}

// int shift_and(char *text, char *pattern) {
// 	int len = strlen(pattern);
// 	int *p = (int *)calloc(sizeof(int), len); 
// 	int **d;

// 	d = (int **)calloc(sizeof(int*), 127); 
// 	for (int i = 0; i < 127; ++i) d[i]=(int *)calloc(sizeof(int), len); 
// 	for (int i = 0; pattern[i]; ++i) d[pattern[i]][i] = 1;

//  	for (int i = 0; text[i]; ++i) { 
// 		for (int j = len - 1; j >= 0; --j) p[j + 1] = p[j] & d[text[i]][j + 1];
// 		if (p[len - 1] == 1) return 1;
// 	}

// 	return 0;
// }

int main() {
	char text[MAX_LEN], pattern[MAX_LEN];
	scanf("%s%s", text, pattern);
	printf("%s = %d\n", pattern, shift_and(text, pattern));

	return 0;
}