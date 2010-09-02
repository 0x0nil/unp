/*
 * 图27.4 用来测试各种服务的tcp客户程序
 * */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../lib/tcp_connect.h"

#define MAXN    16384

int
main(int argc, char *argv[])
{
    int i;
    int j;
    int fd;
    int nchildren;
    int nloops;
    int nbytes;
    pid_t pid;
    ssize_t n;
    char request[MAXN];
    char reply[MAXN];

    if(argc != 6)
    {
        perror("usege: client <hostname or ip> <port> <#children> "
               "<#loops/child> <#bytes/request>");
        exit(1);
    }

    nchildren = atoi(argv[3]);
    nloops = atoi(argv[4]);
    nbytes = atoi(argv[5]);
    snprintf(request,sizeof(request),"%d\n",nbytes);

    for(i=0; i<nchildren; i++)
    {
        if((pid = fork()) == 0)         /* child */
        {
            for(j=0; j<nloops; j++)
            {
                fd = tcp_connect(argv[1],argv[2]);

                write(fd,request, strlen(request));

                if((n = read(fd,reply,nbytes)) != nbytes)
                {
                    fprintf(stderr,"server returned %d bytes\n",n);
                    exit(1);
                }
                close(fd);    /* TIME_WAIT on client,not server */
            }
            printf("child %d done\n",i);
            exit(0);
        }
        /* parent loops around to fork() agian */
    }

    while(wait(NULL) >0)
        ;
    if(errno != ECHILD)
    {
        perror("wait error");
        exit(1);
    }
    exit(0);
}
