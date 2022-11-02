#include "comm.h"
using namespace std;
int main()
{
    //创建管道
    umask(0);
    mkfifo(fifo_path, 0666);
    //打开管道
    int fd = open(fifo_path, O_WRONLY);
    //写入需求
    while (1)
    {
        cout << "请输入:> ";
        cout.flush();
        char buffer[128];
        ssize_t buffer_ret = read(0, buffer, buffer_size);
        buffer[buffer_ret - 1] = 0; //消除'\n'
        if (strcmp(buffer, "_exit") == 0)
            break;
        ssize_t write_ret = write(fd, buffer, strlen(buffer));
    }
    //关闭管道
    close(fd);
    return 0;
}