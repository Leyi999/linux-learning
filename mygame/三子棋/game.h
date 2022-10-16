#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#define ROW 3
#define COL 3
//初始化棋盘的函数
void InitBoard(char Board[ROW][COL], int row, int col);
//打印棋盘的函数
void DisplayBoard(char Board[ROW][COL], int row, int col);
//玩家走- 实现赋值的函数
void Player_Move(char Board[ROW][COL], int row ,int col);
//电脑走- 限制随机 赋值的函数
void Computer_Move(char Board[ROW][COL], int row, int col);
//判断是否需要结束游戏
char Is_win(char Board[ROW][COL], int row, int col);
//判断棋盘是否满了的函数
int Is_full(char Board[ROW][COL], int row, int col);
