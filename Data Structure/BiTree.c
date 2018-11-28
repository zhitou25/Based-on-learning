#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
typedef struct BiTree {
	int val;
	struct BiTree *lchild, *rchild;
}BiNode,*BiTree;


void CreateBiTree(BiTree *T)
{
	char ch;
	scanf("%c", &ch);
	if (ch == ' ')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiNode));
		if (!*T)
			exit(0);
		(*T)->val = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}

void PreOrderTraverse(BiTree T)//二叉树的先序遍历
{
	if (T == NULL)
		return;
	printf("%c ", T->val);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}
void InOrderTraverse(BiTree T)//二叉树的中序遍历
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c ", T->val);
	InOrderTraverse(T->rchild);
}
void PostOrderTraverse(BiTree T)//后序遍历
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c ", T->val);
}








int main()
{
	BiTree T;
	CreateBiTree(&T);
	PreOrderTraverse(T);
	printf("\n");
	InOrderTraverse(T);
	printf("\n");
	PostOrderTraverse(T);
	printf("\n");
	system("pause");
	return 0;
}