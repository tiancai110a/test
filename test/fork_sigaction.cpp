#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

void fun(int sig){
   printf("hehe\n");
   int status;
   pid_t id = waitpid(-1,&status,WNOHANG);
   if(WIFEXITED(status)){
            printf("id:%d\n",id);
   }
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = fun;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD,&act,0);

    pid_t id =fork();
    if(id==0){
        sleep(5);
        printf("i'm child\n");
        exit(0);
    }
    else{
        int c=10;
        while(c--){
            printf("f:%d\n",c);
            sleep(2);
        }
    }
    return 0;
}
