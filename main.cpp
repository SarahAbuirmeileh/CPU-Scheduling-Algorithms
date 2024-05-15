#include <iostream>
#include "algorithms.cpp"
#include "PCB.h"
#include "PCBFuns.h"


using namespace std;

int main(){

    vector<PCB> processes;
    pair<int, vector<PCB>> result ;
    int contextSwitch, quantum;

    readFromFile("processes/FCFS.txt", 3, processes, contextSwitch, quantum);
    result = FCFS(processes, contextSwitch);
    printPCBInfo(result.second);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

    readFromFile("processes/SRT.txt", 4, processes, contextSwitch, quantum);
    result = SRT(processes, contextSwitch);
    printPCBInfo(result.second);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;
    
    readFromFile("processes/RR.txt", 3, processes, contextSwitch, quantum);
    result = RR(quantum ,processes, contextSwitch);
    printPCBInfo(result.second);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

   readFromFile("processes/SJF.txt", 4, processes, contextSwitch, quantum);
    result = SJF(processes, contextSwitch);
    printPCBInfo(result.second);
    processes.clear();

    return 0;
}