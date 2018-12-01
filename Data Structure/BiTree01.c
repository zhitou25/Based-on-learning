//递归遍历二叉树

//二叉树的先序遍历
void PreOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	printf("%c ", T->val);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

//二叉树的中序遍历
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c ", T->val);
	InOrderTraverse(T->rchild);
}

//二叉树的后序遍历
void PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c ", T->val);
}




//用栈进行非递归遍历二叉树

//先序遍历
void  Preorder(BiTree root)
{
	pstack pt = (pstack)malloc(sizeof(stack));
	if (!root)
		return;
	StackInit(pt);
	StackPush(pt, root);
	while (!StackEmpty(pt))
	{
		BiTree pcur = pt->array[(pt->top) - 1];
		printf("%c ", pcur->val);
		StackPop(pt);
		if (pcur->rchild)
			StackPush(pt, pcur->rchild);
		if (pcur->lchild)
			StackPush(pt, pcur->lchild);
	}
	printf("\n");
}
//中序遍历
void  Inorder(BiTree root)
{
	pstack pt = (pstack)malloc(sizeof(stack));
	if (!root)
		return;
	StackInit(pt);
	BiTree pcur = root;
	while (!StackEmpty(pt) || pcur)
	{
		while (pcur)
		{
			StackPush(pt, pcur);
			pcur = pcur->lchild;
		}
		pcur = pt->array[pt->top - 1];
		StackPop(pt);
		printf("%c ", pcur->val);
		pcur = pcur->rchild;
	}
	printf("\n");
}
//后序遍历
void  Postorder(BiTree root)
{
	pstack pt = (pstack)malloc(sizeof(stack));
	if (!root)
		return;
	StackInit(pt);
	BiTree pcur = root;
	BiTree prev = NULL;//标记被遍历过的右孩子结点
	while (!StackEmpty(pt) || pcur)
	{
		while (pcur)
		{
			StackPush(pt, pcur);
			pcur = pcur->lchild;
		}
		BiTree ptop = pt->array[pt->top - 1];
		//如果ptop的右子树为空，输出根结点，否则从该结点右孩子处继续向下遍历
		//用prve标记已经被遍历过的右孩子，否则会死循环
		if (NULL == ptop->rchild || prev == ptop->rchild)
		{
			printf("%c ", ptop->val);
			prev = ptop;
			StackPop(pt);
		}
		else
		{
			pcur = ptop->rchild;
		}
	}
	printf("\n");
}


//层序遍历，借助队列
void  BiTreeFlow(BiTree pRoot)
{
	Queue q;//q的空间在栈上，队列中节点的空间在堆上
	if (NULL == pRoot)
		return;
	QueueInit(&q);
	QueuePush(&q, pRoot);
	while (!QueueEmpty(&q))
	{
		BiTree pcur = QueueFront(&q);
		QueuePop(&q);
		printf("%c ", pcur->val);
		if (pcur->lchild)
			QueuePush(&q, pcur->lchild);
		if (pcur->rchild)
			QueuePush(&q, pcur->rchild);
	}
	DestoryQueue(&q);
}


//判断二叉树是不是一棵完全二叉树
int Judge(BiTree pRoot)
{
	pq q = (pq)malloc(sizeof(Queue));//借助队列完成
	if (NULL == pRoot)
		return 1;
	QueueInit(q);
	QueuePush(q, pRoot);
	while (!QueueEmpty(q))
	{
		int flag = 0;
		if (flag == 1)
		{
			if (q->base[q->front]->lchild || q->base[q->front]->rchild)
			{
				DestoryQueue(q);
				return 0;
			}
		}
		else
		{
			if (q->base[q->front]->lchild == NULL && q->base[q->front]->rchild == NULL)
			{
				flag = 1;
			}
			if (q->base[q->front]->lchild&& q->base[q->front]->rchild == NULL)
			{
				flag = 1;
			}
			if (q->base[q->front]->lchild == NULL&&q->base[q->front]->rchild)
			{
				return 0;
			}
			if (q->base[q->front]->lchild&&q->base[q->front]->rchild)
			{
				QueuePush(q, q->base[q->front]->lchild);
				QueuePush(q, q->base[q->front]->rchild);
			}
		}
		QueuePop(q);
	}
	return 1;
}
