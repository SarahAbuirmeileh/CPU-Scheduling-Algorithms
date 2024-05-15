#include "PCB.h"
#include "PCBFuns.h"
#include <deque>
#include <iomanip>

using namespace std;


// First Come First Serve Algorithm
pair<int, vector<PCB>> FCFS(vector<PCB> processes, int contextSwitch = 0){

    int time;
    setInitialTime(time, processes);
    sortOnArrivalTime(processes);

    cout << "Gantt Chart for FCFS Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    " ;
    } 

    for (PCB &currentProcess : processes){
        int startTime = time;
        time += currentProcess.CPUBurst;
        cout << "|" << startTime << " P" << currentProcess.id << " ";

        processingInFCFS(time, currentProcess);
        if (contextSwitch != 0){
            time += contextSwitch;
            cout << " CS ";
            for (int t = time - contextSwitch; t < time; ++t) {
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
pair<int, vector<PCB>> SJF(vector<PCB> processes, int contextSwitch = 0){

    int time;
    setInitialTime(time, processes);
    deque<PCB> remainProcesses(begin(processes), end(processes)); 

    cout << "Gantt Chart for SJF Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    " ;
    } 

    while (!remainProcesses.empty()){

        sortSJF(remainProcesses, time);

        PCB currentProcess = remainProcesses.front();
        remainProcesses.pop_front();

        int startTime = time;

        cout << "|" << startTime << " ";
        cout << "P" << currentProcess.id << " ";

        time += currentProcess.CPUBurst;
        lastEndTime = time;

        processingInSJF(time, currentProcess, processes);

        if (contextSwitch != 0){
            time += contextSwitch;
            cout << " CS ";
            for (int t = startTime + currentProcess.CPUBurst; t < time; ++t) {
                cout << " ";
            }
            cout << " " << time;
        }
    }
    cout << "|" << time << endl << endl;

    return {time, processes};
}

// Round Robin algorithm
pair<int, vector<PCB>> RR(int quantum, vector<PCB> processes, int contextSwitch) {
    int time = 0;
    setInitialTime(time, processes);
    
    deque<PCB> remainProcesses(processes.begin(), processes.end());
    sortRR(remainProcesses, time);
    vector<PCB> finishedProcesses;

    cout << "Gantt Chart for RR Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    ";
    }

    while (!remainProcesses.empty()) {
        PCB currentProcess = remainProcesses.front();
        remainProcesses.pop_front();

        bool lastTime = currentProcess.remainingBurst <= quantum;
        int processTime = lastTime ? currentProcess.remainingBurst : quantum;

        int startTime = time;
        cout << "|" << startTime << " ";
        cout << "P" << currentProcess.id << " ";
        
        time += processTime;
        lastEndTime = time;
        currentProcess = processingInRR(time, currentProcess, processes, lastTime, quantum);

        if (currentProcess.remainingBurst <= 0) {
            finishedProcesses.push_back(currentProcess);
        } else {
            // Move the process to the end of the queue
            remainProcesses.push_back(currentProcess);
        }

        if (contextSwitch != 0) {
            time += contextSwitch;
            cout << " CS ";
            for (int t = startTime + processTime; t < time; ++t) {
                cout << " ";
            }
            cout << " " << time;
        }

        sortRR(remainProcesses, time);
    }
    cout << "|" << time << endl << endl;

    for (const auto &process : remainProcesses) {
        finishedProcesses.push_back(process);
    }

    return {time, finishedProcesses};
}

// Shortest Remaining Time First 
pair<int, vector<PCB>> SRT(vector<PCB> processes, int contextSwitch = 0) {
    int time;
    setInitialTime(time, processes);
    vector<PCB> completedProcesses;

    cout << "Gantt Chart for SRT Algorithm:" << endl;
    int lastEndTime = 0;

    if (time != 0) {
        cout << "|0    ";
    }

    while (!processes.empty()) {
        sortSRT(processes, time);

        PCB& currentProcess = processes.front();

        if (currentProcess.arrivalTime > time) {
            time = currentProcess.arrivalTime;
        }

        int startTime = time;
        cout << "|" << startTime << " ";
        cout << "P" << currentProcess.id << " ";

        if (!completedProcesses.empty() && contextSwitch != 0) {
            time += contextSwitch;
            cout << " CS ";
            for (int t = startTime; t < time; ++t) {
                cout << " ";
            }
            cout << " " << time;
        }

        processingInSRT(time, currentProcess, processes);

        currentProcess.remainingBurst--;
        time++;
        currentProcess.lastTimeInReady = time;

        if (currentProcess.remainingBurst <= 0) {
            completedProcesses.push_back(currentProcess);
            processes.erase(processes.begin());
        }
    }
    cout << "|" << time << endl << endl;

    return {time, completedProcesses};
}


