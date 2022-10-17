#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
  FILE* pf1=fopen("bite","w+");
  fputs("Linux so easy!\n",pf1);
  fflush(pf1);
  fseek(pf1,0,0);//文件指针 偏移量可为负 0开头 1 cur 2 end
  char tmp[20];
  fgets(tmp,20,pf1);
  fputs(tmp,stdout);
  return 0;
}
