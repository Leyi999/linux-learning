#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"
#include"menu.h"

void Main_menu() {
	printf("*************************\n");
	printf("******1. 开始下棋********\n");
	printf("******0. 退出程序********\n");
	printf("*************************\n");
	printf("******2. 这是什么********\n");
}

void game() {
	//储存数据 二维数组
	char Board[ROW][COL];
	//初始化棋盘 - 初始化为空格
	InitBoard(Board,ROW,COL);
	char A ;
	//打印棋盘 — 打印数组内容
	DisplayBoard(Board, ROW, COL);
	//玩家走- 实现赋值的函数
	while(1) {
		Player_Move(Board, ROW, COL);
		DisplayBoard(Board, ROW, COL);
		 A = Is_win(Board, ROW, COL);
		if (A != 'C')
			break;
		Computer_Move(Board, ROW, COL);
	 	usleep(1000);
		DisplayBoard(Board, ROW, COL);
		A = Is_win(Board, ROW, COL);
		if (A != 'C')
			break;
	}
	switch (A) {
	case 'P':
		usleep(1000);
		printf("平局了,再来一把吧!\n");
		break;
	case'X':
		usleep(1000); 
		printf("你赢了，好厉害!\n");
		break;
	case'O':
		usleep(1000); 
		printf("电脑赢了，笨蛋!\n");
		break;
	}
}

void INFOR() {
	int input = 1;

	while (input) {
		Infor_menu();
		printf("请选择序号:");
		scanf("%d", &input);
		printf("\n");
		switch (input) {
		case 1:rules();
			break;
		case 2:infor();
			break;
		case 0:
			printf("都懂了就来下棋吧！\n");
			game();
			break;
		default:
			printf("输入无效，请重新输入\n");

		}
	}
}
int main() {
	srand((unsigned int)time(NULL));
	int input;
	do {
		Main_menu();
		printf("请选择序号:>");
		scanf("%d", &input);
		switch (input) {
		case 1:
			printf("\n需要看规则吗？\n\n");
			printf("1. 需要，我不知道怎么下\n");
			printf("2. 不需要，我是高手\n");
			int tmp;
			scanf(" %d", &tmp);
			switch (tmp) {
			case 1:
				INFOR();
				break;
			case 2:
				printf("请:>\n");
				game();
				break;
			}
			break;
		case 0:
			printf("立即退出程序");
			break;
		case 2:
			printf("\n这是一款 与人工智能对弈的三子棋!!!\n\n");
			break;
		default:
			printf("选择序号有误，请重新选择>\n");

		}
	} while (input != 0);


	return 0;
}
