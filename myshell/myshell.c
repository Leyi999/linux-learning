#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<ctype.h>
#include<sys/stat.h>
#include <fcntl.h>

#define NUM 1024
#define SUB 128
#define ENV_BUFFER 1024
char cmd_str[1024];//用于用户输入指令
char* sub_str[SUB];//用于分离指令和携带的选项
char env_buffer[ENV_BUFFER];//用于储存要增加的环境变量

#define DEL_SP(start) do{while(isspace(*start)) start++;}while(0)

enum redir{//表示重定向模式
  NONE,//不重定向
  OUT,//输出重定向
  APPEND,//追加
  IN,//输入
};

typedef struct redir_pair{//表示重定向模式的pair
    int _mode;//模式
    char* _path;//文件名
}redir_pair;

redir_pair check_redir(){
  redir_pair ret_pair;
  ret_pair._mode=0;//默认不重定向
  ret_pair._path=NULL;
  char*start=cmd_str;
    while(*start!='\0'){//寻找重定向符号
      if(*start=='>'){
        char*tmp=start;
        while(*start=='>'){ ret_pair._mode++;start++;}//区分是追加还是输出
        *tmp='\0';//重定向前的指令正常识别
        DEL_SP(start);//去掉空格
        ret_pair._path=start;//拿到文件名
        break;
      }
      if(*start=='<'){//输入 逻辑同上
        *start++='\0';
        ret_pair._mode=IN;
        DEL_SP(start);
        ret_pair._path=start;
        break;
      }
      start++;
    }
  return ret_pair;//返回模式和路径
}

int main(){
   //获取提示符信息
    char pwd[SUB];//用于获取当前路径
    memset(pwd,0,SUB);
    strcpy(pwd,getenv("PWD"));
    char*end=strtok(pwd,"/");
    char*cur_dir=0;//切割出当前目录
    while(end=strtok(NULL,"/")){
      cur_dir=end;
     }                                   
    while(1){ 
     //打印提示符
     printf("[%s@%s %s]$ ",getenv("USER"),getenv("HOSTNAME"),cur_dir);
     fflush(stdout);
     //用户输入指令
     memset(cmd_str,0,NUM);//每次输入前清空上一条指令
     fgets(cmd_str,NUM,stdin);//可能携带选项 所以需要按行读入 不能用scanf
     cmd_str[strlen(cmd_str)-1]=0;//将回车去掉
     //获取指令重定向信息
     redir_pair rp=check_redir(); 
     //分离指令和选项
     sub_str[0]=strtok(cmd_str," ");//拿到指令
     int i=1;//对ls 等指令增加默认选项
     if(!strcmp(sub_str[0],"ls"))
          sub_str[i++]="--color=auto";
     while(sub_str[i++]=strtok(NULL," ")){;}//拿到选项
     //针对内建指令
     if(!strcmp(sub_str[0],"cd")&&sub_str[1]){ //cd
       chdir(sub_str[1]);
       continue;
     }
     if(!strcmp(sub_str[0],"export")&&sub_str[1]){//增加环境变量
       strcpy(env_buffer,sub_str[1]);//因为每次sub_str会被修改 
       putenv(env_buffer);//环境变量需要一块独立的空间
       continue;
     }
     if(!strcmp(sub_str[0],"exit")&&!sub_str[1]){ //cd
       exit(0);
        }

     //...就不一一实现了
     //创建子进程
     pid_t id =fork();
     if(!id){
       //child
       //判断重定向
       umask(0);//设置权限掩码保证创建文件的正确性
       int fd=-1;//文件标识符
       //printf("mode: %d path:%s \n",rp._mode,rp._path);
       switch(rp._mode){//
         case NONE:
           break;
         case OUT:
             //printf("OUT\n");调试信息
             fd=open(rp._path,O_TRUNC|O_CREAT|O_WRONLY,0666);
             if(fd==-1){
               printf("打开文件出错！\n");
               exit(3);
             } 
             //printf("dup2 : %d %d \n",fd,1);
             dup2(fd,1);//使用系统调用将进程与底层打开文件的映射关系改变 实现重定向!
             break;
         case APPEND:
             //printf("APPEND\n");
             fd=open(rp._path,O_CREAT|O_WRONLY|O_APPEND,0666);//注意相关参数的正确!
             if(fd==-1){
               printf("打开文件出错！\n");
               exit(3);
             }
             //printf("dup2 : %d %d \n",fd,1);
             dup2(fd,1);
             break;
         case IN:
             //printf("IN\n");
             fd=open(rp._path,O_RDONLY);
             if(fd==-1){
               printf("打开文件出错！\n");
               exit(3);
             }
             //printf("dup2: %d %d \n",fd,0);
             dup2(fd,0);
             break;
         default:
           printf("bug?\n");
           break;

       }
       //程序替换
       execvp(sub_str[0],sub_str);
       //如果指令有误才会执行下面的语句
       printf("-myshell: %s: command not found\n",sub_str[0]);
       continue;
     }
     else if(id>0){
       //father
       int status=0;
       int ret=0;
       ret =waitpid(id,&status,0);//阻塞等待子进程
       if(ret){
          //调试信息
//         printf("等待成功 ");
//         if(WIFEXITED(status))
//            printf( "退出码：%d\n",(status>>8)&0xFF);
//         else 
//            printf("信号：%d\n",status&0x7F);
//
//         }
//       else{
//           printf("等待失败!\n");
//           exit(1);
//         }
      }
       else{
          printf("创建进程失败！\n");
          exit(2);
       } 
  } 
 }
} 


