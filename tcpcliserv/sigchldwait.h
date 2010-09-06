#ifndef _SIGCHLDWAIT_H_
#define _SIGCHLDWAIT_H_

/*
 * 图5.7 调用wait的SIGCHLD 信号处理程序
 * */

void
sig_chld(int signo);

#endif
