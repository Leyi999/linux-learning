#include"comm.h"
using namespace std;
int main(){
    //创建或者获取管道
    umask(0);
    int fifo_ret=mkfifo(fifo_path, 0666);//成功返回0 已经存在返回-1
    if(fifo_ret==-1&&errno!=EEXIST){
        cerr<<"创建获取管道失败！"<<endl;
        exit(1);
    }
    //打开管道
    int fd=open(fifo_path,O_RDONLY);
    if(fd<0){
        cerr<<"打开管道出错！"<<endl;
        exit(1);
    }
    //读取数据
    char buffer[128];
    while(ssize_t ret=read(fd,buffer,sizeof(buffer)-1)){
        if(ret<0){
            cerr<<"读取管道出错！"<<endl;
            exit(2);
        }
        buffer[ret]=0;
        //做出回应
        cout<<"服务器接收到："<<buffer<<endl;
        //...    
    }
    cout<<"客户端停止发送请求，程序退出！"<<endl;
    close(fd);
    return 0;
}