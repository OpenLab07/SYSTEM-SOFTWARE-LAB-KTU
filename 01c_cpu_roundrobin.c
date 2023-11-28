#include<stdio.h>
#include<stdbool.h>

struct process {
    int pid;
    int burst_time;
    int tat;
    bool isCompleted;
    int remain_time;
    int waiting_time;    
} p[20];
int size,time_quantum;

void round_robin_scheduling(){
    int one_more = size;
    int tat_prev = 0;
    for(int i =0;i< size;i++){
        p[i].isCompleted = false;
        p[i].remain_time = p[i].burst_time;
    }
        
    for(int i = 0;one_more > 0 ; i = (i+1)%size){
        if(p[i].isCompleted)
            continue;
       
            if(p[i].remain_time <= time_quantum){
                p[i].tat = tat_prev + p[i].remain_time;
                p[i].isCompleted = true;
                one_more--;
            }
            else{
                p[i].tat = tat_prev + time_quantum;
                p[i].remain_time -= time_quantum;
            }
        tat_prev =p[i].tat;
        p[i].waiting_time = p[i].tat - p[i].burst_time;
    }
    int total_tat =0 ,total_wt =0;
    for(int i =0;i<size;i++){
        total_tat += p[i].tat;
        total_wt += p[i].waiting_time;
    }
    float avg_tat = (float)total_tat / size;
    float avg_wt = (float)total_wt / size;
    printf("\nProcess_id burst_time waiting_time turnaround time\n");
    for(int i =0;i<size;i++)
        printf("\t%d\t%d\t%d\t  %d\n",p[i].pid,p[i].burst_time,p[i].waiting_time,p[i].tat);

    printf("Average turnaround time : %.2f\n",avg_tat);
    printf("Average waiting time : %.2f",avg_wt);
}

int main(){
    printf("Enter the number of process: ");
    scanf("%d",&size);
    printf("Enter the time_quantum : ");
    scanf("%d",&time_quantum);
    printf("Enter the process_id burst_time :\n");
    for(int i =0;i< size ;i++)
        scanf("%d%d",&p[i].pid,&p[i].burst_time);
    round_robin_scheduling();
}
/*
Enter the number of process: 5
Enter the time_quantum : 6
Enter the process_id burst_time :
1 21
2 18
3 12
4 30
5 15

Process_id burst_time waiting_time turnaround time
        1       21      63        84
        2       18      54        72
        3       12      36        48
        4       30      66        96
        5       15      66        81
Average turnaround time : 76.20
Average waiting time : 57.00
*/
