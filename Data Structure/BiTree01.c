//�ݹ����������

//���������������
void PreOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	printf("%c ", T->val);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

//���������������
void InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	InOrderTraverse(T->lchild);
	printf("%c ", T->val);
	InOrderTraverse(T->rchild);
}

//�������ĺ������
void PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c ", T->val);
}




//��ջ���зǵݹ����������

//�������
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
//�������
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
//�������
void  Postorder(BiTree root)
{
	pstack pt = (pstack)malloc(sizeof(stack));
	if (!root)
		return;
	StackInit(pt);
	BiTree pcur = root;
	BiTree prev = NULL;//��Ǳ����������Һ��ӽ��
	while (!StackEmpty(pt) || pcur)
	{
		while (pcur)
		{
			StackPush(pt, pcur);
			pcur = pcur->lchild;
		}
		BiTree ptop = pt->array[pt->top - 1];
		//���ptop��������Ϊ�գ��������㣬����Ӹý���Һ��Ӵ��������±���
		//��prve����Ѿ������������Һ��ӣ��������ѭ��
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


//�����������������
void  BiTreeFlow(BiTree pRoot)
{
	Queue q;//q�Ŀռ���ջ�ϣ������нڵ�Ŀռ��ڶ���
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


//�ж϶������ǲ���һ����ȫ������
int Judge(BiTree pRoot)
{
	pq q = (pq)malloc(sizeof(Queue));//�����������
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
