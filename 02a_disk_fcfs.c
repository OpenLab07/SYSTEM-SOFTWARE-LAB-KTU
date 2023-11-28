#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,head ,disk_queue[20];
    int head_mov =0;
    printf("Enter the number of requests : ");
    scanf("%d",&n);
    printf("Enter the initial position of head : ");
    scanf("%d",&head);
    printf("Enter the requests : ");
    for(int i =0; i< n; i++)
        scanf("%d",&disk_queue[i]);
    printf("\nSeek sequenece in FCFS : %d ",head);
    for(int i =0;i<n;i++){
        printf("%d ",disk_queue[i]);
        head_mov+= abs(head - disk_queue[i]);
        head = disk_queue[i];
    }
    printf("\nTotal head movements : %d ",head_mov);
}
/*
Enter the number of requests : 8
Enter the initial position of head : 53
Enter the requests : 98 183 37 122 14 124 65 67


Seek sequenece in FCFS : 53 98 183 37 122 14 124 65 67 
Total head movements : 640 
*/
