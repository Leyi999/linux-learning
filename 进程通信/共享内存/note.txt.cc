//syscmd
ipcs -m  list out infos of all the shm whitch havent been free 
ipcs -m xxx list out the info of single shm if its havent been free 
ipcrm -m id del shm whichs id is "id";
//func
key_t ftok(path,id) use path and the id(like a secret signal) coders gave to creat a unique key
int shmget(key,size(byte),shmflg) 
    ->size better be the 4 的倍数 or size%4 bytes would waste
    ->shmflg : IPC_CREAT : if m dosent exsit creat one
        IPC_EXCL: use with IPC_CREAT if m dosent exsit return -1 and the errno whill be set
        mode : accsse mode of m   use as IPC_CREAT | IPC_EXCL |0666
    ->RET : shmid is returned ,-1 is returned if error occurs
    a prosses creat a shm doset mean it owns the shm 
    if a prosses want to use the shm ,it needs to get attach before and deattach after using(or automatically deattach when prosses exits );
void* shmat(int shmid,void* pos,int mode) -> shmat(shmid,nullptr, 0) return shm or -1
int shmdt(void* shm); return >0 or -1

int shmctl(id,cmd,shmid_ds*buf) 
    ->rm : shmctl(id,IPC_RMID,nullptr); usually use this to del shm but it can also be used to get shm info or do manythings else
    ->RET : 0 is returned , -1 is return if error occurs