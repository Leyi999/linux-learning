#pragma once
#include"log.hpp"
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define key_path "./"
#define key_id 06
#define shm_size 4096

key_t creat_key(const char* path= key_path,int id =key_id){
    key_t key= ftok(path,id);
    if(key==0){
        log()<<"生成key出错"<<std::endl;
        exit(1);
    }
    return key;
}