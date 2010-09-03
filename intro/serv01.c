/*
 * 图27.5 tcp并发服务器main函数
 * */

#include <stdio.h>

int
main(int argc, char *argv[])
{
    int listenfd;
    int connfd;
    pid_t pid;
    void sig_child(int);
    void sig_init(int);
    void web_clild(int);

    socklen_t clilen;
    socklen_t addrlen;
    struct sockaddr *cliaddr;

    if(argc == 2)
        tcp_listen(NULL,argv[1],&addrlen);
}
