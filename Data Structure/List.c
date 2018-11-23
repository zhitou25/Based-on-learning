#ifndef _SLIST_H_
#define _SLIST_H_

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<assert.h>
#pragma warning(disable:4996)

typedef int DataType;
typedef struct SListNode
{
	struct SListNode* next;
	DataType data;
}SList, *pSList;


void SListInit(pSList* pHead);
pSList CreatNode(DataType data);
void SListPushFront(pSList* pHead, DataType data);
void  SListpushBack(pSList* pHead, DataType data);
void SListPopFront(pSList* pHead);
void SListPopBack(pSList* pHead);
pSList SListFind(pSList pHead, DataType data);
void SListInsert(pSList* pHead, int pos, DataType data);
void SListDestroy(pSList* pHead);
int SListSize(pSList pHead);
void SListRemoveAll(pSList *pHead, DataType data);
void SListErase(pSList* pHead, pSList pos);
void SlistBubbleSort(pSList *pHead);
void ShowSList(pSList pHead);
void removeElements(pSList head, int val);
#endif  //_SLIST_H_




// ����ͷ�ڵ�ĵ����� 
void SListInit(pSList* pHead)
{
	assert(pHead);
	*pHead = NULL;
}
//�����ڵ�
pSList CreatNode(DataType data)
{
	pSList sl = (pSList)malloc(sizeof(SList));
	if (sl == NULL)
	{
		printf("�ڴ�����ʧ�ܣ�\n");
		return NULL;
	}
	else
	{
		sl->data = data;
		sl->next = NULL;
	}
	return sl;
}
//ͷ����
void SListPushFront(pSList* pHead, DataType data)
{
	assert(pHead);
	pSList pcr = CreatNode(data);
	if (NULL != pcr)
	{
		if (*pHead == NULL)
		{
			*pHead = pcr;
			return;
		}
		pcr->next = *pHead;
		*pHead = pcr;
	}
}
//β����
void  SListpushBack(pSList* pHead, DataType data)
{
	assert(pHead);
	pSList pur = *pHead;
	pSList pcr = CreatNode(data);
	if (pcr != NULL)
	{

		if (NULL == (*pHead))
		{
			*pHead = pcr;
			return;
		}
		else
		{
			while (pur->next)
			{
				pur = pur->next;
			}
			pur->next = pcr;
		}
	}
	else
	{
		printf("��㴴��ʧ�ܣ�\n");
		return;
	}
}
//ͷɾ���
void SListPopFront(pSList* pHead)
{
	if (NULL == *pHead)
	{
		return;
	}
	pSList pcr;
	pcr = *pHead;
	*pHead = (*pHead)->next;
	free(pcr);
}
//βɾ���
void SListPopBack(pSList* pHead)
{
	assert(pHead);
	pSList pcr = *pHead;
	if (NULL == pcr)
	{
		return;
	}
	pSList pur = (*pHead)->next;
	if (NULL == pur)
	{
		free(*pHead);
		*pHead = NULL;
	}
	else
	{
		while (pur->next)
		{
			pcr = pur;
			pur = pur->next;
		}
		pSList tem = pcr->next;
		pcr->next = NULL;
		free(tem);
	}
}

//����ͷ��������Ѱ��ָ������
pSList SListFind(pSList pHead, DataType data)
{
	if (NULL != pHead)
	{
		pSList pcr = pHead;
		while (pcr)
		{
			if (pcr->data == data)
			{
				printf("%d\n", pcr->data);
				return pcr;
			}
			pcr = pcr->next;
		}
	}
	return NULL;
}
//��ָ��λ�ò���ָ������
void SListInsert(pSList* pHead, int pos, DataType data)
{
	assert(pHead);
	int num = 0;
	pSList pur = *pHead;
	while (pur)
	{
		pur = (pur)->next;
		num++;
	}
	if (pos >= 1 && pos <= num)
	{
		if (pos == 1)
		{
			SListPushFront(pHead, data);
			return;
		}
		else
		{
			if (pos == num)
			{
				SListpushBack(pHead, data);
				return;
			}
			else
			{
				pSList pcr = *pHead;
				pSList Node = CreatNode(data);

				while (pos - 2)
				{
					pcr = pcr->next;
				}
				pSList temp = pcr->next;
				pcr->next = Node;
				Node->next = temp;
			}
		}
	}
	else
	{
		printf("����λ�÷Ƿ���\n");
		return;
	}
}
//���ٵ�����
void SListDestroy(pSList* pHead)
{
	assert(pHead);
	pSList pcr = *pHead;
	while (pcr)
	{
		pSList temp = pcr;
		pcr = pcr->next;
		free(temp);
	}
	*pHead = NULL;
}
//��������
int SListSize(pSList pHead)
{
	int len = 0;
	assert(pHead);
	while (pHead)
	{
		pHead = pHead->next;
		len++;
	}
	printf("%d \n", len);
	return 0;
}
//ɾ��ָ������
void SListRemoveAll(pSList *pHead, DataType data)
{
	int num = 0;
	assert(pHead);
	pSList pcr = *pHead;
	pSList pur = NULL;
	pSList temp = NULL;
	while (pcr)
	{
		if (pcr->data == data)
		{
			if (pcr == *pHead)
			{
				temp = pcr;
				*pHead = pcr->next;
				pcr = *pHead;
				free(temp);
			}
			else
			{
				temp = pcr;
				pur->next = pcr->next;
				pcr = pcr->next;
				free(temp);
			}
		}
		else
		{
			pur = pcr;
			pcr = pcr->next;
		}
	}
}
//ɾ��pos�ڵ�
void SListErase(pSList* pHead, pSList pos)
{
	assert(pHead);
	pSList pcr = *pHead;
	if (NULL == *pHead)
	{
		printf("����Ϊ��\n");
		return;
	}
	pSList pur = pcr->next;
	if (*pHead = pos)
	{
		pSList temp = *pHead;
		*pHead = (*pHead)->next;
		free(temp);
		return;
	}
	else
	{
		while (pur)
		{
			if (pur == pos)
			{
				pSList temp = pos->next;
				pcr->next = pur->next;
				free(temp);
				return;
			}
			pcr = pur;
			pur = pur->next;
		}
		printf("�������޸ý�㣡\n");
	}
}


