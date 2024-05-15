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
    result = FCFS(processes, contextSwitch);
    cout << "• First Come First Serve Algorithm (FCFS) •" << endl << endl;
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

    processesNum = 4;
    readFromFile("processes/SRT.txt", processesNum, processes, contextSwitch, quantum);
    result = SRT(processes, contextSwitch);
    cout <<"• Shortest Remaining Time First (SRT) •" << endl << endl;
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;
    
    processesNum = 3;
    readFromFile("processes/RR.txt", processesNum, processes, contextSwitch, quantum);
    result = RR(quantum ,processes, contextSwitch);
    cout <<"• Round Robin algorithm (RR) •" << endl << endl;
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

    processesNum = 4;
    readFromFile("processes/SJF.txt", processesNum, processes, contextSwitch, quantum);
    result = SJF(processes, contextSwitch);
    cout <<"• Shortest Job First Algorithm (SJF) •" << endl << endl;
    printPCBInfo(result.second);
    calculateStatistics(result.second, result.first, processesNum);
    processes.clear();

    return 0;
}