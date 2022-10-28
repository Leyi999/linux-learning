#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(){
  umask(0);
  int fd  =open("test.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
  const char*buffer="linux so easy!!\n";
  write(fd,buffer,strlen(buffer));
  close(fd);
  return 0;
}

                                                                 
