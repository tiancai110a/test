#include<stdio.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ioctl.h>
int main(){
  struct ifreq ifr;
  int socketfd = socket(AF_INET,SOCK_STREAM,0);
  memcpy(ifr.ifr_name,"ens33",sizeof(ifr.ifr_name));
  ioctl(socketfd,SIOCGIFADDR,&ifr);
  char *buf = inet_ntoa( ((sockaddr_in*)&ifr.ifr_addr)->sin_addr );
  printf("%s\n",buf);
}
