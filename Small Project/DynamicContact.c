#ifndef _CONTACT_H_
#define _CONTACT_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

typedef struct stu
{
	char name[20];
	char sex[10];
	size_t age;
	char tele[12];
	char addr[20];
}adlist;
typedef struct
{
	adlist *data;
	size_t size;
}contact, *pcontact;
void init_contact(pcontact pt);
void add_contact(pcontact pt, int n);
void del_contact(pcontact pt);
void show_contact(pcontact pt);
int find_contact(pcontact pt);
void change_contact(pcontact pt);
void rank_contact(pcontact pt);
void write_file(pcontact pt);
void read_file(pcontact pt);
#endif //_CONTACT_H_





void init_contact(pcontact pt)
{
	pt->size = 0;
}

void add_contact(pcontact pt, int n)
{
	if (pt->size == n)
	{
		printf("���ͨѶ¼������\n");
		return;
	}
	int count = 0;
	int num = 0;
	if (0 == pt->size)
	{
		printf("������������");
		scanf("%s", pt->data[pt->size].name);
	}
	else
	{
		while (0 == num)
		{
			printf("������������");
			scanf("%s", pt->data[pt->size].name);
			for (size_t i = 0; i < pt->size - 1; i++)
			{
				if (0 == strcmp(pt->data[i].name, pt->data[pt->size].name))
				{
					num = 1;
					break;
				}
			}
			if (1 == num)
			{
				num = 0;
			}
			else
			{
				num = 1;
			}
		}
	}
	printf("�������Ա�");
	scanf("%s", pt->data[pt->size].sex);
	printf("���������䣺");
	scanf("%d", &(pt->data[pt->size].age));
	printf("��������ϵ�˺��룺");
	scanf("%s", pt->data[pt->size].tele);
	printf("��������ϵ�˵�ַ��");
	scanf("%s", pt->data[pt->size].addr);
	pt->size++;
	if (pt->size == n)
	{
		printf("���ͨѶ¼������\n");

	}
	printf("��ӳɹ���size=%d\n", pt->size);
}
int find_contact(pcontact pt)
{
	size_t i = 0;
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ�գ�");
		return 0;
	}
	printf("����������˵�������");
	char name[20];
	scanf("%s", name);
	for (; i < pt->size; i++)
	{
		if (0 == strcmp(pt->data[i].name, name))
		{
			printf("Name:%s\n", pt->data[i].name);
			printf("Sex:%s\n", pt->data[i].sex);
			printf("Age:%d\n", pt->data[i].age);
			printf("Tel:%s\n", pt->data[i].tele);
			printf("Addr:%s\n", pt->data[i].addr);
			return i;
		}
	}
	if (i == pt->size)
	{
		printf("û���ҵ�����ϵ�ˣ�");
		return -1;
	}
	return 0;
}
void show_contact(pcontact pt)
{
	if (NULL == pt)
	{
		printf("ͨѶ¼Ϊ��!");
		return;
	}
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ��!");
	}
	for (size_t i = 0; i < pt->size; i++)
	{
		printf("Name:%s\n", pt->data[i].name);
		printf("Sex:%s\n", pt->data[i].sex);
		printf("Age:%d\n", pt->data[i].age);
		printf("Tel:%s\n", pt->data[i].tele);
		printf("Addr:%s\n", pt->data[i].addr);
		printf("\n");
	}
	printf("\n");
}

