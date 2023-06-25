#include <stdio.h>
#include <stdlib.h>

void heapify(int *A, int i, int heapSize){
    int l=2*i; //lewy syn
    int r = 2*i+1; //prawy syn
    int largest;
    if (l<=heapSize && A[l]>A[i]) {largest = l;}
    else largest=i;
    if(r<=heapSize && A[r]>A[largest]) {largest=r;}
    if(largest!=i){
        int temp = A[i];
        A[i]=A[largest];
        A[largest]=temp;
        heapify(A, largest, heapSize);
    }
}

int main(){

    FILE * file;
    int *heap, *heapTemp, size=0, input;
    heap=(int*)malloc(sizeof(int));
    file=fopen("plik.txt","r");
    if(file==NULL) perror("Blad pliku!");
    else{
        while(fscanf(file, "%d", &input)!=EOF){
            size++;
            heapTemp=(int*)realloc(heap,(size+1)*sizeof(int));
            if(heapTemp!=NULL){
                heap=heapTemp;
                heap[size]=input;
            }else{
                free(heap);
                printf("Error (realloc)\n");
            }
            printf("%d ",heap[size]);
        }
    }
    printf("\nHeap size: %d\n", size);
    heapify(heap, 1, size);
    for(int i=1; i<size+1; i++){
        printf("%d ", heap[i]);
    }
    free(heap);
    return 0;
}