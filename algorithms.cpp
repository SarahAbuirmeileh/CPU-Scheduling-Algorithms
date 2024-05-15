#include "PCB.h"
#include "PCBFuns.h"
#include <deque>
#include <iomanip>

using namespace std;


// First Come First Serve Algorithm
pair<int, vector<PCB>> FCFS(vector<PCB> processes, int context_switch = 0){

    int time;
    setInitialTime(time, processes);
    sortOnArrivalTime(processes);

    cout << "Gantt Chart for FCFS Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    " ;
    } 

    for (PCB &current_process : processes){
        int start_time = time;
        time += current_process.CPUBurst;
        cout << "|" << start_time << " P" << current_process.id << " ";

        processingInFCFS(time, current_process);
        if (context_switch != 0){
            time += context_switch;
            cout << " CS ";
            for (int t = time - context_switch; t < time; ++t) {
                cout << " ";
            }
            cout << " " << time;
        }
        lastEndTime = time;
    }
    cout << "|" << time << endl << endl;

    return {time, processes};
}

// Shortest Job First Algorithm
pair<int, vector<PCB>> SJF(vector<PCB> processes, int context_switch = 0){

    int time;
    setInitialTime(time, processes);
    deque<PCB> remain_processes(begin(processes), end(processes)); 

    cout << "Gantt Chart for SJF Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    " ;
    } 

    while (!remain_processes.empty()){

        sortSJF(remain_processes, time);

        PCB current_process = remain_processes.front();
        remain_processes.pop_front();

        int start_time = time;

        cout << "|" << start_time << " ";
        cout << "P" << current_process.id << " ";

        time += current_process.CPUBurst;
        lastEndTime = time;

        processingInSJF(time, current_process, processes);

        if (context_switch != 0){
            time += context_switch;
            cout << " CS ";
            for (int t = start_time + current_process.CPUBurst; t < time; ++t) {
                cout << " ";
            }
            cout << " " << time;
        }
    }
    cout << "|" << time << endl << endl;

    return {time, processes};
}

// Round Robin algorithm
pair<int, vector<PCB>> RR(int quantum, vector<PCB> processes, int context_switch) {
    int time = 0;
    setInitialTime(time, processes);
    
    deque<PCB> remain_processes(processes.begin(), processes.end());
    sortRR(remain_processes, time);
    vector<PCB> finished_processes;

    cout << "Gantt Chart for RR Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    ";
    }

    while (!remain_processes.empty()) {
        PCB current_process = remain_processes.front();
        remain_processes.pop_front();

        bool last_time = current_process.remainingBurst <= quantum;
        int process_time = last_time ? current_process.remainingBurst : quantum;

        int start_time = time;
        cout << "|" << start_time << " ";
        cout << "P" << current_process.id << " ";
        
        time += process_time;
        lastEndTime = time;
        current_process = processingInRR(time, current_process, processes, last_time, quantum);

        if (current_process.remainingBurst <= 0) {
            finished_processes.push_back(current_process);
        } else {
            // Move the process to the end of the queue
            remain_processes.push_back(current_process);
        }

        if (context_switch != 0) {
            time += context_switch;
            cout << " CS ";
            for (int t = start_time + process_time; t < time; ++t) {
                cout << " ";
            }
            cout << " " << time;
        }

        sortRR(remain_processes, time);
    }
    cout << "|" << time << endl << endl;

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

    cout << "Gantt Chart for SRT Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    ";
    }

    while (!processes.empty()) {
        sortSRT(processes, time);

        PCB& current_process = processes.front();

        if (current_process.arrivalTime > time) {
            time = current_process.arrivalTime;
        }

        int start_time = time;
        cout << "|" << start_time << " ";
        cout << "P" << current_process.id << " ";

        if (!completed_processes.empty() && context_switch != 0) {
            time += context_switch;
            cout << " CS ";
            for (int t = start_time; t < time; ++t) {
                cout << " ";
            }
            cout << " " << time;
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
    cout << "|" << time << endl << endl;

    return {time, completed_processes};
}


