#pragma once

#include "PCB.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <climits>
#include <fstream>

void readFromFile(string filePath, int processesNum, vector<PCB> &processes, int &contextSwitch, int &quantum){
    int id, arrivalTime, CPUBurst, size;

    ifstream fin;
    fin.open(filePath);

    fin >> contextSwitch >> quantum;
    contextSwitch /= 1000;
    for (int i=0; i<processesNum; i++){
        fin >> id >> arrivalTime >> CPUBurst >> size;
        PCB process = PCB(id, arrivalTime, CPUBurst, size);
        processes.push_back(process);
    }
    fin.close();
}

void calculateStatistics(vector<PCB> processes, int endOfProcessesTime, int processesNum){
    
    double AWT = 0; // average waiting time
    double ATAT = 0; // average turnaround time
    double CPUUtilizationRate = processes.size();
    double executionTime = 0;

    // Calculating the sums of the statistics to find the average
    for (PCB process : processes){
        ATAT += process.turnAroundTime;
        AWT += process.waitingTime;
        executionTime += process.CPUBurst;
    }

    CPUUtilizationRate = 1.0 * executionTime / endOfProcessesTime * 100.0;

    ATAT /= 1.0 * processesNum;
    AWT /= 1.0 * processesNum;

    cout << "\nResults:\n" 
         << "•" << " Average Waiting Time = " << AWT << endl
         << "•" << " Average Turnaround Time = " << ATAT << endl
         << "•" << " CPU Utilization Rate = " << CPUUtilizationRate << '%' << endl << endl;
}

// To set the initial time 0 or the time at which the first process arrives
void setInitialTime(int &time, vector<PCB> processes){
    time = INT_MAX; // Initialize time to a large value

    // Find the earliest arrival time
    for (const auto &process : processes) {
        time = min(time, process.arrivalTime);
    }

    if (time == INT_MAX) {
        time = 0;
    }
}

void printPCBInfo(vector<PCB> &processes){
    sort(begin(processes), end(processes),
         [](PCB a, PCB b) // Comparator function
         { return a.id <= b.id; });
    for (PCB process : processes){ // For each item in loop to print the PCB information for each process
        cout << "Process Id = " << process.id << '\n'
              << "-" <<  " Finish Time = " << process.finishTime << '\n'
              << "-" <<  " Waiting Time = " << process.waitingTime << '\n'
              << "-" <<  " Turnaround Time = " << process.turnAroundTime << endl << endl;
    }
}

// Sort processes according to their arrival time then according to id
void sortOnArrivalTime(vector<PCB> &processes){
    sort(begin(processes), end(processes),
         [processes](PCB a, PCB b){ // Comparator function to sort the vector in customized way
             if (a.arrivalTime != b.arrivalTime)
                 return (a.arrivalTime <= b.arrivalTime);
             else
                 return (a.id <= b.id);
         });
}

// To handle the processing of burst time in the FCFS
void processingInFCFS(int time, PCB &process){
    process.finishTime = time;
    process.turnAroundTime = process.finishTime - process.arrivalTime;
    process.waitingTime += (time - process.lastTimeInReady - process.remainingBurst);
    process.lastTimeInReady = time - process.remainingBurst;
    process.remainingBurst = 0;
    if (process.responseTime == -1)
        process.responseTime = process.lastTimeInReady - process.arrivalTime;
}

// Sort depends on CPU burst if the arrival time < current time
void sortSJF(deque<PCB> &d, int time){
    sort(begin(d), end(d),
        [time](PCB a, PCB b) {
            if (a.arrivalTime <= time && b.arrivalTime <= time)
                return a.CPUBurst <= b.CPUBurst;
            else if (a.arrivalTime <= time)
                return true;
            else if (b.arrivalTime <= time)
                return false;
            else
                return a.id <= b.id;
        });
}

// To handle the processing of burst time in the SJF ALG
void processingInSJF(int time, PCB &process, vector<PCB> &processes){
    
    int id = process.id;
    auto it = find_if(processes.begin(), processes.end(), [&id](const PCB& p) { return p.id == id; });
    int index = distance(processes.begin(), it);

    processes[index].finishTime = time;
    processes[index].turnAroundTime = processes[index].finishTime - processes[index].arrivalTime;
    if (processes[index].remainingBurst > 0) {
        processes[index].waitingTime += (time - processes[index].lastTimeInReady - processes[index].remainingBurst);
    } else {
        processes[index].waitingTime += (time - processes[index].lastTimeInReady);
    }
    processes[index].lastTimeInReady = time;
    processes[index].remainingBurst = 0;
    if (processes[index].responseTime == -1)
        processes[index].responseTime = processes[index].lastTimeInReady - processes[index].arrivalTime;
}

// Sort depends on id if the arrival time < current time
void sortRR(deque<PCB> &d, int time) {
    sort(d.begin(), d.end(),
        [time](const PCB &a, const PCB &b) {
            if (a.lastTimeInReady != b.lastTimeInReady)
                return a.lastTimeInReady < b.lastTimeInReady;
            else
                return a.arrivalTime < b.arrivalTime;
        });
}

// To handle the processing of burst time in the RR ALG
PCB processingInRR(int time, PCB &process, vector<PCB> &processes, bool lastTime, int quantum) {
    
    int currentWaitingTime = time - min(quantum, process.remainingBurst ) - process.lastTimeInReady;
    process.waitingTime += currentWaitingTime;
    
    // Update finish time and remaining burst time
    if (lastTime){
        process.finishTime = time;
    }

    process.remainingBurst -= quantum;
    process.lastTimeInReady = time;

    // Update response time if it's the first time in CPU
    if (process.responseTime == -1)
        process.responseTime = process.lastTimeInReady - process.arrivalTime;

    process.turnAroundTime = process.finishTime - process.arrivalTime;
    
    return process;
}

// Sort depends on cpu burst if the arrival time < current time
void sortSRT(vector<PCB> &processes, int time) {
    sort(processes.begin(), processes.end(),
        [time](const PCB& a, const PCB& b) {
            if (a.arrivalTime <= time && b.arrivalTime <= time)
                return a.remainingBurst < b.remainingBurst;
            else if (a.arrivalTime <= time)
                return true;
            else if (b.arrivalTime <= time)
                return false;
            else
                return a.id < b.id;
        });
}

// Function to handle processing of burst time in the SRT algorithm
void processingInSRT(int time, PCB &process, vector<PCB> &processes) {

    process.finishTime = time+1;
    process.turnAroundTime = process.finishTime - process.arrivalTime;

    if (process.responseTime == -1)
        process.responseTime = process.lastTimeInReady - process.arrivalTime;

    process.waitingTime += time  - process.lastTimeInReady;

}