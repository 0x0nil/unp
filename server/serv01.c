/*
 * 图27.5 tcp并发服务器main函数
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <errno.h>
#include <signal.h>

#include "../lib/tcp_listen.h"
#include "pr_cpu_time.h"

int
main(int argc, char *argv[])
{
    int listenfd;
    int connfd;
    pid_t pid;
    void sig_chld(int);
    void sig_init(int);
    void web_clild(int);

    socklen_t clilen;
    socklen_t addrlen;
    struct sockaddr *cliaddr;

    if(argc == 2)
        tcp_listen(NULL,argv[1],&addrlen);
    else if(argc == 3)
        tcp_listen(argv[1],argv[2],&addrlen);
    else
    {
        fprintf(stdout,"usage:serv01 [<host>] <port#>\n");
        exit(1);
    }

    cliaddr = (struct sockaddr *)malloc(addrlen);
    if(cliaddr == NULL)
    {
        perror("malloc error");
        exit(1);
    }

    signal(SIGCHLD,sig_chld);
    signal(SIGINT,sig_int);

    for(; ;)
    {
        clilen = addrlen;

        if((connfd = accpt(listenfd,cliaddr,&clilen)) < 0)
        {
            if(errno == EINTR)
                continue;    /* back to for() */
            else
            {
                perror("accpt error");
                exit(1);
            }
        }

        if((childpid = fork()) == 0)
        {
            /* child process */
            close(listenfd);             /* close listening socket */
            web_child(connfd);           /* process the request */
            exit(0);
        }

        close(connfd);                  /* parent closes connected socket */
    }
}

void sig_int(int signo)
{
    void pr_cpu_time(void);
    pr_cpu_time();
    exit(0);
}
