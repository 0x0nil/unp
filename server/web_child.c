/*
 * 图27.8 处理每个客户请求的web_child函数
 * */

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>

#include "../lib/writen.h"
#include "../lib/readline.h"

#define MAXN   16384      /* max #bytes that a client can request */
#define MAXLINE   1024

void
web_child(int sockfd)
{
    int ntowrite;
    ssize_t nread;
    char line[MAXLINE];
    char result[MAXN];

    for(; ;)
    {
        if((nread = readline(sockfd,line,MAXLINE)) == 0)
            return;      /* connection closed by other end */
        /* line from client specifile #bytes to write back */
        ntowrite = atoi(line);
        if((ntowrite <= 0) || (ntowrite > MAXN))
        {
            fprintf(stderr,"client request for %d bytes",ntowrite);
            exit(1);
        }

        writen(sockfd,result,ntowrite);
    }
}
