#include "ipc_header.hpp"
using namespace std;
int main()
{
    //key
    key_t key = creat_key();
    if (key < 0)
    {
        cout << "生成key失败" << endl;
        exit(5);
    }
    //get
    int shm_id = shmget(key, shm_size, IPC_CREAT);
    if (shm_id == -1)
    {
        log() << "获取共享内存失败 key: " << key << endl;
        exit(2);
    }
    else
        log() << "成功获取共享内存 shm_id: " << shm_id << endl;
    //attach
    void *shm = shmat(shm_id, nullptr, 0);
    if (shm == (void *)-1)
    {
        log() << "关联共享内存失败 shm_id:" << shm_id << endl;
        exit(3);
    }
    else
        log() << "成功关联共享内存！ shm_id:" << shm_id << endl;
    //use...
    sleep(5);
    //detach
    int dt_shm_ret =shmdt(shm);
    if (dt_shm_ret == -1)
    {
        log() << "去关联失败 shm_id:" << shm_id << endl;
        exit(3);
    }
    else
        log() << "去关联成功 shm_id:" << shm_id << endl;
}