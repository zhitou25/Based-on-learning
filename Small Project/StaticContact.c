#ifndef _CONTACT_H_
#define _CONTACT_H_
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<assert.h>
#pragma warning(disable:4996)
#define MAX 1000
typedef struct stu
{
	char name[20];
	char sex[10];
	int age;
	char tele[12];
	char addr[20];
} adlist;
typedef struct
{
	adlist data[1000];//��ϵ�˵���Ϣ
	int size;//ʵ�ʴ洢����
}contact, *pcontact;


void init_contact(pcontact pt);
void show_contact(pcontact pt);
void add_contact(pcontact pt);
void del_contact(pcontact pt);
int find_contact(pcontact pt);
void change_contact(pcontact pt);
void rank_contact(pcontact pt);
void write_file(pcontact pt);
void read_file(pcontact pt);
#endif//_CONTACT_H_



void init_contact(pcontact pt)//��ʼ��ͨѶ¼
{
	pt->size = 0;
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
	for (int i = 0; i < pt->size; i++)
	{
		printf("Name:%s\n", pt->data[i].name);
		printf("Sex:%s\n", pt->data[i].sex);
		printf("Age:%d\n", pt->data[i].age);
		printf("Tel:%s\n", pt->data[i].tele);
		printf("Addr:%s\n", pt->data[i].addr);
	}
	printf("\n");
}
void add_contact(pcontact pt)//�����ϵ��
{
	int count = 0;
	int num = 0;
	if (MAX == pt->size)
	{
		printf("ͨѶ¼������");
	}
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
			for (int i = 0; i < pt->size - 1; i++)
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
	printf("��ӳɹ���size=%d\n", pt->size);
}
int find_contact(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("ͨѶ¼Ϊ��!\n");
		return 0;
	}
	char name[20];
	printf("��������ϵ�˵�������");
	scanf("%s", name);
	int i = 0;
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
		printf("ͨѶ¼�޸���ϵ�ˣ�\n");
		return -1;
	}
	return 0;
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
	int i = 0;
	for (; i < pt->size; i++)
	{
		if (0 == strcmp(pt->data[i].name, name))
		{
			for (int j = i; j < pt->size; j++)
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
	for (int i = 0; i < pt->size - 1; i++)
	{
		for (int j = 0; j < pt->size - i - 1; j++)
		{
			if (strcmp(pt->data[j].name, pt->data[j + 1].name)>0)
			{
				char temp = *(pt->data[j + 1].name);
				*(pt->data[j + 1].name) = *(pt->data[j].name);
				*(pt->data[j].name) = temp;
			}
		}
	}
	for (int i = 0; i < pt->size; i++)
	{
		printf("Name:%s\n", pt->data[i].name);
		printf("Sex:%s\n", pt->data[i].sex);
		printf("Age:%d\n", pt->data[i].age);
		printf("Tel:%s\n", pt->data[i].tele);
		printf("Addr:%s\n", pt->data[i].addr);
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
		int i = 0;
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
		int i = 0;
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



//����Ϊ1000�ľ�̬ͨѶ¼

void menu()
{
	printf("***            ͨѶ¼           ***\n");
	printf("***1.�����ϵ��       2.ɾ����ϵ��***\n");
	printf("***3.��ʾ��ϵ��       4.������ϵ��***\n");
	printf("***5.������ϵ��       6.�޸���ϵ��***\n");
	printf("***7.�����ϵ��       8.д�뵽�ļ�***\n");
	printf("***9.������ϵ��      10.�˳�********\n");
}
int main()
{
	contact pt;
	init_contact(&pt);
	while (1)
	{
		menu();
		int choice;
		printf("please choose:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			add_contact(&pt);//�����ϵ��
			break;
		case 2:
			del_contact(&pt);//ɾ����ϵ��
			break;
		case 3:
			show_contact(&pt);//������ϵ��
			break;
		case 4:
			rank_contact(&pt);//������������ϵ��
			break;
		case 5:
			find_contact(&pt);//������ϵ��
			break;
		case 6:
			change_contact(&pt);//�޸���ϵ����Ϣ
			break;
		case 7:
			init_contact(&pt);//���
			break;
		case 8:
			write_file(&pt);//д���ļ�
			break;
		case 9:
			read_file(&pt);//�����ļ�
			break;
		case 10:
			exit(0);//�˳�
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}
