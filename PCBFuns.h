#pragma once

#include "PCB.h"

#include <iostream>
#include <vector>
#include <algorithm>


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
    for (PCB process : processes){ // For each loop to print the PCB information for the current process
        cout << "Process Id = " << process.id << '\n'
              << "-" <<  " Finish Time = " << process.finishTime << '\n'
              << "-" <<  " Waiting Time = " << process.waitingTime << '\n'
              << "-" <<  " Turnaround Time = " << process.turnAroundTime << '\n\n';
    }
}
