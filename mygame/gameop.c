#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys//wait.h>
#include<stdio.h>
void menu(){
  printf("******************************\n");
  printf("*******1.猜数字游戏***********\n");
  printf("*******2.三子棋游戏***********\n");
  printf("*******3.扫雷游戏（高难）*****\n");
  printf("*******0. EXIT****************\n");
  printf("******************************\n");
}

int main(){
    int input=0;
    while(1){
    menu();
    printf("请选择： ");
    scanf("%d",&input);
    if(input ==0){
      printf("程序退出至终端...\n");
      return 0;
    }
    if(input<0||input>3){
      printf("输入错误！\n");
      sleep(1);
      continue;
    }
      //创建子进程
      pid_t id =fork();
      if(id==0){
        //child
      switch(input){   
         case 1:
               execl("./猜数字.out","./猜数字.out",NULL);
               printf("猜数字 -程序替换出错！\n");
               exit(3);
         case 2:    
               execl("./三子棋.out","./三子棋.out",NULL);
               printf("三子棋 -程序替换出错！\n");
               exit(4); 
         case 3:
               execl("./扫雷.out","./扫雷.out",NULL);
               printf("扫雷 -程序替换出错！\n");
               exit(5);
         default:
               printf("出现未知错误！\n");
               exit(6);
        }
      }
      else if(id <0){
        printf("创建子进程出错！\n");
        exit(1);
      }
      else{
        //father
        int status=0;
        int ret= waitpid(0,&status,0);//阻塞等待 //用ret接受等待结果
        if(ret){
          printf("返回中...\n");
          usleep(500000);
          printf("返回主菜单成功\n ");
//        if(WIFEXITED(status)){
//            printf("退出码：%d\n",WEXITSTATUS(status));
//           }
//        else 
//          printf("信号：%d\n",WTERMSIG(status));
        }
       else{
          printf("等待出错！\n");
          exit(2);
        } //等待成功返回子进程pid 非阻塞只用判断是否大于零           
      }
  }
}
