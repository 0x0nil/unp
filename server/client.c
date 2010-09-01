/*
 * 图27.4 用来测试各种服务的tcp客户程序
 * */

#include <stdio.h>

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
            fd = tcp_connect();
        }
    }
}
