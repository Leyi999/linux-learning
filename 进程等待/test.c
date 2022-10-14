#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
  pid_t id =fork();
  if(!id){
    //子进程//返回0
    while(1){
     printf("我是子进程！ 我的pid：%d，我的ppid：%d \n",getpid(),getppid());
     sleep(1);
    // int*p=NULL;
    // *p=100;//野指针 出现段错误 信号11
    // int err= 10/0;// 除0 出现浮点指针错误 信号8

    // 也可以自行 kill -信号 杀掉进程 
     }
    exit(104);//退出码
  }
  else if(id>0){
   //父进程//返回子进程的pid
   printf("我是父进程！ 我的pid：%d，我的ppid：%d \n",getpid(),getppid());
   int sta=0;
 //非阻塞等待
 //轮转问询
  pid_t ret=0;
  while(1 ){//错误写法 ret=waitpid(id,&sta,WNOHANG) 返回0无法进入循环
    ret=waitpid(id,&sta,WNOHANG);//正确写法 轮转问询
    if(ret>0){//等待成功
      if(WIFEXITED(sta)){//这个宏可以检查是否正常退出                                                                
           printf("等待成功，正常退出！ exit code: %d \n",WEXITSTATUS(sta)); //这个宏可以获取退出码                    
      }
      else{                                                                                                         
           printf("等待成功，异常退出！exit sig: %d\n",sta&0x7F);//信号要自己拿
         }
      break;
   }
   else if(ret==0){//子进程还没退出 
     printf("子进程还没退出 我父进程就去干其他事情拉！\n");
   }
      else{
        //错误 暂不处理
      }
    sleep(1);
  }
  }

 //阻塞等待
//   pid_t ret= waitpid(-1,&sta,0);//第一个参数是要等待的子进程pid 如果是-1 就代表等待任意一个子进程
//                                  //第二个为输出型参数 退出码或信号
//                                   //第三个为等待模式 0 为阻塞等待 WNOHANG 为非阻塞等待
//      if(ret>0){
//       // printf("等待成功： pid:%d  exit sig: %d exit code:%d  \n",ret,sta&0x7F,sta>>8&0xFF);//低七位和高八位表示退出码或者信号
//                                                                                            //如果正常退出那高八位就是0 没有0号信号
//      //位运算有学习成本 因此系统提供了宏
//       if(WIFEXITED(sta))//这个宏可以检查是否正常退出
//         printf("等待成功，正常退出！ exit code: %d \n",WEXITSTATUS(sta)); //这个宏可以获取退出码
//       else{
//         printf("等待成功，异常退出！exit sig: %d\n",sta&0x7F);//信号要自己拿
    
  else{
    //错误
    //do nothing
  }
  return 0;
}
