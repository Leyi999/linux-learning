#include"game.h"

void menu() {
	printf("***************************\n");
	printf("*******   1. PLAY   *******\n");
	printf("*******   0. EXIT   *******\n");
	printf("*******   2. INFOR  *******\n");
	printf("***************************\n");

}
void menu_in() {
	printf("1.游戏规则\n");
	printf("2.制作信息\n");
	printf("3.奖励\n");
	printf("0.返回\n");

}
void game_rules() {
	printf("\n踩点和标记需输入对应 行和列如 第一行第一列 应该输入 \"1 1\"\n猜到雷会被炸死,恐怖至极，骨灰都找不到!!!\n踩到非雷会显示以它中心3X3矩形范围内雷的个数.\n如果显示0会自动帮你展开\n正确标记出所有雷,或者踩完所有非雷点即可获胜.\nthats it...\n\n");
}
void infor() {
	printf(".一步一步按提示来 不然要炸\n\n");
}
void reward() {
	printf("完成1级即可获得:> ");

	printf("乐意的大拇指！！！\n\n");

}

void INFOR() {
	int input;
	do {
		menu_in();
		printf("请选择序号:>");
		scanf("%d", &input);
		switch (input) {
		case 1:
			game_rules();
			break;
		case 2:
			infor();
			break;
		case 3:
			reward();
			break;
		case 0:
			break;
		default:
			printf("输入错误 重新输入\n");//输入错入提示
		}
	} while (input);
}
