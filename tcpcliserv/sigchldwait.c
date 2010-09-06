/*
 * 图5.7 调用wait的SIGCHLD 信号处理程序
 * */

#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

void
sig_chld(int signo)
{
    pid_t pid;
    int stat;

    //pid = wait(&stat);
    while( (pid = waitpid(-1,&stat,WNOHANG)) >0)
        printf("chld %d terminated\n",pid);
    return;
}
