#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #define swap(a, b) { \
// 	__typeof(a) temp;\
// 	temp = (a); \
// 	(a) = (b); \
// 	(b) = temp; \
// }
#define TEST(n, func) { \
	int num[n] = {0}; \
	for (int i = 0; i < n; i++) { \
		num[i] = rand() % 100; \
	} \
	func; \
	output(num, n); \
}
void swap (int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void select_sort(int *, int);
void quick_sort(int *, int, int);
void output(int *, int);
void ungarded_insert_sort(int *, int);

int main() {
	srand(time(0));
	TEST(20, select_sort(num, 20));
	TEST(20, quick_sort(num, 0, 19));
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

void ungarded_insert_sort(int *num, int n) {
	int ind = 0;
	for (int i = 1; i < n; i++) {
		if (num[i] < num[ind]) ind = i;
	}
	swap(&num[ind], &num[0]);
	for (int i = 2; i < n; i++) {
		int j = i;
		while (num[j] < num[j - 1]) {
			swap(&num[j], &num[j - 1]);
			j--;
		}
	}
	return ;
}

void quick_sort(int * num, int l, int r) {
	while (r - l >= 2) {
		int x = l, y = r, z = num[rand() % (r - l + 1) + l];//随机找基准值
		do {
			while (num[x] < z) ++x;
			while (num[y] > z) --y;
			if (x <= y) {
				swap(&num[x], &num[y]);
				++x, --y;
			}
		} while (x <= y);
		quick_sort(num, l, y);
		l = x;
	}
	ungarded_insert_sort(num + l, r - l + 1);//非监督的插入排序
	return ;
}

// void quick_sort(int * num, int l, int r) {
// 	while (r - l >= 2) {
// 		int x = l, y = r, z = rand() % (r - l + 1) + l;//随机找基准值
// 		swap(num[z], num[l]);
// 		z = num[l];
// 		while (x < y) {
// 			while (x < y && num[y] >= z) --y;
// 			if (x < y) num[x++] = num[y];
// 			while (x < y && num[x] <= z) ++x;
// 			if (x < y) num[y--] = num[x];
// 		}
// 		num[x] = z;
// 		quick_sort(num, l, x - 1);
// 		l = x + 1;
// 	}
// 	ungarded_insert_sort(num + l, r - l + 1);//非监督的插入排序
// 	return ;
// }

// void quick_sort(int * num, int l, int r) {
// 	while (r - l >= 16) {
// 		int x = l, y = r, z = num[l];
// 		while (x < y) {
// 			while (x < y && num[y] >= z) --y;
// 			if (x < y) num[x++] = num[y];
// 			while (x < y && num[x] <= z) ++x;
// 			if (x < y) num[y--] = num[x];
// 		}
// 		num[x] = z;
// 		quick_sort(num, l, x - 1);
// 		l = x + 1;
// 	}
// 	ungarded_insert_sort(num + l, r - l + 1);//非监督的插入排序
// 	return ;
// }

// void quick_sort(int * num, int l, int r) {
// 	while (r - l >= 1) {
// 		int x = l, y = r, z = num[l];
// 		while (x < y) {
// 			while (x < y && num[y] >= z) --y;
// 			if (x < y) num[x++] = num[y];
// 			while (x < y && num[x] <= z) ++x;
// 			if (x < y) num[y--] = num[x];
// 		}
// 		num[x] = z;
// 		quick_sort(num, l, x - 1);
// 		l = x + 1;
// 	}
// 	return ;
// }

void select_sort(int *num, int n) {
	for (int i = 0; i < n- 1; i++) {
		int ind = i;
		for (int j = i + 1; j < n; j++) {
			if (num[j] < num[ind]) ind = j;
		}
		swap(&num[i], &num[ind]);
	}
	return ;
}

// void quick_sort(int * num, int l, int r) {
// 	if (r - l < 1) return ;
// 	int x = l, y = r, z = num[l];
// 	while (x < y) {
// 		while (x < y && num[y] >= z) --y;
// 		if (x < y) num[x++] = num[y];
// 		while (x < y && num[x] <= z) ++x;
// 		if (x < y) num[y--] = num[x];
// 	}
// 	num[x] = z;
// 	quick_sort(num, l, x - 1);
// 	quick_sort(num, x + 1, r);
// 	return ;
// }