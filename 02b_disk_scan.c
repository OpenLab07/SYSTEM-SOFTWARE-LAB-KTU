#include<stdio.h>
#include<stdlib.h>

int head,u,l,n,D[20];
int head_mov = 0;

int indexof(int key){
    for(int i =0;i< n;i++)
        if(D[i]==key)
            return i;
}
void sort(){
    for(int i =0; i< n-1;i++){
        int min_idx = i;
        for(int j = i+1;j< n;j++)
            if(D[j]<=D[min_idx])
                min_idx =j;
        if(min_idx!=i){
            int temp = D[i];
            D[i] = D[min_idx];
            D[min_idx] = temp;
        }
    }
}
void scan(){
    D[n++] = head ;
    sort();
    D[n++] = u;
    int h_idx = indexof(head);
    printf("\nSeek sequence in scan : ");
    for(int i = h_idx;i<n;i++){
        head = D[i];
        printf("%d ",head);
        if(i<n-1)
            head_mov +=abs(D[i+1]-head);
    }

    for(int i=h_idx-1; i>=0;i--){
        printf("%d ",D[i]);
        head_mov += abs(D[i] - head);
        head = D[i];
    }
    printf("\nTotal head movement : %d ",head_mov);
}
int main(){
    printf("Enter the lower and upper limit of disk : ");
    scanf("%d%d",&l,&u);
    printf("Enter the number of requests : ");
    scanf("%d",&n);
    printf("Enter the requests : ");
    for(int i =0;i< n;i++)
        scanf("%d",&D[i]);
    printf("Enter the initial position of head :");
    scanf("%d",&head);
    scan();
}
/*
Enter the lower and upper limit of disk : 0 199
Enter the number of requests : 8
Enter the requests : 98 183 37 122 14 124 65 67
Enter the initial position of head :53

Seek sequence in scan : 53 65 67 98 122 124 183 199 37 14
Total head movement : 331
*/
