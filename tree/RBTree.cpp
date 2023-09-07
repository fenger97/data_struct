#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	int key, color;               // 颜色 0 红色 1 黑色 2 双重黑
	struct Node *lchild, *rchild;
} Node;

Node *NIL;
void init_NIL() {
	NIL = (Node *)malloc(sizeof(Node));
	NIL->key = 0;
	NIL->color = 1;
	NIL->lchild = NIL->rchild = NIL;
}

Node *init(int key) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->key = key;
	p->color = 0;
	p->rchild = p->lchild = NIL;
	return p;
}

Node *pre(Node *root) {           // 找前驱节点
	Node *temp = root->lchild;
	while (temp->rchild != NIL) temp = temp->rchild;
	return temp;
}

Node *left(Node *root) {         // 左旋
	Node *temp = root->rchild;
	root->rchild = temp->lchild;
	temp->lchild = root;
	return temp;
}

Node *right(Node *root) {       // 右旋
	Node *temp = root->lchild;
	root->lchild = temp->rchild;
	temp->rchild = root;
	return temp;
}

int hasred(Node *root) {      // 判断当前节点存在红色节点
	return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *insert_maintain(Node *root) {        // 插入调整
	if (!hasred(root)) return root;        // 没有红色节点
	if (root->lchild->color == 0 && root->rchild->color == 0) {     // 都为红色节点
		if (hasred(root->lchild) || hasred(root->rchild)) {         // 孙子为红色节点
			root->color = 0;                                        // 红色上顶
			root->rchild->color = root->lchild->color = 1;
		}
		return root;
	} 
	else if (root->lchild->color == 0) {                   // 左子树为红色
		if (!hasred(root->lchild)) return root;			   // 左子树没有红色节点
		if (root->lchild->rchild->color == 0) {			   // 左子树的右子树为红色
			root->lchild = left(root->lchild);	           // 左旋
		}
		root = right(root);								   // 右旋
	} else {
		if (!hasred(root->rchild)) return root;
		if (root->rchild->lchild->color == 0) {
			root->rchild = right(root->rchild);
		}
		root = left(root);
	}
	root->lchild->color = root->rchild->color = 1;         
	return root;
}

Node *__insert(Node *root, int key) {
	if (root == NULL || root == NIL) return init(key);
	if (root->key == key) return root;
	else if (root->key > key) root->lchild = __insert(root->lchild, key);
	else root->rchild = __insert(root->rchild, key);
	return insert_maintain(root);
}

Node *insert(Node *root, int key) {
	root = __insert(root, key);
	root->color = 1;
	return root;
}

Node *erase_maintain(Node *root) {
	if (root->lchild->color != 2 && root->rchild->color != 2) return root;
	if (root->lchild->color == 0 || root->rchild->color == 0) {
		root->color = 0;
		if (root->lchild->color == 0) {
			root->lchild->color = 1;
			root = right(root);
			root->rchild = erase_maintain(root->rchild);
		} else {
			root->rchild->color = 1;
			root = left(root);
			root->lchild = erase_maintain(root->lchild);
		}
		return root;
	} else if (root->lchild->color == 2) {
		if (!hasred(root->rchild)) {
			root->color += 1;
			root->lchild->color = 1;
			root->rchild->color = 0;
			return root;
		}
		if (root->rchild->rchild->color != 0) {
			root->rchild= right(root->rchild);
			root->rchild->color = 1;
			root->rchild->rchild->color = 0;
		}
		root->lchild->color = 1;
		root = left(root);
		root->color = root->lchild->color;
		root->lchild->color = root->rchild->color = 1;
	} else {
		if (!hasred(root->lchild)) {
			root->color += 1;
			root->rchild->color = 1;
			root->lchild->color = 0;
			return root;
		}
		if (root->lchild->lchild->color != 0) {
			root->lchild= left(root->lchild);
			root->lchild->color = 1;
			root->lchild->lchild->color = 0;
		}
		root->rchild->color = 1;
		root = right(root);
		root->color = root->rchild->color;
		root->lchild->color = root->rchild->color = 1;
	}
	return root;
}

Node *__erase(Node *root, int key) {;
	if (root == NULL || root == NIL) return root;
	if (root->key > key) root->lchild = __erase(root->lchild, key);
	else if (root->key < key) root->rchild = __erase(root->rchild, key);
	else if (root->key == key) {
		if (root->lchild == NIL && root->rchild == NIL) {
			NIL->color += root->color;
			free(root);
			return NIL;
		} else if (root->lchild == NIL || root->rchild == NIL) {
			Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
			temp->color += root->color;
			free(root);
			return temp;
		} else {
			Node *temp = pre(root);
			root->key = temp->key;
			root->lchild = __erase(root->lchild, temp->key);
		}
	}
	return erase_maintain(root);
}

Node *erase(Node *root, int key) {
	root = __erase(root, key);
	root->color = 1;
	return root;
}

void output(Node *root) {
    if (root == NIL) return ;
    output(root->lchild);
    printf("%d %d %d %d\n", root->key, root->color, root->lchild->key, root->rchild->key);
    output(root->rchild);
    return ;
}

int main() {
	init_NIL();
	Node *root = NIL;
	int p = 0, key = 1;
    while (scanf("%d %d\n", &p, &key) != EOF) {
        switch (p) {
            case 1: {
                root = insert(root, key);
                break;
            }
            case 2: {
            	root = erase(root, key);
                break;
            }
            case 3: {
                output(root);
            }
        }
    }
    return 0;
}