//ð������
void SlistBubbleSort(pSList *pHead)
{
	assert(pHead);
	int num = 0;
	if (NULL == *pHead)
	{
		printf("����Ϊ�գ�\n");
		return;
	}
	pSList pcr = *pHead;
	while (pcr)
	{
		pcr = pcr->next;
		num++;
	}
	pcr = *pHead;
	pSList pur = pcr->next;
	pSList chc = NULL;
	int i = 0;
	int j = 0;
	while (num--)//ѭ������
	{
		chc = NULL;
		pcr = *pHead;
		pur = pcr->next;
		while (pur)//�������һ�αȽϹ����Ƿ����
		{
			if (pcr->data > pur->data)
			{
				if (pcr == *pHead)
				{
					pSList temp = pcr->next;
					pcr->next = pur->next;
					temp->next = *pHead;
					*pHead = temp;
				}
				else
				{
					pSList temp1 = pcr->next;
					pSList temp2 = chc->next;
					pcr->next = pur->next;
					chc->next = temp1;
					pur->next = temp2;
				}
			}
			chc = pcr;
			pcr = pur;
			pur = pur->next;
		}
	}
}
void ShowSList(pSList pHead)
{
	pSList pcr = pHead;
	if (NULL == pcr)
	{
		return;
	}
	while (pcr)
	{
		printf("%d->", pcr->data);
		pcr = pcr->next;
	}
	printf("NULL");
	printf("\n");
}


#include"SList.h"



void menu()
{
	printf("#########################################################\n");
	printf("********      ��ͷ��㵥�������             ************\n");
	printf("******1.ͷ����            2.β����*******************\n");
	printf("******3.ͷɾ���            4.βɾ���*******************\n");
	printf("******5.��ָ������          6.��ָ��λ�ò���ָ������*****\n");
	printf("******7.��������          8.ɾ������ָ������***********\n");
	printf("******9.ɾ��ָ�����        10.ð������******************\n");
	printf("******11.��������           12.�˳� *********************\n");
	printf("#########################################################\n");
}

int main()
{
	pSList ps;
	SListInit(&ps);
	int choice;
	while (1)
	{
		menu();
		printf("��ѡ��\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			SListPushFront(&ps, 2);
			SListPushFront(&ps, 1);
			SListPushFront(&ps, 7);
			ShowSList(ps);
			break;
		case 2:
			SListpushBack(&ps, 5);
			SListpushBack(&ps, 8);
			SListpushBack(&ps, 0);
			ShowSList(ps);
			break;
		case 3:
			SListPopFront(&ps);
			ShowSList(ps);
			break;
		case 4:
			SListPopBack(&ps);
			ShowSList(ps);
			break;
		case 5:
			SListFind(ps, 7);
			break;
		case 6:
			SListInsert(&ps, 2, 4);
			ShowSList(ps);
			break;
		case 7:
			SListSize(ps);
			break;
		case 8:
			SListRemoveAll(&ps, 2);
			ShowSList(ps);
			break;
		case 9:
			SListErase(&ps, ps);
			ShowSList(ps);
			break;
		case 10:
			SlistBubbleSort(&ps);
			ShowSList(ps);
			break;
		case 11:
			SListDestroy(&ps);
			ShowSList(ps);
			break;
		case 12:
			exit(1);
			break;
		default:
			printf("ѡ���������\n");
			break;
		}
	}
	system("pause");
	return 0;
}

