#include <stdio.h>
#include<sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
  umask(0);
  write(1,"linux so easy!\n",15);
  return 0;
}
//  int fd1 = open("test1",O_CREAT|O_TRUNC|O_WRONLY,0666);
//  printf("fd1: %d\n",fd1);
//  int fd2 = open("test1",O_CREAT|O_TRUNC|O_WRONLY,0666);
//  printf("fd2: %d\n",fd2);
//  close(fd1);
//  printf("fd1: closed\n");
//  int fd3 = open("test1",O_CREAT|O_TRUNC|O_WRONLY,0666);
//  printf("fd3: %d\n",fd3);
//  int fd4 = open("test1",O_CREAT|O_TRUNC|O_WRONLY,0666);
//  printf("fd4:%d\n",fd4);
//  return 0;
