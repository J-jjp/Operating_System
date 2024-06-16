#include "common.hpp"
//时间片轮转调度算法
class RoundRobin_Scheduler {  
private:  
    std::queue<PCB*> readyQueue; // 就绪队列  
    int time_slice; // 时间片长度  
  
public:  
    RoundRobin_Scheduler(int slice) : time_slice(slice) {}  
  
    // 添加进程到就绪队列  
    void addProcess(int id, int burstTime) {
        PCB* p = new PCB(id, burstTime);
        p->remaining_time=burstTime;  
        readyQueue.push(p);  
    }  
  
    // 模拟调度和执行进程  
    void simulate() {  
        if (readyQueue.empty()) {  
            std::cout << "就绪队列为空，无法进行调度。" << std::endl;  
            return;  
        }  
  
        int currentTime = 0; // 当前时间  
        std::vector<PCB*> processes; // 存放所有进程的指针  
  
        while (!readyQueue.empty()) {  
            PCB* currentProcess = readyQueue.front(); // 取出就绪队列中的第一个进程  
            // 如果进程剩余时间大于0，则执行时间片长度的CPU时间
             if(currentProcess->remaining_time > 0) {  
                int timeToRun = std::min(currentProcess->remaining_time, time_slice);  
                currentProcess->remaining_time -= timeToRun;  
                currentTime += timeToRun;  
  
                // 模拟进程执行（输出）  
                std::cout << "正在运行进程: " << currentProcess->pid  
                          << ", 执行时间: " << timeToRun << " 秒, 剩余时间: "  
                          << currentProcess->remaining_time << " 秒" << std::endl;  
  
                // 如果进程未执行完，将其放回就绪队列尾部  
                if (currentProcess->remaining_time > 0) {  
                    readyQueue.push(currentProcess);
                    readyQueue.pop();  
                    currentProcess->wait_time += time_slice; // 累加等待时间  
                } else {  
                    readyQueue.pop();  
                }  
  
                // 如果就绪队列不为空，则输出下一个准备运行的进程ID  
                if (!readyQueue.empty()) {  
                    std::cout << "下一个准备运行的进程: P" << readyQueue.front()->pid << " (*Ready)" << std::endl;  
                }  
  
                // 进程执行完，计算周转时间  
                if (currentProcess->remaining_time == 0) {  
                    currentProcess->turnaround_time = currentTime;  
                    processes.push_back(currentProcess);  
                }  
            }  
        }  
  
        // 计算并显示平均周转时间  
        double totalTurnaround = 0.0;  
        for (PCB* p : processes) {  
            totalTurnaround += p->turnaround_time;  
            std::cout << "进程 " << p->pid << " 的周转时间为: " << p->turnaround_time << " 秒" << std::endl;  
        }  
        std::cout << "平均周转时间为: " << totalTurnaround / processes.size() << " 秒" << std::endl;  
  
        // 注意：这里省略了内存清理的代码（如delete进程对象）  
    }  
};  