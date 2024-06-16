#include"common.hpp"
// 自定义比较器，用于就绪队列，根据burstTime排序  
struct ComparePriority{  
    bool operator()(const PCB* lhs, const PCB* rhs) {  
        return lhs->priority > rhs->priority;  
    }  
};  
// 优先级调度算法  
class Priority_Scheduler {  
private:  
    std::priority_queue<PCB*, std::vector<PCB*>, ComparePriority> readyQueue;
  
public:  
    // 添加进程到就绪队列  
    void addProcess(int id, int prio, int burstTime) {  
        PCB* p = new PCB(id, burstTime);
        p->priority=prio;
        readyQueue.push(p);  
    }  
  
    // 模拟调度和执行进程  
    void simulate() {  
        if (readyQueue.empty()) {  
            std::cout << "就绪队列为空，无法进行调度。" << std::endl;  
            return;  
        }  
  
        int currentTime = 0; // 当前时间  
        std::vector<PCB*> processes; // 存放所有进程的副本，以便后续计算平均周转时间  
  
        while (!readyQueue.empty()) {  
            PCB* currentProcess = readyQueue.top(); // 取出就绪队列中优先级最高的进程  
            readyQueue.pop();  
  
            // 计算等待时间  
            currentProcess->wait_time = currentTime;  
  
            // 模拟进程执行  
            std::cout << "正在运行进程: " << currentProcess->pid << ", 优先级: " << currentProcess->priority  
                      << ", 执行时间: " << currentProcess->burst_time << " 秒" << std::endl;  
            currentTime += currentProcess->burst_time; // 更新当前时间  
  
            // 计算周转时间  
            currentProcess->turnaround_time = currentTime;  
  
            // 添加到所有进程列表以便后续计算平均周转时间  
            processes.push_back(currentProcess);  
  
            // 显示就绪队列  
            std::cout << "就绪队列: ";  
            if (!readyQueue.empty()) {  
                std::cout << "进程 " << readyQueue.top()->pid << " (优先级 " << readyQueue.top()->priority << ") ";  
            }  
            std::cout << "(*Ready)" << std::endl;  
        }  
  
        // 计算并显示平均周转时间  
        double totalTurnaround = 0.0;
        for (PCB* p : processes) {  
            totalTurnaround += p->turnaround_time;  //总时间
            std::cout << "进程 " << p->pid << " 的周转时间为: " << p->turnaround_time << " 秒" << std::endl;  
        }  
        std::cout << "平均周转时间为: " << totalTurnaround / processes.size() << " 秒" << std::endl;  
    }  
};  