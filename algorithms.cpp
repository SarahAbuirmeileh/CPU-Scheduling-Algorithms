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


// Round Robin algorithm
pair<int, vector<PCB>> RR(int quantum, vector<PCB> processes, int context_switch) {
    int time = 0;
    setInitialTime(time, processes);
    
    deque<PCB> remain_processes(processes.begin(), processes.end());
    sortRR(remain_processes, time);
    vector<PCB> finished_processes;

    while (!remain_processes.empty()) {
        PCB current_process = remain_processes.front();
        remain_processes.pop_front();

        // Check if the remaining burst time is less than the quantum
        bool last_time = current_process.remainingBurst <= quantum;

        // Calculate the time for current process
        int process_time = last_time ? current_process.remainingBurst : quantum;

        // Process the current process
        time += process_time;
        current_process = processingInRR(time, current_process, processes, last_time, quantum);

        // Check if the process is finished
        if (current_process.remainingBurst <= 0) {
            finished_processes.push_back(current_process);
        } else {
            // Move the process to the end of the queue
            remain_processes.push_back(current_process);
        }

        if (context_switch != 0) {
            time += context_switch;
        }

        sortRR(remain_processes, time);
    }

    // Concatenate finished processes with remaining processes
    for (const auto &process : remain_processes) {
        finished_processes.push_back(process);
    }

    return {time, finished_processes};
}

// Shortest Remaining Time First 
pair<int, vector<PCB>> SRT(vector<PCB> processes, int context_switch = 0) {
    
    int time;
    setInitialTime(time, processes);
    
    vector<PCB> completed_processes;

    while (!processes.empty()) {
        sortSRT(processes, time);

        PCB& current_process = processes.front();

        if (current_process.arrivalTime > time) {
            time = current_process.arrivalTime;
        }

        if (!completed_processes.empty() && context_switch != 0) {
            time += context_switch;
        }

        processingInSRT(time, current_process, processes);

        current_process.remainingBurst--;
        time++;
        current_process.lastTimeInReady = time;

        if (current_process.remainingBurst <= 0) {
            completed_processes.push_back(current_process);
            processes.erase(processes.begin());
        }

    }

    return {time, completed_processes};
}


