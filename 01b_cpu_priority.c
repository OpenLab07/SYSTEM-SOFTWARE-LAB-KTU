#include<stdio.h>

struct process {
    int pid;
    int burst_time;
    int priority;
    int tat;
    int waiting_time;
} p[20],temp;
int size;

void sort(){
    int min_idx;
    for(int i=0; i<size-1;i++){
        min_idx = i;
        for(int j =i+1;j<size;j++)
            if(p[j].priority < p[min_idx].priority)
                min_idx = j;
        if(min_idx!=i){
            temp = p[i];
            p[i] = p[min_idx];
            p[min_idx]=temp;
        }
    }
}

void priority_scheduling(){
    sort();
    int tat_prev = 0;
    int total_tat =0,total_wt=0;
    for(int i =0;i<size ;i++){
        p[i].waiting_time = tat_prev;
        p[i].tat = p[i].waiting_time+ p[i].burst_time;
        tat_prev = p[i].tat;
        total_tat += p[i].tat;
        total_wt+=p[i].waiting_time;
    }
    float avg_tat = (float)total_tat / size;
    float avg_wt = (float)total_wt / size;
    printf("\nProcess_id priority burst_time waiting_time turnaround time\n");
    for(int i =0;i<size;i++){
        printf("\t%d\t%d\t%d\t%d\t\t%d\n",p[i].pid,p[i].priority,p[i].burst_time,p[i].waiting_time,p[i].tat);
    }
    printf("Average turnaround time : %.2f\n",avg_tat);
    printf("Average waiting time : %.2f",avg_wt);
}

int main(){
    printf("Enter the number of process :");
    scanf("%d",&size);
    printf("Enter the process_id  burst_time and  priority\n");
    for(int i=0;i<size;i++)
        scanf("%d%d%d",&p[i].pid,&p[i].burst_time,&p[i].priority);
    priority_scheduling();
}

/*
Enter the number of process :5
Enter the process_id  burst_time and  priority
1 10 3                 
2 1 1
3 2 4
4 1 5
5 5 2

Process_id priority burst_time waiting_time turnaround time
        2       1       1       0         1
        5       2       5       1         6
        1       3       10      6         16
        3       4       2       16        18
        4       5       1       18        19
Average turnaround time : 12.00
Average waiting time : 8.20

*/
