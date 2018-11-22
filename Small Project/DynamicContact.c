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
		printf("你的通讯录已满！\n");
		return;
	}
	int count = 0;
	int num = 0;
	if (0 == pt->size)
	{
		printf("请输入姓名：");
		scanf("%s", pt->data[pt->size].name);
	}
	else
	{
		while (0 == num)
		{
			printf("请输入姓名：");
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
	printf("请输入性别：");
	scanf("%s", pt->data[pt->size].sex);
	printf("请输入年龄：");
	scanf("%d", &(pt->data[pt->size].age));
	printf("请输入联系人号码：");
	scanf("%s", pt->data[pt->size].tele);
	printf("请输入联系人地址：");
	scanf("%s", pt->data[pt->size].addr);
	pt->size++;
	if (pt->size == n)
	{
		printf("你的通讯录已满！\n");

	}
	printf("添加成功！size=%d\n", pt->size);
}
int find_contact(pcontact pt)
{
	size_t i = 0;
	if (0 == pt->size)
	{
		printf("通讯录为空！");
		return 0;
	}
	printf("请输入查找人的姓名：");
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
		printf("没有找到该联系人！");
		return -1;
	}
	return 0;
}
void show_contact(pcontact pt)
{
	if (NULL == pt)
	{
		printf("通讯录为空!");
		return;
	}
	if (0 == pt->size)
	{
		printf("通讯录为空!");
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
		printf("通讯录为空!\n");
		return;
	}
	char name[20];
	printf("请输入联系人的姓名：");
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
			printf("联系人已删除!size=%d\n", pt->size);
		}
		else
		{
			printf("通讯录无该联系人！\n");
		}
	}
}
void change_contact(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("通讯录为空!\n");
		return;
	}
	int ret = find_contact(pt);
	if (ret != -1)
	{
		printf("请输入姓名：");
		scanf("%s", pt->data[ret].name);
		printf("请输入性别：");
		scanf("%s", pt->data[ret].sex);
		printf("请输入年龄：");
		scanf("%d", &(pt->data[ret].age));
		printf("请输入联系人号码：");
		scanf("%s", pt->data[ret].tele);
		printf("请输入联系人地址：");
		scanf("%s", pt->data[ret].addr);
	}
}
void rank_contact(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("通讯录为空!\n");
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
		printf("通讯录为空!\n");
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
		printf("写入文件完毕:)\n");
		fclose(file);
	}
}
void read_file(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("通讯录为空!\n");
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
	printf("***            通讯录             ***\n");
	printf("***1.添加联系人       2.删除联系人***\n");
	printf("***3.显示联系人       4.排序联系人***\n");
	printf("***5.查找联系人       6.修改联系人***\n");
	printf("***7.清空联系人       8.写入到文件***\n");
	printf("***9.加载联系人      10.退出********\n");
}
int main()
{

	pcontact pt;
	int num;
	int choice;
	printf("键入你通讯录大小(联系人的个数)：");
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
			printf("请选择要进行的操作：");
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				add_contact(pt, num);//添加联系人
				break;
			case 2:
				del_contact(pt);//删除联系人
				break;
			case 3:
				show_contact(pt);//加载联系人
				break;
			case 4:
				rank_contact(pt);//按姓名排序联系人
				break;
			case 5:
				find_contact(pt);//查找联系人
				break;
			case 6:
				change_contact(pt);//修改联系人信息
				break;
			case 7:
				init_contact(pt);//清空
				break;
			case 8:
				write_file(pt);//写入文件
				break;
			case 9:
				read_file(pt);//加载文件
				break;
			case 10:
				exit(0);//退出
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


