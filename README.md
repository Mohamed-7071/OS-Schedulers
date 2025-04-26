📚 Project Description
This project simulates a mini Operating System that manages process execution, memory allocation, and resource access with scheduling algorithms and mutex locks. It interprets simple user programs, allocates memory dynamically, controls access to shared resources, and schedules processes efficiently.

The system provides a graphical interface for tracking processes, memory, resources, and scheduling behavior in real-time.

Developed as part of the second milestone for the Operating Systems course, Spring 2025.

🎯 Key Features
Interpreter for Custom Programs

Supports instructions like print, assign, readFile, writeFile, printFromTo, semWait, and semSignal.

Memory Management

Fixed size memory of 60 words.

Allocates space for program code, variables, and PCBs.

Process Management

Creates and manages Process Control Blocks (PCB) for every process.

Handles process states: Ready, Running, Blocked.

Scheduling Algorithms

First Come First Serve (FCFS)

Round Robin (RR) (with user-defined quantum)

Multilevel Feedback Queue (MLFQ)

Resource Management with Mutexes

Controls access to shared resources:

userInput (taking input from user)

userOutput (printing to screen)

file (reading/writing files)

Blocking and unblocking processes based on resource availability.

Graphical User Interface (GUI)

Displays process list, memory usage, queues, and logs.

Allows scheduling control (start, stop, reset).

Real-time updates per clock cycle.

Logging and Console Output

Execution logs, memory updates, event messages.

