#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define C       3
#define SIZE    100000
#define MLD     1000000000.0

int partition(int *A, int p, int r){
    int x=*(A+r);
    int i=p-1;
    for(int j=p; j<r+1; j++){
        if(*(A+j)<=x){
            i++;
            int temp=*(A+i);
            *(A+i)=*(A+j);
            *(A+j)=temp;
        }
    }
    if(i<r) return i;
    else return i-1;
}



void quicksort(int *A, int p, int r){
    if(p+C<r){
        int q=partition(A, p, r);
        quicksort(A, p, q);
        quicksort(A, q+1, r);
    }
}

void insertionSort(int *A, int size){
    for(int i=2; i<size; i++){
        int insert = A[i];
        int j=i-1;
        while(j>0 && A[j]>insert){
            A[j+1]=A[j];
            j=j-1;
        }
        A[j+1]=insert;
    }
}

int main(){

    int arr[SIZE];
    struct timespec begin, end;
    double totalTime;

    //Dane losowe
    /*arr[0]=0;
    srand(time(NULL));
    for(int i=1; i<SIZE; i++){
        arr[i]=rand()%1000;
    }*/

    //dane niekorzystne
    for(int i=1; i<SIZE; i++){
        arr[i]=i;
    }
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&begin);

    quicksort(arr, 1, SIZE-1);
    insertionSort(arr, SIZE);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);

    totalTime=(end.tv_sec+end.tv_nsec/MLD)-(begin.tv_sec+begin.tv_nsec/MLD);

    printf("%lf\n", totalTime);
    return 0;
}



/*
testowane dla stałej c=3

~~~~~~~~~~dane LOSOWE (czasy)

    ROZMIAR     Quicksort       Quicksort+insertion
    10 000      0.004570        0.004027
    25 000      0.011135        0.014407
    50 000      0.024467        0.023133
    100000      0.059652        0.060768
    500000      0.734011        0.753116
    1000000     2.773527        2.737880

~~~~~~~~~~dane posortowane MALEJĄCO (czasy)

    ROZMIAR     Quicksort       Quicksort+insertion
    10 000      0.203230        0.177360
    25 000      1.122864        1.091391
    50 000      4.527175        4.241169
    100000      17.137458       17.190791

~~~~~~~~~~dane posortowane ROSNĄCO (czasy)

    ROZMIAR     Quicksort       Quicksort+insertion
    10 000      0.228991        0.265774
    25 000      1.348724        1.499913
    50 000      5.675953        5.591709
    100000      22.916696       22.227647

*/
