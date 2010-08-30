/*
 * 图3-15 readn函数: 从一个描述符读n字节
 * */

ssize_t    /* read "n" bytes from a desriptor. */
readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0)
    {
        if( (n = read(fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
                nread == 0;          /* and call read() again */
            else
                return -1;
        }
        else if (nread == 0)
            break;                   /* EOF */

        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft);              /* return >= 0 */
}
