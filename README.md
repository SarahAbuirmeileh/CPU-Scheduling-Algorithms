# Process Scheduling Algorithms ⚙️💻
This repository contains C++ implementations of various process scheduling algorithms:

* First Come First Serve (FCFS)
* Shortest Remaining Time First (SRT)
* Round Robin (RR)
* Shortest Job First (SJF)


## Description 🎯
Each algorithm is implemented in its respective file. The main program, main.cpp, reads process information from input files, simulates the scheduling algorithms, and prints out the results.

## Files 🗂
* PCB.h: Defines the Process Control Block (PCB) structure used to represent individual processes.
* PCBFuns.h: Contains helper functions used in scheduling algorithms.
* algorithms.cpp: Contains implementations of the scheduling algorithms.
* main.cpp: The main program that orchestrates the simulation and prints results.
* processes/: Directory containing input files for different scheduling algorithms.


## How to Use 👩🏻‍💻
1. Compilation: Compile the program using a C++ compiler. For example: <br>
```g++ main.cpp -o scheduler```

2. Input Files: Prepare input files in the processes/ directory. Each input file should follow the format specified below: 
    ```php
    <context_switch_time> <quantum_time> 
    <process_id> <arrival_time> <CPU_burst_time> <size_in_bytes>
    ```
3. Execution: Run the compiled program, providing the number of processes as a command-line argument. For example:

4. Output: The program will display Gantt charts and various statistics for each scheduling algorithm.

## Input File Format 📑
Each input file should contain the following information:

* The first line specifies the context switch time and quantum time.
* Each subsequent line represents a process, with the following fields separated by spaces:
    * * Process ID
    * * Arrival time
    * * CPU burst time
    * * Size in bytes
* Example input file (FCFS.txt):

    ```yaml
    2 4
    1 0 8 1024
    2 1 6 512
    3 3 10 2048
    ```

## Output 💻
The program generates Gantt charts and calculates the following statistics for each scheduling algorithm:

* Average Waiting Time
* Average Turnaround Time
* CPU Utilization Rate