#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void InitBoard(char Board[ROW][COL], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			Board[i][j] = ' ';
	}
}
void DisplayBoard(char Board[ROW][COL], int row, int col) {
	int r;
	int c;
	for (r = 0; r < row; r++) {
		for (c = 0; c < col; c++) {
			printf(" %c ", Board[r][c]);
			if (c + 1 < col)
				printf("|");
		}
		printf("\n");
		printf("---|---|---\n");

	}

}
void Player_Move(char Board[ROW][COL], int row, int col) {
	printf("玩家走:>");
	int ro, co;
	while (1) {
		scanf("%d %d", &ro, &co);
		if (ro <= row && co <= col && ro > 0 && co > 0 && Board[ro - 1][co - 1] == ' ') {
			Board[ro - 1][co - 1] = 'X';
			break;
		}
		else {
			if (!(ro <= row && co <= col && ro > 0 && co > 0))
			{
				printf("输错了 重新输入:>\n");
			}
			else
			{
				printf("这个点(%d,%d)已经有棋子了，不许叠罗汉\n",ro,co);
			}
			DisplayBoard(Board, row, col);
		}
	}
}
void Computer_Move(char Board[ROW][COL], int row, int col) {
	int ro, co;
	printf("AI走:>\n");
	while (1) {
		ro = rand() % row;
		co = rand() % col;
		if (Board[ro][co] == ' ') {
			Board[ro][co] = 'O';
			break;
		}
	}
}
int Is_full(char Board[ROW][COL], int row, int col) {
	int i = row;
	int j = col;
	int flag = 1;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (Board[i][j] == ' ')
				flag = 0;
		}
	}
	return flag;
}
char Is_win(char Board[ROW][COL], int row, int col) {
	int i;
	int j;
	int flag;
	flag= 0;
	for (i = 0; i < row; i++, flag = 0) {
		
		for (j = 1; j < col; j++) {
			if (' ' == Board[i][j - 1] || ' ' == Board[i][j]) {
				continue;
			}
			if (Board[i][j] == Board[i][j-1]) {
				flag++;
				if (flag == 2)
					return Board[i][j];
			}
			
		}
		
	}

	for (j = flag = 0; j < col; j++, flag = 0) {

		for (i = 1; i < row; i++) {

			if (' ' == Board[i-1][j] || ' ' == Board[i][j]) {
				continue;
			}
			if (Board[i][j] == Board[i-1][j])
				flag++;
			if (2 == flag)
				return Board[i][j];
		}
		
	}
	
	for (i = 1,flag = 0; i < row; i++) {
		
		if ((Board[i][i] == Board[i - 1][i - 1])&&Board[i][i]!=' ') {
			flag++;
		}
		if (2==flag) {
			return Board[i][i];
		}
	}

	for (i = 1, j = 1, flag = 0; i < row&&j>=0; i++,j--) {
		//0,2 //1,1 //2,0 
		if ((Board[i][j] == Board[i - 1][j + 1]) && Board[i][j] != ' ') {
			flag++;
		}
		if (2 == flag) {
			return Board[i][j];
		}

	}
	
	if(Is_full(Board,row,col)){
		return 'P';
	}
	return 'C';
}

	
