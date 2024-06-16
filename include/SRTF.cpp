#include "common.hpp"
struct CompareRemainingTime {  
    bool operator()(const PCB* lhs, const PCB* rhs) {  
        return lhs->remaining_time > rhs->remaining_time;  
    }  
};  
// 短进程优先（SJF）调度器类  
class Shortest_remaining{  
private:  
    int currentTime = 0; // 当前时间  
  
public:  
    std::priority_queue<PCB*, std::vector<PCB*>, CompareRemainingTime> readyQueue; // 就绪队列
    std::vector<int> turnaround_times; // 周转时间列表  
    // 添加进程到就绪队列  
    void addProcess(int id, int burstTime) {  
        PCB* p = new PCB(id, burstTime);
        p->remaining_time=burstTime;    
        readyQueue.push(p);  
    }  
  
    // 执行SJF调度  
    void simulate() {  
        if (readyQueue.empty()) {  
            std::cout << "就绪队列为空，无法进行调度。" << std::endl;  
            return;  
        } 
        std::vector<PCB*> processes; // 存放所有进程的指针  
  
        if(!readyQueue.empty()) {  
            PCB* currentProcess = readyQueue.top();  
            readyQueue.pop();  
  
            currentProcess->wait_time = currentTime;  
  
            // 模拟进程执行  
            std::cout << "正在运行进程: " << currentProcess->pid << "剩余时间"<<currentProcess->remaining_time<<"秒" << std::endl;  
            currentTime ++; // 更新当前时间
            --currentProcess->remaining_time;
            // 如果进程还有剩余时间，则重新加入就绪队列  
            if (currentProcess->remaining_time > 0) {  
                readyQueue.push(currentProcess);  
            }
            if (currentProcess->remaining_time == 0) {  
                turnaround_times.push_back(currentTime);  
            std::cout << "进程 " << currentProcess->pid << " 的周转时间为: " << currentTime << std::endl;  
            }  
        }
        double totalTurnaround = 0.0;  
        if(!readyQueue.empty())             //判断这个队列是否为空
        {  
            // 显示就绪队列状态  
            std::cout << "就绪队列: "; 
            std::cout << readyQueue.top()->pid << " ";            //输出下一个进程的id
        }
        else{
            totalTurnaround = (double)currentTime / (double)turnaround_times.size();  
            std::cout << "平均周转时间: " << totalTurnaround << " 秒" << std::endl;  
        }  
        std::cout << "(*Ready)" << std::endl;  
    }  
};  
  