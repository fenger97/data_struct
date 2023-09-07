#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define data_type int
#define NULL_VALUE 0
#define f(a) ((int)log10(a) + 1)

typedef struct Stack {
	data_type *data;
	int top, size;
} Stack;

Stack *init(int n);
void clear(Stack *);
data_type top(Stack *);
int push(Stack *, data_type);
int pop(Stack *);
int empty(Stack *);
void output(Stack *);

int main() {
	srand(time(0));
	Stack *s = init(100);

	for (int i = 0; i < 20; i++) {
		int op = rand() % 2, value = rand() % 100;
		switch (op) {
			case 0: {
				printf("pushh element = %d to Stack\n", value);
				push(s, value);
				output(s);
				break;
			}
			case 1: {
				printf("pop element from Stack\n");
				pop(s);
				output(s);
				break;
			}
			default: {
				fprintf(stderr, "error operator = %d\n", op);
				break;
			}
		}
	}
	clear(s);

	return 0;
}
void output(Stack *s) {
	int top = s->top;

	printf("[");
	for (int i = 0; i < 20; i++) {
		if (i < top) printf("%d,", s->data[i]);
		else printf(",");
	}
	printf("]\n");
	for (int i = 0; i < top; i++) {
		for (int j = 0; j < f(s->data[i]); j++){
			printf(" ");
		}
		if (i > 0) printf(" ");
	}
	printf("^\n");

	for (int i = 0; i < top; i++) {
		for (int j = 0; j < f(s->data[i]); j++){
			printf(" ");
		}
		if (i > 0) printf(" ");
	}
	printf("|\n");

	for (int i = 0; i < top; i++) {
		for (int j = 0; j < f(s->data[i]); j++){
			printf(" ");
		}
		if (i > 0 && i < top - 1) printf(" ");

	}
	printf("top\n");
}

Stack *init(int n) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data = (data_type *)malloc(sizeof(data_type) * n);
	s->size = n;
	s->top = -1;
	return s;
}

void clear(Stack *s) {
	if (s == NULL) return ;
	free(s->data);
	free(s);

	return ;
}

data_type top(Stack *s) {
	if (empty(s)) return NULL_VALUE;
	return s->data[s->top];
}

int push(Stack *s, data_type value) {
	if (s->top + 1 == s->size) {
		return 0;
	}
	s->top++;
	s->data[s->top] = value;

	return 1;
}

int pop(Stack *s) {
	if (empty(s)) return 0;
	s->top -= 1;

	return 1;
}

int empty(Stack *s) {

	return s->top == -1;
}