#include <stdio.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM 2 // for Round Robin algorithm

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_by_arrival_time(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void fcfs(struct Process processes[], int n) {
    sort_by_arrival_time(processes, n);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        current_time = (current_time > processes[i].arrival_time) ? current_time : processes[i].arrival_time;
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        current_time = processes[i].completion_time;
    }

    printf("\nProcess\t\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

void sjf(struct Process processes[], int n) {
    sort_by_arrival_time(processes, n);

    int current_time = 0;
    int completed = 0;
    while (completed < n) {
        int min_index = -1;
        int min_burst = 99999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_burst && processes[i].remaining_time > 0) {
                min_index = i;
                min_burst = processes[i].remaining_time;
            }
        }
        if (min_index == -1) {
            current_time++;
            continue;
        }
        processes[min_index].remaining_time--;
        if (processes[min_index].remaining_time == 0) {
            completed++;
            processes[min_index].completion_time = current_time + 1;
            processes[min_index].waiting_time = processes[min_index].completion_time - processes[min_index].burst_time - processes[min_index].arrival_time;
            processes[min_index].turnaround_time = processes[min_index].waiting_time + processes[min_index].burst_time;
        }
        current_time++;
    }

    printf("\nProcess\t\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

void round_robin(struct Process processes[], int n) {
    int current_time = 0;
    int remaining_processes = n;

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                int time_slice = (processes[i].remaining_time >= TIME_QUANTUM) ? TIME_QUANTUM : processes[i].remaining_time;
                current_time += time_slice;
                processes[i].remaining_time -= time_slice;

                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                    processes[i].completion_time = current_time;
                    processes[i].waiting_time = current_time - processes[i].burst_time - processes[i].arrival_time;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                }
            }
        }
    }

    printf("\nProcess\t\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

void priority_scheduling(struct Process processes[], int n) {
    sort_by_arrival_time(processes, n);

    int current_time = 0;
    int completed = 0;
    while (completed < n) {
        int highest_priority = -1;
        int highest_priority_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }
        if (highest_priority_index == -1) {
            current_time++;
            continue;
        }
        processes[highest_priority_index].remaining_time--;
        if (processes[highest_priority_index].remaining_time == 0) {
            completed++;
            processes[highest_priority_index].completion_time = current_time + 1;
            processes[highest_priority_index].waiting_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].burst_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].turnaround_time = processes[highest_priority_index].waiting_time + processes[highest_priority_index].burst_time;
        }
        current_time++;
    }

    printf("\nProcess\t\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESSES];

    printf("Enter burst time, arrival time, and priority for each process:\n");
    for (int i = 0; i < n; ++i) {
        printf("Process %d:\n", i + 1);
        processes[i].id = i + 1;
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    printf("\nSelect scheduling algorithm:\n");
    printf("1. First-Come, First-Served (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("3. Round Robin (RR)\n");
    printf("4. Priority Scheduling (PS)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(processes, n);
            break;
        case 2:
            sjf(processes, n);
            break;
        case 3:
            round_robin(processes, n);
            break;
        case 4:
            priority_scheduling(processes, n);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
