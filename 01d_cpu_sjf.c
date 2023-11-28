#include<stdio.h>
struct process{
    int pid;
    int burst_time;
    int tat;
    int completion_time;
    int waiting_time;
} p[20],temp;
int size;

void sort(){
    int min_idx;
    for(int i=0 ;i< size-1 ;i++){
        min_idx = i;
        for(int j=i+1 ;j< size;j++)
            if(p[j].burst_time <= p[min_idx].burst_time)
                min_idx = j;
        if(min_idx!=i){
            temp  = p[i];
            p[i]   = p[min_idx];
            p[min_idx]=temp;
        }
    }
}
void sjf(){
    sort();
    int tat_prev = 0;
    int total_tat=0,total_wt=0;
    for(int i =0;i< size;i++){
        p[i].waiting_time = tat_prev;
        p[i].tat=p[i].waiting_time + p[i].burst_time;
        total_tat += p[i].tat;
        total_wt += p[i].waiting_time;
        tat_prev =p[i].tat;
    }
    float avg_tat = (float)total_tat / size;
    float avg_wt = (float)total_wt / size;
    printf("\nProcess_id burst_time waiting_time turnaround time\n");
    for(int i =0;i<size;i++){
        printf("\t%d\t%d\t%d\t  %d\n",p[i].pid,p[i].burst_time,p[i].waiting_time,p[i].tat);
    }
    printf("Average turnaround time : %.2f\n",avg_tat);
    printf("Average waiting time : %.2f",avg_wt);
}

int main(){
    printf("Enter the number of process :");
    scanf("%d",&size);
    printf("Enter the process id and burst time of processes\n");
    for(int i=0;i<size;i++)
        scanf("%d%d",&p[i].pid,&p[i].burst_time);
    sjf();
}

/*
Enter the number of process :5
Enter the process id and burst time of processes
1 45
2 32
3 21
4 67
5 89

Process_id burst_time waiting_time turnaround time
        3       21      0         21
        2       32      21        53
        1       45      53        98
        4       67      98        165
        5       89      165       254
Average turnaround time : 118.20
Average waiting time : 67.40

*/
