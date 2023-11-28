#include<stdio.h>
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int tat;
    int completion_time;
} PROCESS;

PROCESS p[25],temp;
int size;
void fcfs();
void sort();

int main(){
    printf("Enter the number of process : ");
    scanf("%d",&size);
    printf("Enter the process id ,arrival time and burst time \n");
    for(int i=0;i<size;i++){
        scanf("%d%d%d",&p[i].pid,&p[i].arrival_time,&p[i].burst_time);
    }
    fcfs();
}
void fcfs(){
    sort();
    int total_tat=0,total_wt=0;
    int completion_prev=0;
    for(int i =0;i<size;i++){
        if(p[i].arrival_time < completion_prev)
            p[i].completion_time = completion_prev + p[i].burst_time;
        else
            p[i].completion_time= p[i].arrival_time+ p[i].burst_time;

        p[i].tat = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time= p[i].tat - p[i].burst_time;
        total_tat+=p[i].tat ;
        total_wt +=  p[i].waiting_time;
        completion_prev= p[i].completion_time;
    }
    printf("\nProcess_id arrival_time burst_time waiting_time turnaround time\n");
    for(int i =0;i<size;i++){
        printf("\t%d\t%d\t\t%d\t%d\t  %d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].tat);
    }
    float avg_tat = (float)total_tat / size;
    float avg_wt = (float)total_wt / size;
    printf("Average_waiting_time : %.2f \n",avg_wt);
    printf("Average_turnaround_time : %.2f \n",avg_tat);
}
void sort(){
    int min_idx;
    for(int i =0;i<size-1;i++){
        min_idx=i;
        for(int j =i+1;j< size;j++)
            if( p[j].arrival_time <= p[min_idx].arrival_time)
                min_idx=j;
        if(i!=min_idx){
            temp = p[i];
            p[i] = p[min_idx];
            p[min_idx] = temp;
        }
    }
}
/*
Enter the number of process : 5
Enter the process id ,arrival time and burst time 
1 0 4
2 1 3
3 2 1
4 3 2 
5 4 5

Process_id arrival_time burst_time waiting_time turnaround time
        1       0               4       0         4
        2       1               3       3         6
        3       2               1       5         6
        4       3               2       5         7
        5       4               5       6         11
Average_waiting_time : 3.80 
Average_turnaround_time : 6.80 
*/
