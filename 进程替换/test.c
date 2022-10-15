#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(){
  printf("程序开始执行了！ pid:%d\n",getpid());
  pid_t id= fork();
  if(id==0){
  //int ret=execl("/bin/ls","ls","-l",NULL);
  //execl("/bin/ls","ls","-l",NULL);//一般不需要接收返回值，当程序代码和数据被替换执行不到return语句
                                  //而若替换失败必然会接着执行后面的代码
  char *const arg[] ={(char*)"ls",(char*)"-l",(char*)NULL};//参数数组
  //execv("/bin/ls",arg);//execv 与 execl 只有传参方式不同 一个是数组传参一个是可变参数列表
  //execlp("ls","ls","-l",NULL);//这两个p代表环境变量path 是默认搜索路径不同
  //execvp
  char*const env[]={(char*)"MYENV=HEHEHEHE!!" };
  //execve 这个是唯一的系统调用 其他五个都是 封装的 最后都是调用它！
  // execvpe("ls",arg,env);//带e版本传递env是覆盖式的！但并不影响p版本的path路径 只是替换后的进程的环境变量被换成传入
  //正确的做法是 再外部 export 环境变量名 ="..." 添加至本地环境变量里
  //声明环境变量指针
  extern char** environ;
  //execle("/bin/ls","ls","-l",NULL,environ);//对应execvpe 但这个无法p 不能默认从PATH开始找
  execlp("./cpp_print","./cpp_print",NULL);//只要是可执行程序都可以替换
  // execlp("cpp_print","./cpp_print",NULL);//如果是p 那就不能用相对路径如 cpp_print  但是./cpp_print 算绝对路径
  
  //一共七个 
  //execl execv 在当前目录搜索 系统指令要用绝对路径 当前目录下的可以直接传程序名
  //execlp execvp 在PATH也就是系统指令所在的目录搜索 PATH路径下的可以直接传程序名 其他程序带路径 可以用./程序名
  //execle execve execvpe 表示自己维护环境变量(改用自己的传入的环境变量)
  //       只有execve是系统调用！也就是剩下六个它的封装 最后都是调它

  printf("调用execl后  pid:%d\n",getpid());//若调用成功 程序的代码数据都会被替换不会执行

  return 0;
  }
  int sta=0;
  int ret = waitpid(id,&sta,0);
  if(ret){
    printf("等待成功! ");
    if(WIFEXITED(sta))
      printf(" 退出码:%d \n",WEXITSTATUS(sta));
    else 
      printf(" 信号：%d \n",WTERMSIG(sta)) ;
    
  }
  else {
    printf("等待发生错误！\n");
  }
}