void del_contact(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	char name[20];
	printf("��������ϵ�˵�������");
	scanf("%s", name);
	size_t i = 0;
	for (; i < pt->size; i++)
	{
		if (0 == strcmp(pt->data[i].name, name))
		{
			for (size_t j = i; j < pt->size; j++)
			{
				pt->data[j] = pt->data[j + 1];
			}
			pt->size--;
			printf("��ϵ����ɾ��!size=%d\n", pt->size);
		}
		else
		{
			printf("ͨѶ¼�޸���ϵ�ˣ�\n");
		}
	}
}
void change_contact(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	int ret = find_contact(pt);
	if (ret != -1)
	{
		printf("������������");
		scanf("%s", pt->data[ret].name);
		printf("�������Ա�");
		scanf("%s", pt->data[ret].sex);
		printf("���������䣺");
		scanf("%d", &(pt->data[ret].age));
		printf("��������ϵ�˺��룺");
		scanf("%s", pt->data[ret].tele);
		printf("��������ϵ�˵�ַ��");
		scanf("%s", pt->data[ret].addr);
	}
}
void rank_contact(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	for (size_t i = 0; i < pt->size - 1; i++)
	{
		for (size_t j = 0; j < pt->size - i - 1; j++)
		{
			if (strcmp(pt->data[j].name, pt->data[j + 1].name)>0)
			{
				char temp[20];
				strcpy(temp, pt->data[j + 1].name);
				strcpy(pt->data[j + 1].name, pt->data[j].name);
				strcpy(pt->data[j].name, temp);
			}
		}
	}
	for (size_t i = 0; i < pt->size; i++)
	{
		printf("Name:%s\n", pt->data[i].name);
		printf("Sex:%s\n", pt->data[i].sex);
		printf("Age:%d\n", pt->data[i].age);
		printf("Tel:%s\n", pt->data[i].tele);
		printf("Addr:%s\n", pt->data[i].addr);
		printf("\n");
	}
	printf("\n");
}
void write_file(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	FILE *file = fopen("log.txt", "w+");
	if (NULL != file)
	{
		size_t i = 0;
		for (; i < pt->size; i++)
		{
			fprintf(file, "%s %s %d %s %s\n",
				pt->data[i].name, pt->data[i].sex, pt->data[i].age, pt->data[i].tele, pt->data[i].addr);
		}
		printf("д���ļ����:)\n");
		fclose(file);
	}
}
void read_file(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return;
	}
	FILE *file = fopen("contact.txt", "w+");
	if (NULL != file)
	{
		size_t i = 0;
		for (; i < pt->size; i++)
		{
			fscanf(file, "%s %s %d %s %s\n",
				pt->data[i].name, pt->data[i].sex, &pt->data[i].age, pt->data[i].tele, pt->data[i].addr);

			printf("%s %s %d %s %s\n", \
				pt->data[i].name, pt->data[i].sex, pt->data[i].age, pt->data[i].tele, pt->data[i].addr);
		}
		fclose(file);
	}
}





void menu()
{
	printf("***            ͨѶ¼             ***\n");
	printf("***1.�����ϵ��       2.ɾ����ϵ��***\n");
	printf("***3.��ʾ��ϵ��       4.������ϵ��***\n");
	printf("***5.������ϵ��       6.�޸���ϵ��***\n");
	printf("***7.�����ϵ��       8.д�뵽�ļ�***\n");
	printf("***9.������ϵ��      10.�˳�********\n");
}
int main()
{

	pcontact pt;
	int num;
	int choice;
	printf("������ͨѶ¼��С(��ϵ�˵ĸ���)��");
	scanf("%d", &num);
	pt = (pcontact)malloc(sizeof(contact));
	pt->data = (adlist*)malloc(sizeof(adlist)*num);
	init_contact(pt);
	while (1)
	{
		menu();
		printf("\n");
		if (NULL != pt)
		{
			printf("��ѡ��Ҫ���еĲ�����");
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				add_contact(pt, num);//�����ϵ��
				break;
			case 2:
				del_contact(pt);//ɾ����ϵ��
				break;
			case 3:
				show_contact(pt);//������ϵ��
				break;
			case 4:
				rank_contact(pt);//������������ϵ��
				break;
			case 5:
				find_contact(pt);//������ϵ��
				break;
			case 6:
				change_contact(pt);//�޸���ϵ����Ϣ
				break;
			case 7:
				init_contact(pt);//���
				break;
			case 8:
				write_file(pt);//д���ļ�
				break;
			case 9:
				read_file(pt);//�����ļ�
				break;
			case 10:
				exit(0);//�˳�
				break;
			default:
				break;
			}
		}
	}
	free(pt->data);
	free(pt);
	system("pause");
	return 0;
}


