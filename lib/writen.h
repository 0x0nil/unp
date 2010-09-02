#ifndef _WRITEN_H_
#define _WRITEN_H_

/*
 * 图3-16 writen函数: 往一个描述符写n字节
 * */

ssize_t                      /* write "n" bytes to a descriptor */
writen(int fd,const void *vptr, size_t n);


#endif
