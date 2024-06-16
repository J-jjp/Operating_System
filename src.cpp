#include"include/FCFS.cpp" //先来先服务（FCFS）算法
#include"include/SJF.cpp"   //短进程优先（SJF）算法
#include"include/RRS.cpp"   //时间片轮转调度算法（RRS）
#include"include/SRTF.cpp"  //最短剩余时间优先调度算法
#include"include/PS.cpp"
int main(int argc,char **argv) {
    if (argc < 2) {  
        std::cerr << "Usage: " << argv[0] << " <arg1>" << std::endl;  
        return 1; // 表示错误  
    }  
    std::string arg1(argv[1]); 
    if(arg1=="FCFS")           //先来先服务（FCFS）算法
    {
        FCFS_Scheduler scheduler;  
    
        // 创建并添加进程到就绪队列  
        scheduler.addProcess(1, 5);  
        scheduler.addProcess(2, 3);  
        scheduler.addProcess(3, 8);  
    
        // 模拟调度和执行进程  
        scheduler.simulate();  
    }
    else if(arg1=="SJF")              //短进程优先（SJF）算法
    {
        SJFScheduler scheduler;  
        
        // 添加进程到调度器  
        scheduler.addProcess(1, 6);  
        scheduler.addProcess(2, 8);  
        scheduler.addProcess(3, 7);  
        scheduler.addProcess(4, 3);  
    
        // 执行SJF调度  
        scheduler.simulate();
    }
    else if(arg1=="RRS")            //时间片轮转调度算法（RRS)
    {
        RoundRobin_Scheduler scheduler(2); // 设定时间片长度为2秒  
    
        scheduler.addProcess(1, 5); // 添加进程到就绪队列  
        scheduler.addProcess(2, 3);  
        scheduler.addProcess(3, 8);  
        scheduler.simulate(); // 模拟调度过程 
    }
    else if(arg1=="SRTF")   //最短剩余时间优先调度算法(SRTF)
    {
        Shortest_remaining Shortest;  
    
        // 添加一些进程到就绪队列  
        Shortest.addProcess(1, 5);  
        Shortest.addProcess(2, 6);  
        int n=0;   //计时器
        // 执行SJF调度模拟 
        while (!Shortest.readyQueue.empty())
        {
            if(n==2)
            Shortest.addProcess(3, 3);  
            Shortest.simulate();  
            n++;
        }
    }
        else if(arg1=="PS")  //优先级调度算法(priority Scheduling)
    {
        Priority_Scheduler scheduler;  
        scheduler.addProcess(1, 3, 6);  
        scheduler.addProcess(2, 1, 4);  
        scheduler.addProcess(3, 4, 3);  
        scheduler.simulate();  
    }
    return 0;  
}