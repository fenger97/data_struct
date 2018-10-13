#include <stdio.h>
#include <stdlib.h>

typedef struct RBNode {
	int key, color; // 0 red 1 black 2 double black
	struct RBNode *lchild, *rchild;
} RBNode;

RBNode *NIL;

RBNode *getNewNode(int key) {
	RBNode *p = (RBNode *)malloc(sizeof(RBNode));
	p->key = key;
	p->color = 0; // 新节点默认为红色
	p->lchild = p->rchild = NIL;
	return p;
}

__attribute__((constructor)) void init_NIL() {
	NIL = getNewNode(0);
	NIL->color = 1;
	NIL->lchild = NIL->rchild = NIL;
	return ;
}

int hasRedChild(RBNode *node) {
	return node->lchild->color == 0 || node->rchild->color == 0;
}

RBNode *left_rotate(RBNode *node) {  // 操作次数少 不用调整深度 相比较AVL
	RBNode *temp = node->rchild;
	node->rchild = temp->lchild;    
	temp->lchild = node;
	return temp;
}

RBNode *right_rotate(RBNode *node) {
	RBNode *temp = node->lchild;
	node->lchild = temp->rchild;
	temp->rchild = node;
	return temp;
}

RBNode *insert_maintain(RBNode *root) {
	if (!hasRedChild(root)) return root;  // 祖父节点 的 两个孩子节点 都为黑色
	if (root->lchild->color == 0 && root->rchild->color == 0) { // 都为红色
		if (hasRedChild(root->lchild) || hasRedChild(root->rchild)) {  // 祖父节点的孩子节点有红色
			root->color = 0;                                // 不管哪个孩子是红色 都直接把祖父节点改为红色
			root->rchild->color = root->lchild->color = 1;  // 左右孩子改为黑色
		}
		return root;   // 本次调整结束 返回祖父节点 没有旋转
	}
	if (root->lchild->color == 0) { // 左子树为红色
		if (!hasRedChild(root->lchild)) return root; // 左子树的两个孩子都是黑色
		if (root->lchild->rchild->color == 0) {      // 左子树的右子树为红色 LR
			root->lchild = left_rotate(root->lchild);
		}
		root = right_rotate(root);  // LL
	} else {                        // 右子树红色
		if (!hasRedChild(root->rchild)) return root; // 右子树的两个孩子都是黑色
		if (root->rchild->lchild->color == 0) {      // 右子树的左子树为红色 RL
			root->rchild = right_rotate(root->rchild);
		}
		root = left_rotate(root);  // RR
	}
	root->color = 0;                               // 祖父节点改为 红色
	root->lchild->color = root->rchild->color = 1; // 左右孩子改为 黑色
	return root;
}

RBNode *__insert(RBNode *root, int key) {
	if (root == NIL || root == NULL) return getNewNode(key);
	if (root->key == key) return root;
	if (root->key < key) root->rchild = __insert(root->rchild, key);
	else root->lchild = __insert(root->lchild, key);
 	return insert_maintain(root);
}

RBNode *insert(RBNode *root, int key) {
	root = __insert(root, key);
	root->color = 1;       // 根节点改成黑色
	return root;
}

RBNode *predecessor(RBNode *node) {
	RBNode *temp = node->lchild;
	while (temp->rchild != NIL) temp = temp->rchild;
	return temp;
}

RBNode *erase_maintain(RBNode *root) {
	if (root->lchild->color != 2 && root->rchild->color != 2) return root; // root 左右孩子 都不是双重黑 不需要调整 直接返回
	if (root->lchild->color == 0 || root->rchild->color == 0) {   // root有红色节点 并且一个是双重黑
		root->color = 0;
		if (root->lchild->color == 0) {
			root->lchild->color = 1;                       // 把红色节点 改为黑色
			root = right_rotate(root);
			root->rchild = erase_maintain(root->rchild);   // 转成第一种
		} else {
			root->rchild->color = 1;
			root = left_rotate(root);
			root->lchild = erase_maintain(root->lchild);   // 转成第一种
		}
		return root; // 
	}
	if (root->lchild->color == 2) {  // 左孩子为 双重黑 右孩子为黑色
		if (!hasRedChild(root->rchild)) { // 坑 不能判断是否有黑色节点 root 右节点没有红色节点 都为黑色节点
			root->color += 1;			  // 根节点颜色 + 1 
			root->lchild->color = 1;      // 双重黑减少一层黑
			root->rchild->color = 0;	  // 另一条边 变成红色
			return root;
		} else if (root->rchild->rchild->color != 0) {  // 第二种 RL
			root->rchild = right_rotate(root->rchild);  // 兄弟右旋
			root->rchild->color = 1;					// 兄弟变
			root->rchild->rchild->color = 0;
		}
		root->lchild->color = 1;          // 38 变为黑色
		root = left_rotate(root);		  // 左旋
		root->color = root->lchild->color;// 交换颜色
		root->lchild->color = root->rchild->color = 1; //  双重黑减少一冲黑色
	} else {                         // 右孩子为双重黑
		if (!hasRedChild(root->lchild)) { // 坑 不能判断是否有黑色节点
			root->color += 1;
			root->rchild->color = 1;
			root->lchild->color = 0;
			return root;
		} else if (root->lchild->lchild->color != 0) {
			root->lchild = left_rotate(root->lchild);
			root->lchild->color = 1;
			root->lchild->lchild->color = 0;
		}
		root->rchild->color = 1;
		root = right_rotate(root);
		root->color = root->rchild->color;
		root->rchild->color = root->lchild->color = 1;
	}
	return root;
}

RBNode *__erase(RBNode *root, int key) {
	if (root == NIL || root == NULL) return NIL;  // 不存在 直接返回 NIL
	if (root->key < key) root->rchild = __erase(root->rchild, key);
	else if (root->key > key) root->lchild = __erase(root->lchild, key);
	else {
		if (root->lchild == NIL && root->rchild == NIL) { // 带删除节点没有孩子 出度为0
			NIL->color += root->color;                    // 可能是双重黑 
			free(root);
			return NIL;									  // 因为删除站在父节点看 所以可以直接返回
		} else if (root->lchild == NIL || root->rchild == NIL) {  // 出度为1
			RBNode *temp = root->lchild == NIL ? root->rchild : root->lchild;
			temp->color += root->color;                   // root如果红色 temp颜色不变 如果是黑色 temp变成双重黑
			free(root); 			
			return temp;
		} else {                                          // 出度为2
			RBNode *temp = predecessor(root);			  // 找到前驱
			root->key = temp->key;						  // 交换值
			root->lchild = __erase(root->lchild, temp->key);
		}
	}
	return erase_maintain(root);
}

RBNode *erase(RBNode *root, int key) {
	root = __erase(root, key);
	root->color = 1;
	return root;
}

void clear(RBNode *root) {
	if (root == NULL) return ;
	clear(root->lchild);
	clear(root->rchild);
	free(root);
	return ;
}

void output(RBNode *root) {
	if (root == NIL) return ;
	printf("(%d | %d, %d, %d)\n", root->color, root->key, root->lchild->key, root->rchild->key);
	output(root->lchild);
	output(root->rchild);
}

int main() {
	int op, value;
	RBNode *root = NIL;
	while (scanf("%d%d", &op, &value) != EOF) {
		switch (op) {
			case 0: root = insert(root, value); break;
			case 1: root = erase(root, value); break;
			default: printf("error\n");
		}
		output(root);
	}

	return 0;
}
