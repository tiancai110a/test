#include<iostream>
#include<string>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
using namespace std;


int main(int argc, char *argv[])
{
    printf("client\n");

    int socketfd =socket(PF_INET,SOCK_STREAM,0);;
    sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr("192.168.199.143");
    addr.sin_family =AF_INET;
    addr.sin_port = htons(8080);
    socklen_t len = sizeof(addr);
    if( connect(socketfd,(sockaddr*)&addr,len) <0){
        printf("connect error");
        exit(0);
    }
    struct linger so_linger;
    so_linger.l_onoff = 1;
    so_linger.l_linger = 0;
//    int z = setsockopt(socketfd,
//        SOL_SOCKET,
//        SO_LINGER,
//        &so_linger,
//        sizeof so_linger);
    char buf[65535];
    while(scanf("%s",buf)!=EOF){
        if(buf[0]=='S'){
            close(socketfd);
            break;
        }
        int n;
        if( (n=send(socketfd,buf,strlen(buf),0)) <0){
          printf("send error!");
        }
        if(n==EOF){
            printf("n==EOF\n");
            exit(0);
        }
        if(n==0){
            printf("n==0\n");
        }
    }
printf("closing\n");
close(socketfd);
sleep(2);
    return 0;
}
