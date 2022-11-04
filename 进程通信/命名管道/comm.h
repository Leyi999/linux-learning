#pragma once
#include<cstring>
#include<cerrno>
#include<iostream>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
#include<cstdio>
#include<unistd.h>

//buffer size
#define buffer_size 1024

//隐藏文件
#define fifo_path "./.mypipe"