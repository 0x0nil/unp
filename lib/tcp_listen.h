#ifndef _TCP_LISTEN_H_
#define _TCP_LISTEN_H_

/*
 * 图11.8 tcp_listen函数：执行服务器程序的一般操作步骤
 * */

int
tcp_listen(const char *host,const char *serv,socklen_t *addrlenp);

#endif
