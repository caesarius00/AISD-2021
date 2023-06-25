#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*void heapify(int *A, int i, int heapSize){
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
}*/

//ITERACYJNIE-----------------------------
void heapify(int *A, int i, int heapSize){
    bool x;
    do{
        x=false;
        int l=2*i; //lewy syn
        int r = 2*i+1; //prawy syn
        int largest;
        if (l<=heapSize && A[l]>A[i]) largest = l;
        else largest=i;
        if(r<=heapSize && A[r]>A[largest]) largest=r;
        if(largest!=i){
            int temp = A[i];
            A[i]=A[largest];
            A[largest]=temp;
            x=true;
            i=largest;
        }
    }while (x);
}

void buildHeap(int *A, int *sizePtr, int length){
    *sizePtr=length;
    for(int i=length/2; i>0; i--){
        heapify(A, i, length);
    }
}

void heapSort(int *A, int *sizePtr, int length){
    buildHeap(A, sizePtr, length);
    *sizePtr=length;
    for(int i=length; i>1; i--){

        int temp=A[1];
        A[1]=A[*sizePtr];
        A[*sizePtr]=temp;
        (*sizePtr)--;
        heapify(A,1,*sizePtr);
    }
}

int main(){

    FILE * file;
    int *heap, *heapTemp, length=0, input;
    heap=(int*)malloc(sizeof(int));
    file=fopen("plik.txt","r");
    if(file==NULL) perror("Blad pliku!");
    else{
        while(fscanf(file, "%d", &input)!=EOF){
            length++;
            heapTemp=(int*)realloc(heap,(length+1)*sizeof(int));
            if(heapTemp!=NULL){
                heap=heapTemp;
                heap[length]=input;
            }else{
                free(heap);
                printf("Error (realloc)\n");
            }
            //printf("%d ", heap[length]);
        }
    }
    fclose(file);
    printf("Heap size: %d\n", length);
    //heapify(heap, 1, length);
    int heapSize = length;
    //buildHeap(heap, &heapSize, length);
    heapSort(heap, &heapSize, length);
    file=fopen("wynik.txt","w");
    for(int i=1;i<length+1;i++) fprintf(file,"%d ", heap[i]);
    free(heap);
    return 0;
}