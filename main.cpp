#include <iostream>
#include "algorithms.cpp"
#include "PCB.h"
#include "PCBFuns.h"


using namespace std;

int main(){

    vector<PCB> processes;
    pair<int, vector<PCB>> result ;
    int contextSwitch;

    readFromFile("processes/FCFS.txt", 3, processes, contextSwitch);
    result = FCFS(processes, contextSwitch);
    printPCBInfo(result.second);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

    readFromFile("processes/SRT.txt", 4, processes, contextSwitch);
    result = SRT(processes, contextSwitch);
    printPCBInfo(result.second);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;
    
    readFromFile("processes/RR.txt", 3, processes, contextSwitch);
    result = RR(4 ,processes, 0);
    printPCBInfo(result.second);
    processes.clear();

    cout << "------------------------------------------------------------" << endl << endl;

   readFromFile("processes/SJF.txt", 4, processes, contextSwitch);
    result = SJF(processes, 0);
    printPCBInfo(result.second);
    processes.clear();

    return 0;
}