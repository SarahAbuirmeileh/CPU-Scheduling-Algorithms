#pragma once

using namespace std;

// This class for building the Process control Block (PCB) strucure
class PCB
{
public:

    // Process id
    int id;

    // The time that in which the process enter the ready queue for the first time
    int arrivalTime;

    // The total cpu burst of the process
    int CPUBurst;

    // Process size 
    int sizeInBytes;

    // The time in which the process finish the execution
    int finishTime;

    // The total time the process wait in the ready queue
    int waitingTime;

    // The total time from the request of the process until finish the execution
    int turnAroundTime;

    // The last time the process was in the ready queue, I use it for som calculations
    int lastTimeInReady;

    // The remaining cpu burst after some (zero or more) times in the cpu, I use it for som calculations
    int remainingBurst;

    // The time from the request of the process until first time enter the cpu
    int responseTime;

    // The methods of the PCB class
    PCB(int id, int arrivalTime, int CPUBurst, int sizeInBytes) // Constructor
    {
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->CPUBurst = CPUBurst;
        this->remainingBurst = CPUBurst; // At first time the process did not finish any burst 
        this->sizeInBytes = sizeInBytes;
        this->lastTimeInReady = arrivalTime;  // From this to the end will be changed while running the program
        this->finishTime = 0;
        this->waitingTime = 0;
        this->turnAroundTime = 0;
        this->responseTime = -1;
    }
};
