#include <stdio.h>
#include<stdlib.h>
// Define a Process struct to hold process information
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int scheduled_time; // New field to track scheduled time
    int completion_time; // New field to track completion time
} Process;

int main() {
    // Read process information from file
    FILE *file;
    file = fopen("process.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Declare variables
    int num_processes;
    fscanf(file, "%d", &num_processes);

    Process *processes = malloc(num_processes * sizeof(Process)); // Dynamic memory allocation
    if (processes == NULL) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return 1;
    }

    int quantum = 2; // Example time quantum

    // Read process information
    for (int i = 0; i < num_processes; i++) {
        fscanf(file, "%*s %d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = -1; // Initialize response time to -1
        processes[i].scheduled_time = -1; // Initialize scheduled time to -1
        processes[i].completion_time = -1; // Initialize completion time to -1
    }

    fclose(file);

    // Implement Round Robin algorithm
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < num_processes) {
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].remaining_time > 0 && current_time >= processes[i].arrival_time) {
                if (processes[i].scheduled_time == -1) {
                    // Update scheduled time only if it's the first time
                    processes[i].scheduled_time = current_time;
                    // Calculate response time as scheduled time - arrival time
                    processes[i].response_time = processes[i].scheduled_time - processes[i].arrival_time;
                }
                if (processes[i].remaining_time <= quantum) {
                    current_time += processes[i].remaining_time;
                    processes[i].completion_time = current_time; // Update completion time
                    processes[i].remaining_time = 0;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed_processes++;
                } else {
                    current_time += quantum;
                    processes[i].remaining_time -= quantum;
                }
            }
        }
    }

    // Calculate average waiting time, turnaround time, and response time
    float average_waiting_time = 0;
    float average_turnaround_time = 0;
    float average_response_time = 0;
    int total_completed_processes = 0; // Track total completed processes for averaging
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].completion_time != -1) { // Check if the process is completed
            total_completed_processes++;
            average_waiting_time += processes[i].waiting_time;
            average_turnaround_time += processes[i].turnaround_time;
            average_response_time += processes[i].response_time;
        }
    }
    // Calculate averages only if there are completed processes
    if (total_completed_processes > 0) {
        average_waiting_time /= total_completed_processes;
        average_turnaround_time /= total_completed_processes;
        average_response_time /= total_completed_processes;
    }

    // Write average waiting time, turnaround time, and response time to file
    file = fopen("waiting_turnaround_response_time_rr.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fprintf(file, "Average Waiting Time: %.2f\n", average_waiting_time);
    fprintf(file, "Average Turnaround Time: %.2f\n", average_turnaround_time);
    fprintf(file, "Average Response Time: %.2f\n", average_response_time);

    // Write process details to file
    fprintf(file, "\nProcess Details:\n");
    for (int i = 0; i < num_processes; i++) {
        fprintf(file, "Process %d:\n", processes[i].pid);
        fprintf(file, "Arrival Time: %d\n", processes[i].arrival_time);
        fprintf(file, "Burst Time: %d\n", processes[i].burst_time);
        fprintf(file, "Completion Time: %d\n", processes[i].completion_time);
        fprintf(file, "Turnaround Time: %d\n", processes[i].turnaround_time);
        fprintf(file, "Waiting Time: %d\n", processes[i].waiting_time);
        fprintf(file, "First Scheduling Time: %d\n", processes[i].scheduled_time);
        fprintf(file, "Response Time: %d\n", processes[i].response_time);
        fprintf(file, "\n");
    }
    fclose(file);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
