/**
 * 函数inet_aton和函数inet_addr对于接受什么为点分十进制数IPv4地址串是
 * 相当随意的：允许是由小数点分隔的1～4个数，允许一个前导的0x来表示一个
 * 十六进制数，还允许一个前导的0表示一个八进制的数。
 * 函数inet_pton对IPv4地址要求则严格的多，它明确要求三个小数点来分隔四
 * 个数，每个数都是0～255之间的十进制数。当地址族为AF_INET6时。函数
 * inet_pton不允许指定点分十进制地址。
 * */

/**
 * 查看了netbsd中的inet_pton的源码，发现inet_pton的实现是由两个函数组成的 ，
 * inet_pton4 inet_pton6,根据inet_pton的第一个参数去判断调用哪一个函数，
 * 而其中inet_pton4的实现和inet_aton是一样的，即接受的点分十进制也是相当
 * 随意的。又看了一下gun libc 的实现，inet_pton也是那两个函数实现的，但
 * gun libc中的inet_pton4接受的参数就像题目中要求的一样，明确要求三个小数点
 * 分隔4个数，每个数都是十进制的。
 * 不同的系统实现不同，现在我还不能回答题目中的问题。
 * 猜想这中改变应该是考虑了格式种类太多的话会混乱，例如，使用127.0.0.010表示的
 * 是127.0.0.8，而127.0.0.08表示的是127.0.0.8，010表示的是0.0.0.8,0xe表示的是
 * 0.0.0.12,9.0xe表示的是9.0.0.14,9.020.0xe表示的是9.16.0.14。
 * 这样会比较乱，比较容易出错。改为统一格式会好点。这是我的想法，不知道个改变是基于
 * 什么样的想法。
 * */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
	char *ip_src = argv[1]?argv[1]:"127.0.0.010";
	printf("ip_src=%s\n",ip_src);
	struct in_addr addr;
	int ret;
	ret = inet_aton(ip_src,&addr);
	if(ret != 1)
		printf("inet_aton error %d\n",ret);
	char *ip_dst;
	ip_dst = inet_ntoa(addr);
	printf("test inet_aton:ip_dst=%s\n",ip_dst);
	
	ret = inet_pton(AF_INET,ip_src,&addr);
	if(ret != 0)
		printf("inet_pton error %d\n",ret);
	ip_dst = inet_ntoa(addr);
	printf("test inet_pton:ip_dst=%s\n",ip_dst);

	return 0;
}
