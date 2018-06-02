#include<iostream>
#include<cassert>
#include<sys/epoll.h>
#include<thread>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string>
using namespace std;


//string spaceHtml= "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\
//        <html>\
//        <head>\
//          <meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\">\
//          <title>空白的网页</title>\
//        </head>\
//        <body>\
//           \
//        </body>\
//        </html>";
int main(){
   const int EPOLL_SIZE = 100;
   int listenfd =socket(PF_INET,SOCK_STREAM,0);
   sockaddr_in addr;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_family =AF_INET;
   addr.sin_port = htons(8080);
   bind(listenfd,(sockaddr*)&addr,sizeof(addr));



   int flag = fcntl(listenfd,F_GETFL,0);
   flag|= SO_REUSEADDR;
   flag|= SO_REUSEPORT;
   fcntl(listenfd,F_SETFL,flag);

    listen( listenfd,5);

   epoll_event ev;
   epoll_event *evs;
   evs = (epoll_event*)malloc(EPOLL_SIZE * sizeof(epoll_event));
   ev.data.fd = listenfd;
   ev.events = EPOLLIN;
   int epollfd = epoll_create(EPOLL_SIZE);
    epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&ev);


    while(1){
        int n = epoll_wait(epollfd,evs,EPOLL_SIZE,-1);
        for(int i =0;i<n;i++){
            if(evs[i].data.fd == listenfd){
                sockaddr_in peer;
                socklen_t len = sizeof(sockaddr_in);
                 int socketfd = accept(listenfd,(sockaddr*)&peer,&len);
                 int flag = fcntl(socketfd,F_GETFL,0);
                 flag|=O_NONBLOCK;
                 fcntl(socketfd,F_SETFL,flag);

                 epoll_event et;
                 et.data.fd = socketfd;
                 et.events = EPOLLIN|EPOLLOUT;
                 epoll_ctl(epollfd,EPOLL_CTL_ADD,socketfd,&et);
            }

            else if(evs[i].events & EPOLLIN){
                printf("heheh\n");
                char buf[65535];
                int n=0;
                n = read(evs[i].data.fd,buf,sizeof(buf)) ;

                if(n==0){
                    epoll_ctl(epollfd,EPOLL_CTL_DEL,evs[i].data.fd,&evs[i]);
                    close(evs[i].data.fd);
                    continue;
                }
                char*  p = buf+n;
                while( (n = read(evs[i].data.fd,p,65535-(p-buf))  ) >0){
                        p+=n;
                }
                p[0]='\0';
                string tmp ="HTTP/1.1 200 ok\r\n\r\nhaha\nhehe\r\n\r\n";

                printf("%s\n",buf);
                if(buf[0]=='G'&&buf[1]=='E'&&buf[2]=='T'){
                    write(evs[i].data.fd,tmp.c_str(),tmp.size());
                    epoll_ctl(epollfd,EPOLL_CTL_DEL,evs[i].data.fd,&evs[i]);
                    //close(evs[i].data.fd);
                    continue;
                }

            }
        }
    }


}
