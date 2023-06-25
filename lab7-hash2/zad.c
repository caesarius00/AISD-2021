#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 10000
#define LENGTH 24
#define PROCENT 0.9
#define S 111

typedef struct{
    int number;
    char string[LENGTH];
}dataType;


int h(char *T){

    int length=strlen(T);
    int conv=0;
    for(int i=length-1; i>-1; i--){
        int powerS=1;
        for(int j=0; j<length-i-1; j++){
            powerS*=S;
            powerS=powerS%SIZE;    
        }
        conv+=((int)*(T+i))*powerS;
    }
    return conv%SIZE;
}

int wstaw(dataType* dest, dataType src){
    int trials=0;
    int h1=h(src.string);

    //wydruk kontrolny dla malej tablicy
    //printf("h1=%d\n",h1);

    bool searching=true;
    for(; searching; trials++){
        if(!dest[(h1+trials)%SIZE].number){
            searching=false;
            dest[(h1+trials)%SIZE]=src;
        }
    }

    return trials;
}



int main(){

    dataType data[SIZE];
    dataType temp;
    FILE * plik;
    float sum=0;

    //ustawiam wartosci oznaczajace pusty element
    for(int i=0; i<SIZE; i++) {
        data[i].number=0;
        strcpy(data[i].string,"");
    }

    plik=fopen("nazwiskaASCIImoje.txt", "r");
    char input[LENGTH];
    for(int i=0; fscanf(plik, "%s", input)!=EOF && i<(SIZE*PROCENT)*2; i++){
        if(i%2==0){  //jesli numer
            temp.number=atoi(input);
        }else{
            strcpy(temp.string,input);
            sum+=wstaw(data,temp);

            //wydruk kontrolny dla małej tablicy
            /*
            printf("%d (Dodaje %s): \n", i/2, temp.string);
            for(int i=0; i<SIZE; i++){
                printf("|%d: %10d %23s|\n", i, data[i].number, data[i].string);
            }
            printf("\n\n");

            */

        }
    }
    fclose(plik);

    printf("Srednia z %.6g elementow, przy zapelnieniu tablicy %.6g%%: %.6g\n", SIZE*PROCENT, PROCENT*100, sum/(SIZE*PROCENT));

    return 0;
}

/*
----------------W Y N I K I----------------

Tablica rozmiar 1000:
    Srednia z 500 elementow, przy zapelnieniu tablicy 50%: 1.506
    Srednia z 700 elementow, przy zapelnieniu tablicy 70%: 2.17286
    Srednia z 900 elementow, przy zapelnieniu tablicy 90%: 4.72889

Tablica rozmiar 5000:
    Srednia z 2500 elementow, przy zapelnieniu tablicy 50%: 1.4984
    Srednia z 3500 elementow, przy zapelnieniu tablicy 70%: 2.26143
    Srednia z 4500 elementow, przy zapelnieniu tablicy 90%: 5.32022


Tablica rozmiar 10 000:
    Srednia z 5000 elementow, przy zapelnieniu tablicy 50%: 1.5264
    Srednia z 7000 elementow, przy zapelnieniu tablicy 70%: 2.24929
    Srednia z 9000 elementow, przy zapelnieniu tablicy 90%: 6.573

*/
