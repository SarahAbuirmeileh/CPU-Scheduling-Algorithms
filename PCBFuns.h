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

void calculateStatistics(vector<PCB> &v, int end_of_all_processes_time, int number_of_processes){
    
    double AWT = 0; // average waiting time
    double ATAT = 0; // average turnaround time
    double CPUUtilizationRate = v.size();
    double executionTime = 0;

    // Calculating the sums of the statistics to find the average
    for (PCB process : v){
        ATAT += process.turnAroundTime;
        AWT += process.waitingTime;
        executionTime += process.CPUBurst;
    }

    CPUUtilizationRate = 1.0 * executionTime / end_of_all_processes_time * 100.0;

    ATAT /= 1.0 * number_of_processes;
    AWT /= 1.0 * number_of_processes;

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
void processingInFCFS(int time, PCB &p){
    p.finishTime = time;
    p.turnAroundTime = p.finishTime - p.arrivalTime;
    p.waitingTime += (time - p.lastTimeInReady - p.remainingBurst);
    p.lastTimeInReady = time - p.remainingBurst;
    p.remainingBurst = 0;
    if (p.responseTime == -1)
        p.responseTime = p.lastTimeInReady - p.arrivalTime;
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
    // Loop to find the index of the process in the vector
    int id = process.id, index = -1;
    for (int i = 0; i < processes.size(); i++){
        if (id == processes[i].id){
            index = i;
            break;
        }
    }
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
PCB processingInRR(int time, PCB &process, vector<PCB> &processes, bool last_time, int quantum) {
    
    int current_waiting_time = time - min(quantum, process.remainingBurst ) - process.lastTimeInReady;
    process.waitingTime += current_waiting_time;
    
    // Update finish time and remaining burst time
    if (last_time){
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


void printPCBInfo(deque<PCB> &processes){
    // sort(begin(processes), end(processes),
    //      [](PCB a, PCB b) // Comparator function
    //      { return a.id <= b.id; });
    for (PCB process : processes){ // For each item in loop to print the PCB information for each process
        cout << "Process Id = " << process.id << '\n'
              << "-" <<  " Finish Time = " << process.finishTime << '\n'
              << "-" <<  " Waiting Time = " << process.waitingTime << '\n'
              << "-" <<  " Turnaround Time = " << process.turnAroundTime << endl << endl;
    }
}

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