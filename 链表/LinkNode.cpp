#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct LinkNode {
	int data;
	struct LinkNode *next;
} LinkNode;

LinkNode *init(int data) {
	LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
	p->data = data;
	p->next = NULL;
	return p;
}

LinkNode *insert(LinkNode *head, int data, int ind) {
	if (ind < 0) return head;
	LinkNode ret, *p;
	ret.next = head;
	p = &ret;
	while (p && ind--) {
		p = p->next;
	}
	if (p == NULL) return head;
	LinkNode *new_node = init(data);
	new_node->next = p->next;
	p->next = new_node;
	return ret.next;
}

void clear(LinkNode *head) {
	while (head) {
		LinkNode *next = head->next;
		free(head);
		head = next;
	}
	return ;
}

void output(LinkNode *head) {
	while (head) {
		printf("%d ->", head->data);
		head = head->next;
	}
	printf("NULL\n");
}

int main() {
	LinkNode *head = NULL;
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		int data = rand() % 100, ind = rand() % (i+ 1);
		printf("%d : insert(%d %d) = ", i, data, ind);
		fflush(stdout);
		head = insert(head, data, ind);
		output(head);
	}

	return 0;
}