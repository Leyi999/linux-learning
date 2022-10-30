#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;
int main()
{                     //创建管道
    int pfd[2]{0, 0}; //输出型参数
    if (pipe(pfd))    //返回0 成功 否则失败
    {
        cerr << "管道创建出错！" << endl;
        exit(1);
    }
    //创建子进程 管道以读和写分别打开一个管道内存文件 被子进程所继承
    // pfd[0] ->readonly
    // pfd[1] ->writeonly
    //管道是单向的（系统规定的） 创建子进程后各自关闭一个fd（根据需求）
    // 1.管道能单向通信
    // 2.如果写端关闭，读端能读到文件结尾EOF
    // 3.管道内自带访问控制机制：
    //    如果管道内没有文件，读端会阻塞等待；阻塞==>R->S/D/T ==>运行队列->等待队列
    //    如果管道写满了（通常是512字节），写段会阻塞等待。
    pid_t id = fork();
    if (id < 0)
    {
        cerr << "子进程创建出错！" << endl;
        exit(2);
    }
    if (id == 0)
    {
        // child 假设需求是子进程读 父进程写
        close(pfd[1]);
        char *buffer[128];
        while (1)
        {
            int ret = read(pfd[0], buffer, sizeof(buffer) - 1);
            if (ret < 0)
            {
                cerr << "读取管道文件出错！" << endl;
                exit(3);
            }
            if (ret > 0)
            {
                buffer[ret] = 0;
                printf("子进程接收到： %s\n",buffer);
            }
            else
            {
                cout << "读取完毕，子进程退出..." << endl;
                exit(0);
            }
        }
    }
    else
    {
        // father
        close(pfd[0]);
        int n = 5;
        while (n--)
        {
            char buffer[128];
            memset(buffer,128,0);
            sprintf(buffer, "你好子进程，我是父进程! 还剩%d条消息...\n");
            write(pfd[1], buffer, strlen(buffer)); //不用+1
            sleep(1);
        }
        close(pfd[1]); //子进程能读到文件结尾
        int status = 0;
        int wait_ret = waitpid(id, &status, 0);
        if (wait_ret)
        {
            cout << "等待子进程成功！";
            if (WIFEXITED(status))
                cout << "退出码：" << WEXITSTATUS(status);
            else
                cout << "推出信号：" << WTERMSIG(status);
        }
        cout << " 父进程退出..." << endl;
    }

    return 0;
}