#pragma once  //一个头文件只被包含一次
#include <iostream>  
#include <list>  
#include <algorithm>
#include <string>
#include <functional>
#include <queue> 
//创建一个Process control block（进程控制块）的结构体
struct PCB {  
    int pid;  
    int burst_time; // 进程需要的CPU时间  
    int remaining_time; // 剩余需要CPU时间  
    int wait_time; // 等待时间  
    int turnaround_time; // 周转时间
    int priority; // 进程优先级  
    PCB(int id, int bt) : pid(id), burst_time(bt), wait_time(0), turnaround_time(0) {}
    int getRemainingTime() const {  
        return burst_time - (turnaround_time - wait_time);  
    }  
};
