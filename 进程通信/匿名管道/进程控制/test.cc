#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <ctime>
#include <random>

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
//一对一控制
// int main()
// {
//     //创建匿名管道
//     int fd[2]{0, 0};
//     if(pipe(fd)){
//         cout<<"创建管道失败！"<<endl;
//         exit(1);
//     }
//     //加载方法
//     lode_func();
//     pid_t id = fork();
//     if (id == 0)
//     {
//         // child
//         //关闭不需要的文件fd
//         close(fd[1]);
//         while (1)
//         {
//             char buffer[128];
//             //读取指令
//             ssize_t ret = read(fd[0], buffer, sizeof(buffer) - 1);
//             buffer[ret] = 0;
//             if (ret == 0)//代表父进程关闭了管道写端->读到了EOF -1
//             {
//                 cout << "任务读取完毕 子进程退出！" << endl;
//                 exit(0);
//             }
//             //估计这里还是深拷贝 效率或许不如c 的函数指针数组
//             auto it = fmap.find(string(move(buffer)));
//             if (it != fmap.end())
//                 (*it).second();
//             else
//                 cout<<"未找到命令对应的方法！"<<endl;
//         }
//     }
//     else if (id > 0)
//     {
//         // father
//         close(fd[0]);
//         string str;
//         do
//         {
//             str.clear();
//             cin >> str;
//             write(fd[1], str.c_str(), str.size());
//         } while (str != string("退出"));
//         close(fd[1]);
//         waitpid(id, nullptr, 0);
//         //...
//         cout<<"父进程等待成功! 程序退出"<<endl;
//         exit(0);
//     }
//     else
//     {
//         cout << "创建子进程出错！" << endl;
//         exit(2);
//     }
// }
//一对多控制
void work(int read_fd)
{
    while (1)
    {
        //阻塞等待读取指令
        char buffer[128];
        ssize_t ret = read(read_fd, buffer, sizeof(buffer) - 1);
        buffer[ret] = 0;
        if (ret == 0)
        {
            cout << "任务读取完毕 子进程退出！" << endl;
            return;
        }
        //获取方法
        unordered_map<string, function<void()>>::iterator it = fmap.find(buffer);
        cout << "子进程 " << getpid() << " 接收到<" << string(buffer) << ">"
             << "的任务 "
             << "即将查找并调用对应的方法..." << endl;
        //执行方法
        if (it != fmap.end())
            it->second();
        else
            cout << "bug:没有对应方法" << endl;
    }
}
void order(const vector<pair<pid_t, pid_t>> &infor_list)
{
    int order_num = 10;
    while (order_num--)
    {
        //建立随机数与字符串指令映射
        unordered_map<int, string> order_map{make_pair(1, "网络"), make_pair(2, "日志"), make_pair(3, "备份")};
        //生成随机指令
        string random_order(order_map[rand() % 3 + 1]);
        //随机指定子进程
        int random_index = rand() % infor_list.size();
        //写入指令
        cout << "给id:" << infor_list[random_index].first
             << "的子进程分配了<" << random_order << ">"
             << "的任务" << endl;
        write(infor_list[random_index].second, random_order.c_str(), random_order.size());
        sleep(1);
    }
}
int main()
{
    //使用随机数 下达随机命令给随机子进程来模拟场景
    srand(static_cast<unsigned int>(time(static_cast<time_t>(NULL))));
    //加载方法
    lode_func();
    int num = 5;
    //循环创建num个子进程
    //保存信息
    //用pair保存 子进程的pit 和 这个子进程接收命令的管道写入端的fd
    //子进程fd用于等待回收子进程资源 管道写入端fd用于部署任务
    vector<pair<pid_t, int>> infor_list;
    while (num--)
    {
        //为每个子进程都建立单向匿名管道
        int pfd[2]{0, 0};
        pipe(pfd);
        pid_t id = fork();
        if (id)
        {
            //父进程
            //保存子进程pid与管道写入端口
            infor_list.push_back(make_pair(id, pfd[1]));
            close(pfd[0]);
        }
        if (id == 0)
        {
            close(pfd[1]);
            //读取指令并执行对应方法
            work(pfd[0]);
            //管道写入端口关闭后退出
            close(pfd[0]);
            exit(0);
        }
    }
    //指派任务 此时子进程们在阻塞等待读取
    order(infor_list);
    //等待回收子进程
    cout << "已指派完所有任务，开始等待子进程回收..." << endl;
    for (const auto e : infor_list)
        //关闭管道写端 子进程读到EOF read 返回0
        close(e.second);
    int n = 0;
    while (n < infor_list.size())
    {
        waitpid(0, nullptr, 0);
        n++;
    }
    cout << "所有子进程已经退出，主进程退出！" << endl;
    return 0;
}