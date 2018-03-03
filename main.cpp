//
//  main.cpp
//  myThreadPool
//
//  Created by wb on 2018/3/3.
//  Copyright © 2018年 wb. All rights reserved.
//

#include "threadpool.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void* mytask(void *arg)
{
    printf("thread %d is working on task %d\n", (uintptr_t)pthread_self(), *(int*)arg);
    sleep(1);
    free(arg);
    return NULL;
}

//测试代码
int main(void)
{
    threadpool_t pool;
    //初始化线程池，最多三个线程
    threadpool_init(&pool, 3);
    int i;
    //创建十个任务
    for(i=0; i < 10; i++)
    {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        threadpool_add_task(&pool, mytask, arg);
        
    }
    threadpool_destroy(&pool);
    return 0;
}
