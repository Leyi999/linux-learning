#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#define ROW 9 
#define COL 9 
#define ROWS 11
#define COLS 11
//扫雷游戏主体
void game();
//初始化棋盘的函数
void InitBoard(char Board[ROWS][COLS], int rows, int cols, char set);
//打印棋盘的函数
void DisplayBoard(char Board[ROWS][COLS], int row, int col);
//设置雷的函数
void SetMine(char Board[ROWS][COLS],int row,int col,int nub);
//玩家排雷(一直玩到结束，返回值为输赢结果)
char FindMine(char Board[ROWS][COLS], char show[ROWS][COLS], int row, int col,int nub);
//返回点周围雷的个数
char CountMine(char Board[ROWS][COLS],char[ROWS][COLS] ,int row, int col);
//将点展开
void Extend(char Board[ROWS][COLS], char show[ROWS][COLS], int row, int col);
//判断赢没赢(赢返回 1 ，没赢返回 0 )
int Is_win(char Board[ROWS][COLS],char show[ROWS][COLS], int row, int col,int nub);
//游戏胜利 或 失败后延时打印结果
void SleepPrint(char* p);
