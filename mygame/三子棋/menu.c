#define _CRT_SECURE_NO_WARNINGS 1
#include"menu.h"

void Infor_menu() {
	printf("1.三子棋游戏规则\n");
	printf("2.游戏简介\n");
	printf("0.都懂了（Ready）\n");
}
void rules() {
	
	printf("1. 下棋走子 需要输入棋盘坐标，输入时用空格隔开\n");
	printf("如 想在棋盘第一行第一列走子:应输入 \"1 1\" ; 三子一线即胜利:>\n");
	printf("\n");
}
void infor() {
	printf("该游戏的对手是凝聚了作者 目前所有的编程智慧结晶的AI副本\n"); 
	printf("原本难度极大，为了派遣你的孤独和保护你的心理健康故意放水\n若是不放水，难免日后留下难以消除的心理阴影 :>\n");
	printf("\n");

}
