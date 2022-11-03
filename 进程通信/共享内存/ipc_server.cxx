#include "ipc_header.hpp"
using namespace std;
int main()
{
    //生成唯一值
    key_t key = creat_key();
    if (key < 0)
    {
        cout << "生成key失败" << endl;
        exit(5);
    }
    //创建共享内存
    int shm_id = shmget(key, shm_size, IPC_CREAT | IPC_EXCL | 0777); //保证是新申请的 //务必加上权限
    if (shm_id == -1)
    {
        log() << "共享内存已经存在 key: " << key << endl;
        exit(2);
    }
    else
        log() << "成功创建共享内存 shm_id: " << shm_id << endl;
    //产生关联
    void *shm = shmat(shm_id, nullptr, 0); //默认挂接位置 默认读写打开
    if (shm == (void *)-1)
    {
        log() << "关联共享内存失败 shm_id:" << shm_id << endl;
        exit(3);
    }
    else
        log() << "成功关联共享内存！ shm_id:" << shm_id << endl;
    //...
    sleep(10);
    //去关联
    int dt_shm_ret = shmdt(shm);
    if (dt_shm_ret == -1)
    {
        log() << "去关联失败 shm_id:" << shm_id << endl;
        exit(3);
    }
    else
        log() << "去关联成功 shm_id:" << shm_id << endl;
    //释放共享内存
    int del_shm_ret = shmctl(shm_id, IPC_RMID, nullptr);
    if (del_shm_ret == -1)
    {
        log() << "释放共享内存失败 shm_id: " << shm_id << endl;
        exit(4);
    }
    else
        log() << "释放共享内存成功 shm_id: " << shm_id << endl;
    return 0;
}