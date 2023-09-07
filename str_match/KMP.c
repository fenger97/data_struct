#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int KMP(const char *text, const char *pattern) {
	int len1 = strlen(text);
	int len2 = strlen(pattern);
	int *next = (int *)malloc(sizeof(int) * len2);
	int j = -1;
	next[0] = -1;
	for (int i = 1; i < len2; ++i) {
		while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
		if (pattern[j + 1] == pattern[j]) ++j;
		next[i] = j;
	}
	j = -1;
	for (int i = 0; text[i]; ++i) {
		while (j != -1 && pattern[j + 1] != text[i]) j = next[j];
		if (pattern[j + 1] == text[i]) ++j;
		if (pattern[j + 1] == 0) return 1;
	}
	return 0;
}

int main() {
	char str1[] = "hello world";
	printf("KMP(%s, %s) = %d\n", str1, "wor", KMP(str1, "wor"));

	return 0;
}