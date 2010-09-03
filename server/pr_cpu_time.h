#ifndef _PR_CPU_TIME_H_
#define _PR_CPU_TIME_H_

/*
 * 图27.7 pr_cpu_time 函数：输出总cpu时间
 * */

#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

#ifndef HAVE_GETRUSAGE_PROTO
int getrusage(int ,struct rusage *);
#endif

void
pr_cpu_time(void);

#endif
