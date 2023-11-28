#include<stdio.h>
#include<stdlib.h>

int l,u,n,D[25];
int head, head_mov =0;
int indexof(int key){
    for(int i =0;i<n;i++)
        if(D[i]== key)
            return i;
}
int sort(){
    for(int i =0;i<n-1;i++){
        int min_idx = i;
        for(int j = i+1;j<n;j++){
            if(D[j]<=D[min_idx])
                min_idx = j;
        }
        if(i!=min_idx){
            int temp = D[i];
            D[i]= D[min_idx];
            D[min_idx] = temp;
        }
    }
}
void cscan(){
    D[n++] = l;
    D[n++] = head;
    D[n++] = u;
    sort();
    int h_idx = indexof(head);
    printf("Seek sequence in cscan : ");
    for(int i=h_idx; i !=h_idx-1;i=(i+1)%n){
        head = D[i];
        printf("%d ",head);
        head_mov += abs(D[(i+1)%n]- head); 
    }
    printf("%d\n",D[h_idx-1]);
    printf("Total head movements : %d",head_mov);
}
int main(){
    printf("Enter the lower and upper limit of disk: ");
    scanf("%d%d",&l,&u);
    printf("Enter the number of requests : ");
    scanf("%d",&n);
    printf("Enter the requests : ");
    for(int i =0; i< n ;i++)
        scanf("%d",&D[i]);
    printf("Enter the initial head position : ");
    scanf("%d",&head);
    cscan();
}
/*
Enter the lower and upper limit of disk: 0 199
Enter the number of requests : 8
Enter the requests :  98 183 37 122 14 124 65 67
Enter the initial head position : 53
Seek sequence in cscan : 53 65 67 98 122 124 183 199 0 14 37
Total head movements : 382

*/
