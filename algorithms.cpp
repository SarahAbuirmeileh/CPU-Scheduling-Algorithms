#include "PCB.h"
#include "PCBFuns.h"
#include <deque>

using namespace std;


// First Come First Serve Algorithm
pair<int, vector<PCB>> FCFS(vector<PCB> processes, int context_switch = 0){

    int time;
    setInitialTime(time, processes);

    sortOnArrivalTime(processes);
    for (PCB &current_process : processes){
        time += current_process.CPUBurst;
        processingInFCFS(time, current_process);
        if (context_switch != 0){
            time += context_switch;
        }
    }
    return {time, processes};
}

// Shortest Job First Algorithm
pair<int, vector<PCB>> SJF(vector<PCB> processes, int context_switch = 0){

    int time;
    setInitialTime(time, processes);

    deque<PCB> remain_processes(begin(processes), end(processes)); 
    while (!remain_processes.empty()){

        sortSJF(remain_processes, time);
        PCB current_process = remain_processes.front();
        remain_processes.pop_front();
        time += current_process.CPUBurst;

        processingInSJF(time, current_process, processes);
        if (context_switch != 0){
            time += context_switch;
        }
    }
    return {time, processes};
}