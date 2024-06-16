#include "common.hpp"  
// 自定义比较器，用于就绪队列，根据burstTime排序  
struct CompareBurstTime {  
    bool operator()(const PCB* lhs, const PCB* rhs) {  
        return lhs->burst_time > rhs->burst_time;  
    }  
};  
// 短进程优先（SJF）调度器类  
class SJFScheduler {  
private:  
    std::priority_queue<PCB*, std::vector<PCB*>, CompareBurstTime> readyQueue; // 就绪队列  
    /*std::queue 是一个标准的先进先出（FIFO）队列，它不支持自定义比较器来排序队列中的元素
    std::priority_queue 是一个标准库容器适配器，它提供队列的所有操作，但其中的元素总是按照特定的顺序进行排序
    */
  
public:  
    // 添加进程到就绪队列  
    void addProcess(int id, int burstTime) {  
        PCB* p = new PCB(id, burstTime);  
        readyQueue.push(p);  
    }  
  
    // 执行SJF调度  
    void simulate() {
        if (readyQueue.empty()) {  
            std::cout << "就绪队列为空，无法进行调度。" << std::endl;  
            return;  
        }  
  
        int currentTime = 0; // 当前时间  
        std::vector<PCB*> processes; // 存放所有进程的指针，以便后续计算平均周转时间  
        while (!readyQueue.empty()) {  
            PCB* currentProcess = readyQueue.top();  
            readyQueue.pop();  
            currentProcess->wait_time = currentTime;  
  
            // 模拟进程执行  
            std::cout << "正在运行进程: " << currentProcess->pid << ", 执行时间: " << currentProcess->burst_time << " 秒" << std::endl;  
            currentTime += currentProcess->burst_time; // 更新当前时间  
  
            // 计算周转时间  
            currentProcess->turnaround_time = currentTime;  
  
            // 添加到所有进程列表以便后续计算平均周转时间  
            processes.push_back(currentProcess);  
  
            // 显示就绪队列状态  
            std::cout << "就绪队列: "; 
            if(!readyQueue.empty())             //判断这个队列是否为空
             {  
                std::cout << readyQueue.top()->pid << " ";            //输出下一个进程的id
            }  
            std::cout << "(*Ready)" << std::endl;  
  
            // 如果有新的进程加入就绪队列（这里简化处理，实际中可能根据具体情况添加）  
  
        }
        // 计算并显示平均周转时间  
        double totalTurnaround = 0.0;  
        for (PCB* p : processes) {  
            totalTurnaround += p->turnaround_time;  //总时间
            std::cout << "进程 " << p->pid << " 的周转时间为: " << p->turnaround_time << " 秒" << std::endl;  
        }  
        std::cout << "平均周转时间为: " << totalTurnaround / processes.size() << " 秒" << std::endl;  //输出平均时间
    }  
};  