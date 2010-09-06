#ifndef _READLINE_H_
#define _READLINE_H_

/*
 * 图3-18 readline函数的改进版
 * */

ssize_t
readline(int fd, void *vptr, size_t maxlen);

ssize_t
readlinebuf(void **vptrptr);

#endif
