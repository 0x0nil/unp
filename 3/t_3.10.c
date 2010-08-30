/*
 * 判断主机大小端的程序 ,16位整型的内存表示
 *          内存地址增大方向
 * -------------------------------->
 * +---------------+---------------+
 * |     0x1       |     0x2       |  big-endian
 * +---------------+---------------+
 * 
 * +---------------+---------------+
 * |    0x2        |    0x1        | little-endian
 * +---------------+---------------+
 *
 * */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc,char *argv[])
{
    union {
        short s;
        char c[sizeof(short)];
    }un;

    un.s = 0x0102;
    //    printf("%s: ",CPU_VENDOR_OS);
    if(sizeof(short) == 2)
    {
        if(un.c[0] == 1 && un.c[1] == 2)
            printf("big-endian\n");
        else if(un.c[0] == 2 && un.c[1] == 1)
            printf("little-endlian\n");
        else
            printf("unknow\n");
    }
    else
        printf("szieof(short) = %d\n",sizeof(short));
    exit(0);
}
