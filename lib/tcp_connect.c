/*
 * 图11.6 tcp_connect函数:执行客户程序的一般操作
 * */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int
tcp_connect(const char *host, const char *serv)
{
    int sockfd;
    int n;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *ressave;

    bzero(&hints,sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;


    if((n = getaddrinfo(host,serv,&hints,&res)) != 0)
    {
        fprintf(stderr,"tcp_connect error for %s,%s:%s\n",
                host,serv,gai_strerror(n));
        exit(1);
    }

    ressave = res;

    do
    {
        sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
        if(sockfd < 0)
            continue;

        if(connect(sockfd,res->ai_addr,res->ai_addrlen) == 0)
            break;
        close(sockfd);
    }
    while((res = res->ai_next) != NULL);

    if(res == NULL)
    {
        fprintf(stderr,"tcp_connect error for %s,%s\n",host,serv);
        exit(1);
    }

    freeaddrinfo(ressave);

    return sockfd;
}
