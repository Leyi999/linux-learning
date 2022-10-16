
#include "game.h"
#include"infor.h"

int main() {
	srand((unsigned int)time(NULL));
	int input;
	do {
		menu();
		printf("请选择序号:>");
		scanf("%d", &input);
		switch (input) {
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		case 2:
			INFOR();
			break;
		default:
			printf("输入错误 重新输入\n");
		}

	} while (input);

	return 0;
}
