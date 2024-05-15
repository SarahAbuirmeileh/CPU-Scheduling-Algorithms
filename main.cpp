#include <iostream>
#include "algorithms.cpp"
#include "PCB.h"
#include "PCBFuns.h"


using namespace std;

int main(){

    PCB p1 = PCB(1, 0, 24, 12);
    PCB p2 = PCB(2, 0, 3, 12);
    PCB p3 = PCB(3, 0, 3, 12);

    vector<PCB> processes = {p1, p2, p3};

    pair<int, vector<PCB>> result = FCFS(processes, 0);
    printPCBInfo(result.second);
    
    // PCB p1 = PCB(1, 2, 6, 12);
    // PCB p2 = PCB(2, 2, 8, 12);
    // PCB p3 = PCB(3, 3, 7, 12);
    // PCB p4 = PCB(41, 3, 3, 12);

    // vector<PCB> processes = {p1, p2, p3, p4};

    // pair<int, vector<PCB>> result = SJF(processes, 0);
    // printPCBInfo(result.second);

    // PCB p1 = PCB(1, 0, 24, 12);
    // PCB p2 = PCB(2, 0, 3, 12);
    // PCB p3 = PCB(3, 0, 3, 12);

    // vector<PCB> processes = {p1, p2, p3};

    // pair<int, vector<PCB>> result = RR(4 ,processes, 0);
    //      printPCBInfo(result.second);

    return 0;
}