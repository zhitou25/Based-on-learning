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

//获取二叉树的高度
int BiTreeDepth(BiTree bt)
{
	if (!bt)
		return 0;
	return BiTreeDepth(bt->lchild) > BiTreeDepth(bt->rchild) ? BiTreeDepth(bt->lchild) + 1 : BiTreeDepth(bt->rchild) + 1;
}
//获取二叉树第k层的结点个数
int  BiTreeFlowNum(BiTree bt, int k)
{
	if (NULL == bt || k <1)
		return 0;
	if (k == 1)
		return 1;
	return BiTreeFlowNum(bt->lchild, k - 1) + BiTreeFlowNum(bt->rchild, k - 1);
}
//求二叉树的节点数
int BiTreeNode(BiTree bt)
{
	if (bt == NULL)
		return 0;
	return BiTreeNode(bt->lchild) + BiTreeNode(bt->rchild) + 1;
}
//返回二叉树叶子节点的个数
int BiTreeLeafNode(BiTree bt)
{
	//int count=0;
	if (!bt)
		return 0;
	if ((BiTreeLeafNode(bt->lchild) == 0 && BiTreeLeafNode(bt->rchild) == 0))
	{
		return 1;
	}
	else
	{
		return BiTreeLeafNode(bt->lchild) + BiTreeLeafNode(bt->rchild);
	}
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
	printf("二叉树总共有%d个节点\n", BiTreeNode(T));
	printf("树的高度是%d\n", BiTreeDepth(T));
	printf("有%d个叶子节点\n", BiTreeLeafNode(T));
	printf("第三层有%d个节点\n", BiTreeFlowNum(T, 3));
	system("pause");
	return 0;
}