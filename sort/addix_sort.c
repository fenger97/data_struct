#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define lowbit(x) (x & 0xffff)
#define hightbit(x) ((x >> 16) & 0xffff) 

#define TEST(n, func) { \
	int num[n] = {0}; \
	for (int i = 0; i < n; i++) { \
		num[i] = rand() % 100; \
	} \
	func; \
	output(num, n); \
}

void raddix_sort(int *num, int n);
void output(int *, int);

int main() {
	TEST(20, );
	return 0;
}

void output(int *num, int n) {
	printf("[");
	for (int i = 0; i < n; i++) {
		printf(" %d", num[i]);
	}
	printf("]\n");
	return ;
}

void raddix_sort(int *num, int n) {
	#define MAX_N 655546
	int *temp = (int *)malloc(sizeof(int) * n);
	int cnt[MAX_N] = {0};

	for (int i = 0; i < n; i++) cnt[lowbit(num[i])]++;
	for (int i = 1; i < MAX_N; i++) cnt[i] += cnt[i - 1];
	for (int i = n -1; i >= 0; i--) temp[--cnt[lowbit(num[i])]] = num[i];
	//output(cnt, 100);
		
	memeset(cnt, 0, sizeof(MAX_N * (int)));
	for (int i = 0; i < n; i++) cnt[hightbit(temp[i])]++;
	for (int i = 1; i < MAX_N; i++) cnt[i] += cnt[i - 1];
	for (int i = n -1; i >= 0; i--) num[--cnt[hightbit(temp[i])]] = temp[i];             
	free(temp);
	#undef MAX_N
}