#pragma once

#include "PCB.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>


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
