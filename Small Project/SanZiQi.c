#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#pragma warning(disable:4996)
#define ROW 3
#define COL 3

//显示棋盘
void show_board(char board[ROW][COL], int rows, int cols)
{
	int i = 0;
	for (i = 0; i < rows; i++)
	{
		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
		if (i != rows - 1)
			printf("---|---|---\n");
	}
	printf("\n");
}
//初始化棋盘
void init_board(char board[ROW][COL], int rows, int cols)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = ' ';
		}
	}
}
//玩家下棋
void play_move(char arr[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("玩家:\n");
		scanf("%d%d", &x, &y);
		if (((x >= 1) && (x <= row)) && ((y >= 1) && (y <= col)))
		{
			if (arr[x - 1][y - 1] == ' ')
			{
				arr[x - 1][y - 1] = 'x';
				break;
			}
			else
				printf("此处已有棋子！请重新输入坐标\n");
		}
		else
			printf("坐标非法，请重新输入！\n");
	}
}
//电脑下棋
void computer_move(char  arr[ROW][COL], int row, int col)
{
	while (1)
	{
		printf("电脑:\n");
		int x = rand() % 3;
		int y = rand() % 3;
		if (arr[x][y] == ' ')
		{
			arr[x][y] = 'o';
			break;
		}
	}
}

//判断棋盘是否下满
static int is_full(char arr[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (arr[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}

//判断游戏结果
char check_win(char  arr[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		if ((arr[i][0] == arr[i][1]) && (arr[i][1] == arr[i][2]) && (arr[i][0] != ' '))
		{
			return arr[i][0];
		}
	}
	for (i = 0; i < row; i++)
	{
		if ((arr[0][i] == arr[1][i]) && (arr[1][i] == arr[2][i]) && (arr[0][i] != ' '))
		{
			return arr[0][i];
		}
	}
	if ((arr[0][0] == arr[1][1]) && (arr[1][1] == arr[2][2]) && (arr[0][0] != ' '))
		return arr[0][0];
	else if ((arr[0][2] == arr[1][1]) && (arr[1][1] == arr[2][0]) && (arr[0][2] != ' '))
		return arr[1][1];
	else if (is_full(arr, ROW, COL))
		return 'e';
	return ' ';
}








void menu()
{
	printf("########三子棋游戏#######\n");
	printf("##1.play        2.exit###\n");
	printf("#########################\n");
}
//游戏逻辑
void game()
{
	char n = 0;
	char arr[ROW][COL] = { 0 };
	init_board(arr, ROW, COL);
	while (1)
	{
		computer_move(arr, ROW, COL);
		show_board(arr, ROW, COL);
		n = check_win(arr, ROW, COL);
		if (n != ' ')
		{
			break;
		}
		play_move(arr, ROW, COL);
		show_board(arr, ROW, COL);
		n = check_win(arr, ROW, COL);
		if (n != ' ')
		{
			break;
		}
	}
	if (n == 'x')
	{
		printf("玩家胜利！\n");
	}
	else if (n == 'o')
	{
		printf("电脑胜利！\n");
	}
	else if (n == 'e')
	{
		printf("平局！\n");
	}
}
int main()
{
	while (1)
	{
		int choice;
		srand((unsigned int)time(NULL));
		menu();
		printf("请选择-> ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			game();
			break;
		case 2:
			exit(0);
			break;
		default:
			printf("输入错误\n");
			break;
		}
	}
	system("pause");
	return 0;
}