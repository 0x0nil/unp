/* *
 * 书里面的答案是指针必须按所读写的字节数增加，但c并不支持void指针的增加（因为
 * 编译器并不知道所指向的数据类型）。
 * 但我使用下面的代码试了一下，竟然是可以的，为什么？是标准未定义，而gcc自己实现
 * 的？还是其他原因？
 *
 * 在c程序设计语言中没找到相关的描述，在网上找到了和unp答案相符的描述
 * */

#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    char *a = "abcdefd";
    char *b = a;
    void *c = a;
    b++;
    c++;
    printf("%c,%c\n",*b,*(char *)c);
    b += 2;
    c += 2;
    printf("%c,%c\n",*b,*(char *)c);
    return 0;
}
