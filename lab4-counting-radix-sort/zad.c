#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LENGTH 32
#define MLD     1000000000.0


int partition(char **A, int p, int r, char **A2){
    char *x=*(A+r);
    int i=p-1;
    for(int j=p; j<r+1; j++){
        //if(*(A+j)<=x)
        //printf("%d, ",strcmp(*(A+j), x));
        if(strcmp(*(A+j), x)<=0){
            i++;
            //printf("i=%d j=%d p=%d r=%d\n", i, j, p, r);
            char *temp;
            temp=malloc(MAX_LENGTH*(sizeof(char)));
            strcpy(temp, *(A+i));
            strcpy(*(A+i),*(A+j));
            strcpy(*(A+j),temp);

            strcpy(temp,*(A2+i));
            strcpy(*(A2+i),*(A2+j));
            strcpy(*(A2+j),temp);
            free(temp);
        }
    }
    if(i<r) return i;
    else return i-1;
}



void quicksort(char **A, int p, int r, char **A2){
    if(p<r){
        int q=partition(A, p, r, A2);
        quicksort(A, p, q, A2);
        quicksort(A, q+1, r, A2);
    }
}


void countingSort(char** A, int ADlugosc, char** B, int p, char **AData, char **BData, int *ALength, int *BLength){
    
    int C[27];
    for(int i=0; i<27; i++) C[i]=0;
    if(p){
        for(int i=0; i<ADlugosc; i++) C[A[i][p]-96]++;
        for(int i=1; i<27; i++) C[i]+=C[i-1];
        for(int i=ADlugosc-1; i>-1; i--){
            B[C[A[i][p]-96]-1]=A[i];
            BLength[C[A[i][p]-96]-1]=ALength[i];
            BData[C[A[i][p]-96]-1]=AData[i];
            C[A[i][p]-96]--;
        }
    }
    else{
        for(int i=0; i<ADlugosc; i++) C[A[i][p]-64]++;
        for(int i=1; i<27; i++) C[i]+=C[i-1];
        for(int i=ADlugosc-1; i>-1; i--){
            B[C[A[i][p]-64]-1]=A[i];
            BLength[C[A[i][p]-64]-1]=ALength[i];
            BData[C[A[i][p]-64]-1]=AData[i];
            C[A[i][p]-64]--;
        }
    }
    
    //zapisywanie adresów do tablicy A
    for(int i=0; i<ADlugosc; i++) {
        A[i]=B[i];
        AData[i]=BData[i];
        ALength[i]=BLength[i];
    }

}

void fullCountingSort(char **A, int ADlugosc, char **B, int max, char **AData, char **BData, int *ALength, int *BLength){
    for(int i=max-1; i>-1; i--)
        countingSort(A, ADlugosc, B, i, AData, BData, ALength, BLength);
}

int getLongest(int *length, int size){
    int max=0;
    for(int i=0; i<size; i++){
        if(length[i]>max)
            max=length[i];
    }
    return max;
}

void changeStrings(char **A, int ASize,int *length, int max, char toWhat){
    
    for(int i=0; i<ASize; i++){
        for(int j=length[i]; j<max; j++){
            A[i][j]=toWhat;
        }
        A[i][max]='\0';
    }
}


int main(){
    FILE *plik;
    char input[MAX_LENGTH];
    struct timespec begin, end;
    double totalTime;
    //plik=fopen("test.txt","r");
    plik=fopen("nazwiskaASCIImoje.txt","r");

    int count=0;
    char** stringArray, **numberArray, **B, **BNumbers;
    int *length, *BLength;
    length=malloc(sizeof(int));
    BLength=malloc(sizeof(int));
    stringArray = malloc(sizeof(char*));
    numberArray=malloc(sizeof(char*));
    B=malloc(sizeof(char*));
    BNumbers=malloc(sizeof(char*));
    for(; fscanf(plik,"%s", input)!=EOF; count++){
        if(count%2){
            stringArray=realloc(stringArray,(count/2+1)*sizeof(char*));
            length=realloc(length,(count/2+1)*sizeof(int));
            stringArray[count/2] = malloc(strlen(input)*sizeof(char));
            strcpy(stringArray[count/2], input);
            length[count/2]=strlen(input);
        }
        else{
            numberArray=realloc(numberArray,(count/2+1)*sizeof(char*));
            numberArray[count/2] = malloc(strlen(input)*sizeof(char));
            strcpy(numberArray[count/2], input);
        }
    }
    count-=count/2;
    B=realloc(B,(count+1)*sizeof(char*));
    BNumbers=realloc(BNumbers,(count+1)*sizeof(char*));
    BLength=realloc(BLength,(count+1)*sizeof(int));

    int choice;

    printf("\nM\tE\tN\tU\n\t1 - sortowanie pozycyjne\n\t2 - sortowanie przez porownanie (quicksort)\nPodaj sposob sortowania: ");
    scanf("%d", &choice);

    //dopasowywanie stringów, aby były tej samej długości
    int longest = getLongest(length, count);
    if(choice==1){
        changeStrings(stringArray, count, length, longest, '`');

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&begin);
        fullCountingSort(stringArray, count, B, longest,numberArray,BNumbers,length,BLength);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
        totalTime=(end.tv_sec+end.tv_nsec/MLD)-(begin.tv_sec+begin.tv_nsec/MLD);
        
        changeStrings(stringArray, count, length, longest, '\0');
        printf("Czas counting-sort: %lf", totalTime);
    }else if(choice==2){
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&begin);
        quicksort(stringArray, 0, count-1, numberArray);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
        totalTime=(end.tv_sec+end.tv_nsec/MLD)-(begin.tv_sec+begin.tv_nsec/MLD);

        printf("Czas quicksort: %lf", totalTime);
    }else printf("Nie ma takiego wyboru. Konczenie programu.\n");
    

    fclose(plik);
    plik=fopen("wynik.txt","w");
    for(int i=0; i<count; i++) fprintf(plik,"%s %s\n",numberArray[i], stringArray[i]);
    fclose(plik);

    free(stringArray);  //stringArray i B
    free(length);       //length
    free(BLength);      //BLength
    free(BNumbers);     //BNumbers i numberArray
    return 0;
}


/*


    Czas counting-sort: 0.025484

    Czas quicksort:     0.043069


*/