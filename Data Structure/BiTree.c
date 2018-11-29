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

void PreOrderTraverse(BiTree T)//���������������
{
	if (T == NULL)
		return;
	printf("%c ", T->val);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}
void InOrderTraverse(BiTree T)//���������������
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c ", T->val);
	InOrderTraverse(T->rchild);
}
void PostOrderTraverse(BiTree T)//�������
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c ", T->val);
}

//��ȡ�������ĸ߶�
int BiTreeDepth(BiTree bt)
{
	if (!bt)
		return 0;
	return BiTreeDepth(bt->lchild) > BiTreeDepth(bt->rchild) ? BiTreeDepth(bt->lchild) + 1 : BiTreeDepth(bt->rchild) + 1;
}
//��ȡ��������k��Ľ�����
int  BiTreeFlowNum(BiTree bt, int k)
{
	if (NULL == bt || k <1)
		return 0;
	if (k == 1)
		return 1;
	return BiTreeFlowNum(bt->lchild, k - 1) + BiTreeFlowNum(bt->rchild, k - 1);
}
//��������Ľڵ���
int BiTreeNode(BiTree bt)
{
	if (bt == NULL)
		return 0;
	return BiTreeNode(bt->lchild) + BiTreeNode(bt->rchild) + 1;
}
//���ض�����Ҷ�ӽڵ�ĸ���
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
	printf("�������ܹ���%d���ڵ�\n", BiTreeNode(T));
	printf("���ĸ߶���%d\n", BiTreeDepth(T));
	printf("��%d��Ҷ�ӽڵ�\n", BiTreeLeafNode(T));
	printf("��������%d���ڵ�\n", BiTreeFlowNum(T, 3));
	system("pause");
	return 0;
}