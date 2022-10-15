#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define NUM 1024
#define SUB_NUM 128
char cmd_arry[NUM];
char* sub_str[SUB_NUM];
int main(){
  while(1){
    //1.显示提示符 先不关系获取这些属性的系统调用
    printf("[hly@999-CentOS 当前目录]$");
    fflush(stdout);
    //2.用户输入
    memset(cmd_arry,'\0',NUM);//输入前初始化
    fgets(cmd_arry,NUM,stdin);
    cmd_arry[strlen(cmd_arry)-1]=0;//把用户输入的回车去掉
    //printf("%s\n",cmd_arry);//测试
    //3按空格分割出子串
    sub_str[0]=strtok(cmd_arry," ");//按空格分割出子串
    int index =1;
    while(sub_str[index++]=strtok(NULL," ")){ ; }
    //4 TODO ->内建命令
    //5 创建子进程 执行对应指令 
    pid_t id =fork();
    if(id==0){
      //child
      execvp(sub_str[0],sub_str);
      printf("-myshell: %s: command not found\n",sub_str[0]);
      _exit(1);
    }
    int status =0;
    int ret =waitpid(id,&status,0);
    if(ret){
   //   printf("等待成功！ ");
   //   if(WIFEXITED(status)){
   //     printf("退出码：%d\n",WEXITSTATUS(status));
   //   }
   //   else 
   //     printf("退出信号：%d\n",WTERMSIG(status));
      ;
    }
    else{
      printf("父进程等待出错！\n");
      _exit(2);
    }
  }
  return 0;
}

    
