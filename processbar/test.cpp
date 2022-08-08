#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
int main(){
   const char* state="-\\|/";
    char *str =(char*)calloc(51,1);
    for(int p=0;p<=100;p++){
      str[p/2]='#';
      printf("[%-50s][%d%%][%c]\r",str,p,state[p/2%4]);
      fflush(stdout);
      usleep(50000);
    } 
    printf("\n");
    return 0;
}
