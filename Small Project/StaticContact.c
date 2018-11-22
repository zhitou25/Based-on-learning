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
	adlist data[1000];//联系人的信息
	int size;//实际存储个数
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



void init_contact(pcontact pt)//初始化通讯录
{
	pt->size = 0;
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
void add_contact(pcontact pt)//添加联系人
{
	int count = 0;
	int num = 0;
	if (MAX == pt->size)
	{
		printf("通讯录已满！");
	}
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
	printf("请输入性别：");
	scanf("%s", pt->data[pt->size].sex);
	printf("请输入年龄：");
	scanf("%d", &(pt->data[pt->size].age));
	printf("请输入联系人号码：");
	scanf("%s", pt->data[pt->size].tele);
	printf("请输入联系人地址：");
	scanf("%s", pt->data[pt->size].addr);
	pt->size++;
	printf("添加成功！size=%d\n", pt->size);
}
int find_contact(pcontact pt)
{
	if (0 == pt->size)
	{
		printf("通讯录为空!\n");
		return 0;
	}
	char name[20];
	printf("请输入联系人的姓名：");
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
		printf("通讯录无该联系人！\n");
		return -1;
	}
	return 0;
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
		printf("通讯录为空!\n");
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



//容量为1000的静态通讯录

void menu()
{
	printf("***            通讯录           ***\n");
	printf("***1.添加联系人       2.删除联系人***\n");
	printf("***3.显示联系人       4.排序联系人***\n");
	printf("***5.查找联系人       6.修改联系人***\n");
	printf("***7.清空联系人       8.写入到文件***\n");
	printf("***9.加载联系人      10.退出********\n");
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
			add_contact(&pt);//添加联系人
			break;
		case 2:
			del_contact(&pt);//删除联系人
			break;
		case 3:
			show_contact(&pt);//加载联系人
			break;
		case 4:
			rank_contact(&pt);//按姓名排序联系人
			break;
		case 5:
			find_contact(&pt);//查找联系人
			break;
		case 6:
			change_contact(&pt);//修改联系人信息
			break;
		case 7:
			init_contact(&pt);//清空
			break;
		case 8:
			write_file(&pt);//写入文件
			break;
		case 9:
			read_file(&pt);//加载文件
			break;
		case 10:
			exit(0);//退出
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}
