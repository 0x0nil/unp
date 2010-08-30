/*
 * 图1-5 TCP时间获取客户程序
 * */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 521

int main(int argc,char *argv[])
{
    int sockfd,n;
    char recvline[MAXLINE +1];
    struct sockaddr_in servaddr;
    if(argc != 2)
    {
        perror("usage:a.out<IP address>");
        exit(0);
    }

    if((sockfd=socket(AF_INET,SOCK_STREAM,0)) <0)
    {
        perror("socket error");
        exit(0);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); /*daytime server */
    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <=0)
    {
        perror("inet_pton error");
        exit(0);
    }

    if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
    {
        perror("connect error");
        exit(0);
    }

    while( (n = read(sockfd,recvline,MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if(fputs(recvline,stdout) == EOF)
        {
            perror("fputs error");
            exit(0);
        }
    }
    if(n < 0)
    {
        perror("read error");
        exit(0);
    }

    exit(0);
}
