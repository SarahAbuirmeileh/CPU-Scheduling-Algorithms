#include "PCB.h"
#include "PCBFuns.h"

using namespace std;


// First Come First Serve Algorithm
pair<int, vector<PCB>> FCFS(vector<PCB> processes, int context_switch = 0){
    sortOnArrivalTime(processes);
    int time = 0;
    for (PCB &current_process : processes){
        time += current_process.CPUBurst;
        processingInFCFS(time, current_process);
        if (context_switch != 0){
            time += context_switch;
        }
    }
    return {time, processes};
}