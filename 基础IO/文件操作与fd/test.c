#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
int main(){
//  FILE* pf1=fopen("bite","w+");
//  fputs("Linux so easy!\n",pf1);
//  fflush(pf1);
//  fseek(pf1,0,0);//文件指针 偏移量可为负 0开头 1 cur 2 end
//  char tmp[20];
//  fgets(tmp,20,pf1);
//  fputs(tmp,stdout);

//  umask(0);//先设置权限掩码保证文件权限正确
//  int i =open("bit.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
  int i =open("bit.txt",O_RDWR);
  printf("%d\n",i);
//  char* buffer="linux so easy!!";
//  ssize_t size=write(i,buffer,strlen(buffer));//不能带\n文件不认识
  char buffer[128];
  ssize_t size = read(3,buffer,128);   //文件标识符 缓冲区地址 希望读取的字节数 返回实际读取到的字节数
  ssize_t size2=write(1,buffer,size);//向标准输入写入“一切皆文件  //文件标识符 缓冲区地址 希望写入多少字节 返回实际写入字节数
  printf("\n%d %d\n",size,size2);
  close(3);
  return 0;
}
