#include <iostream>
#include "algorithms.cpp"
#include "PCB.h"
#include "PCBFuns.h"

using namespace std;

int main(){

    vector<PCB> processes;
    pair<int, vector<PCB>> result ;
    int contextSwitch, quantum, processesNum;

    processesNum = 3;
    readFromFile("processes/FCFS.txt", processesNum, processes, contextSwitch, quantum);
    cout << "• First Come First Serve Algorithm (FCFS) •" << endl << endl;
    result = FCFS(processes, contextSwitch);
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

    processesNum = 4;
    readFromFile("processes/SRT.txt", processesNum, processes, contextSwitch, quantum);
    cout <<"• Shortest Remaining Time First (SRT) •" << endl << endl;
    result = SRT(processes, contextSwitch);
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;
    
    processesNum = 3;
    readFromFile("processes/RR.txt", processesNum, processes, contextSwitch, quantum);
    cout <<"• Round Robin algorithm (RR) •" << endl << endl;
    result = RR(quantum ,processes, contextSwitch);
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

    processesNum = 4;
    readFromFile("processes/SJF.txt", processesNum, processes, contextSwitch, quantum);
    cout <<"• Shortest Job First Algorithm (SJF) •" << endl << endl;
    result = SJF(processes, contextSwitch);
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    return 0;
}