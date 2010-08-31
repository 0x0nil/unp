/*
 * 图4.11 输出客户端ip地址和端口的时间/日期服务器
 * */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


#define MAXLINE     512

int
main(int argc,char *argv[])
{
    int listenfd;
    int connfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;

    char buff[MAXLINE];
    time_t ticks;

    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    char *ptr;
    int backlog = 5;
    if( (ptr = getenv("LISTENQ")) != NULL)
        backlog = atoi(ptr);
    if(listen(listenfd,backlog) < 0)
    {
        perror("listen");
        exit(1);
    }

    socklen_t len;
    for(; ;)
    {
        len = sizeof(cliaddr);
        if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len)) < 0)
        {
            perror("accept");
            exit(1);
        }
        printf("connection from %s,prot %d\n",
               inet_ntop(AF_INET,&cliaddr.sin_addr,buff,sizeof(buff)),
               ntohs(cliaddr.sin_port));

        ticks = time(NULL);
        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        if( (write(connfd,buff,strlen(buff))) < strlen(buff))
        {
            perror("write");
            exit(1);
        }

        close(connfd);
    }

    exit(0);
}
