#include"game.h"


//初始化棋盘的函数
void InitBoard(char Board[ROWS][COLS],int rows,int cols,char set) {
	int i;
	int j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			Board[i][j] = set;
		}
	}
}

void DisplayBoard(char Board[ROWS][COLS], int row, int col) {
	int i;
	int j;
	
	printf("————扫雷游戏————\n");
	for (j = 0; j < 10; j++) {
		if (0 == j) {
			printf("%d  ", j);
			continue;
		}
		printf("%d ",j);
	}
	printf("\n\n");
	for (i = 1; i <=row; i++) {
		printf("%d  ", i);
		for (j = 1; j <= col; j++) {
			printf("%c ", Board[i][j]);
		}
		printf("\n");
	}
	printf("————扫雷游戏————\n");

}
void SetMine(char Board[ROWS][COLS], int row, int col,int nub) {	 
	int i;
	int j;
	while (nub) {
		 i = rand() % row + 1;
		 j = rand() % col + 1;
		if (Board[i][j] == '*') {
			Board[i][j] = '#';
			nub--;

		}
	}
}
char CountMine(char Board[ROWS][COLS], char show[ROWS][COLS],int row, int col) {
	char count = '0';
	int i; int j;
	for (i = row - 1; i < row + 2; i++) {

		for (j = col - 1; j < col + 2; j++) {
			
			if (Board[i][j] == '#') {
				count++;

			}
		}

	}
	return count;
	}
	

void Extend(char Board[ROWS][COLS],char show[ROWS][COLS],int row,int col){
	show[row][col] = ' ';

	int i, j;
	for (i = row - 1; i < row + 2; i++) {
		for (j = col - 1; j < col + 2; j++) {
			
			if (show[i][j] == '*') {
				show[i][j] = CountMine(Board, show, i, j);
				if (show[i][j] == '0') {
					Extend(Board, show, i, j);
				}
			}
		}
		
	}
}
int Is_win(char Board[ROWS][COLS],char show[ROWS][COLS], int row, int col,int nub) {
	int i,j;
	int count = 0;//数正确的标记
	int count0 = 0;//数标记的总个数
	int COUNT = 0;//数*号后面是雷的个数
	int COUNT0 = 0;//数*号的总个数
	for (i = 1; i <=row; i++) {
		for (j = 1; j <= col; j++) {
			if (show[i][j] == '!') {
				count0++;
				if (Board[i][j] == '#') {
					count++;
				}
			}if (show[i][j] == '*') {
				COUNT0++;
				if (Board[i][j] == '#') {
					COUNT++;


				}
			}
		}
	}
	if ((nub == count&&nub==count0)|| COUNT == COUNT0) {
		return 1;
	}
	else if (nub == count && nub <= count0) {
		return 2;
	}
	
	return 0;
}

char FindMine(char Board[ROWS][COLS],char show[ROWS][COLS], int row,int col,int nub) {
	int a, b;
	int input=1;
	while (1) {
		printf("请选择是要踩(1)还是要标记(2):>");
		scanf("%d", &input);
		switch (input)
		{
		case 1://踩
			printf("请输入要走的行列:>");
			while (1) {
				scanf("%d %d", &a, &b);
				if (a > 0 && a < 10 && b>0 && b < 10) {
					if (show[a][b] != '*' && show[a][b] != '!') {
						printf("这个点 (%d行%d列) 已经踩过了,重新输入:>", a, b);
						continue;
					}
					break;
				}
				else
					printf("输入错误，重新输入:>");
			}
			if (Board[a][b] == '#') {
				return 'F';

			}
			else {
				show[a][b] = CountMine(Board, show, a, b);
				if (show[a][b] == '0') {
					Extend(Board, show, a, b);
				}
			}
			if (1 == Is_win(Board, show, row, col, nub)) {
				DisplayBoard(show, row, col);
				return 'W';
			}
			
			DisplayBoard(show, row, col);
		
			

			break;
		case 2://标记
			printf("请输入要标记的行列:>");
			while (1) {
				scanf("%d %d", &a, &b);
				if (a > 0 && a < 10 && b>0 && b < 10) {
					if (show[a][b] == '!') {
						show[a][b] = '*';
						if (1 == Is_win(Board, show, row, col, nub)) {
							DisplayBoard(show, row, col);
							return 'W';
						}
						if (2 == Is_win(Board, show, row, col, nub)) {
							printf("标记多了...");
						}
						
						break;
					}
					else {
						show[a][b] = '!';
						if (1==Is_win(Board, show, row, col,nub)) {
							return 'W';
						}
						if (2 == Is_win(Board, show, row, col, nub)) {
							printf("标记多了...");
						}
						break;
					}
				}
				else {
					printf("输入错误,重新输入:>");
				}
			}
			DisplayBoard(show, row, col);
			break;
		default:
			printf("输入错误,重新输入:>");
			printf("\n");
		}
	}
	
}
void usleepPrint(const char* p) {
	int i;
	int len = strlen(p);
	for (i = 0; i < len; i += 2) {
		printf("%c%c", *(p + i), *(p + i + 1));
		usleep(600);
	}

}
void game() {
	char Board[ROWS][COLS] = { 0 };//布置好雷的信息
	char show[ROWS][COLS] = { 0 };//排查出雷的信息
	InitBoard(Board, ROWS, COLS, '*');
	InitBoard(show, ROWS, COLS, '*');
	printf("请选择游戏难度(1~3):>");
	int tmpe;
	int nub=0;
	do {
		scanf("%d", &tmpe);
		switch (tmpe)
		{
		case 1:
			nub = 10;
			break;
		case 2:
			nub = 15;
			break;
		case 3:
			nub = 20;
			break;
		default:
			printf("输入错误,重新输入:>");
			break;
		}
	} while (tmpe != 1 && tmpe != 3 && tmpe != 2);
	SetMine(Board, ROW, COL, nub);
	DisplayBoard(show, ROW, COL);
	
	char Result=FindMine(Board, show, ROW, COL,nub);
	switch (Result) {
	case 'F':
		usleepPrint("你被炸死了");
		for (int i = 0; i < 3; i++) {
			printf(".");
			usleep(600);
		}
		printf("\n");
		DisplayBoard(Board, ROW, COL);
		break;
	case'W':

		usleepPrint("你赢了");
		for (int i = 0; i < 3; i++) {
			printf("!");
			usleep(600);
		}
		printf("\n");
		DisplayBoard(Board, ROW, COL);
	}
}
