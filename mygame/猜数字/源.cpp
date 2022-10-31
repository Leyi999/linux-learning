#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

void sign() {
	char arr1[] = "##########  ###";
	char arr2[] = "#########  ####";
	char arr3[] = "########  #####";
	char arr4[] = "#  ####  ######";
	char arr5[] = "##  ##  #######";
	char arr6[] = "###    ########";
	usleep(999);
	printf("%s\n", arr1);
	usleep(600);
	printf("%s\n", arr2);	
	usleep(600);
	printf("%s\n", arr3);	
	usleep(600);
	printf("%s\n", arr4);
	usleep(600);
	printf("%s\n", arr5);
	usleep(600);
	printf("%s\n", arr6);
	usleep(600);
	printf("\n\n\n");
}


void memu() {
	printf("*************************\n");
	printf("*********1. play*********\n");
	printf("*********0. exit*********\n");
	printf("*************************\n");
}
void game() {
	printf("猜猜数字(0～100):>");
	int a = rand()%100, guess;
	while (1)
	{
		scanf("%d", &guess);
		if (guess < a) {
			printf("猜小了\n再猜猜:>");
		}
		else if (guess > a) {
			printf("猜大了\n再猜猜:>");
		}
		else {
			printf("\n\n厉害,猜对了!!!\n\n");
			sign();
			break;
		}
	}
}
int main() {
	int input;
	srand((unsigned int)time(NULL));
	do {
		memu();
		printf("请选择序号:");
		scanf("%d",& input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("游戏结束，程序退出");
			break;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	} while (input);
			return 0;
}
