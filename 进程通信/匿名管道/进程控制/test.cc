#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <functional>
#include <unordered_map>
#include <string>
using namespace std;
unordered_map<string, function<void()>> fmap; //方法集
void lode_func()
{ //加载方法
    fmap["日志"] = []
    {
        cout << "这是一个处理日志的方法！" << endl;
        //...
    };
    fmap["网络"] = []
    {
        cout << "这是一个处理网络的方法！" << endl;
        //...
    };
    fmap["备份"] = []
    {
        cout << "这是一个备份数据的方法！" << endl;
        //...
    };
}
int main()
{
    //创建匿名管道
    int fd[2]{0, 0};
    if(pipe(fd)){
        cout<<"创建管道失败！"<<endl;
        exit(1);
    }
    //加载方法
    lode_func();
    pid_t id = fork();
    if (id == 0)
    {
        // child
        //关闭不需要的文件fd
        close(fd[1]);
        while (1)
        {
            char buffer[128];
            //读取指令
            ssize_t ret = read(fd[0], buffer, sizeof(buffer) - 1);
            buffer[ret] = 0;
            if (ret == 0)//代表父进程关闭了管道写端->读到了EOF -1
            {
                cout << "任务读取完毕 子进程退出！" << endl;
                exit(0);
            }
            //估计这里还是深拷贝 效率或许不如c 的函数指针数组
            auto it = fmap.find(string(move(buffer)));
            if (it != fmap.end())
                (*it).second();
            else
                cout<<"未找到命令对应的方法！"<<endl;     
        }
    }
    else if (id > 0)
    {
        // father
        close(fd[0]);
        string str;
        do
        {
            str.clear();
            cin >> str;
            write(fd[1], str.c_str(), str.size());
        } while (str != string("退出"));
        close(fd[1]);
        waitpid(id, nullptr, 0);
        //...
        cout<<"父进程等待成功! 程序退出"<<endl;
        exit(0);
    }
    else
    {
        cout << "创建子进程出错！" << endl;
        exit(2);
    }
}