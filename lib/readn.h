#ifndef _READN_H_
#define _READN_H_

/*
 * 图3-15 readn函数: 从一个描述符读n字节
 * */

ssize_t    /* read "n" bytes from a desriptor. */
readn(int fd, void *vptr, size_t n);

#endif
