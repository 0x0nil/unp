/*
 * 图11.8 tcp_listen函数：执行服务器程序的一般操作步骤
 * */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define LISTENQ    5

int
tcp_listen(const char *host,const char *serv,socklen_t *addrlenp)
{
    int listenfd;
    int n;
    const int on = 1;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *ressave;

    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((n = getaddrinfo(host,serv,&hints,&res)) != 0)
    {
        fprintf(stderr,"tcp_listen error for %s:%s\n",
                host,serv);
        exit(1);
    }

    ressave = res;

    do
    {
        listenfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
        if(listenfd < 0)
            continue;      /* error,try next one */

        setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
        if(bind(listenfd,res->ai_addr,res->ai_addrlen)  == 0)
            break;        /* success */

        close(listenfd);  /* bind error,close and try next one */
    }
    while((res = res->ai_next) != NULL);

    if(res == NULL)
    {
        fprintf(stderr,"tcp_listen error for %s:%s\n",host,serv);
        exit(1);
    }

    listen(listenfd,LISTENQ);

    if(addrlenp)
        *addrlenp = res->ai_addrlen;   /* return size of protocol address */

    freeaddrinfo(ressave);

    return listenfd;
}
