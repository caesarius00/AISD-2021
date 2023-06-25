#include <stdio.h>
#include <string.h>
#include <time.h>
#define S 111
#define MAX_WORD_LENGTH 30
#define M 1031
#define MLD 1000000000.0



int getMax(int *T){
    int max=T[0];
    for(int i=0; i<M; i++) {
        if(T[i]>max) max=T[i];
    }
    return max;
}

double getAvg(int *T){
    double sum=0;
    double count=0;
    for(int i=0; i<M; i++) if(T[i]){
        sum+=T[i];
        count++;
    }
    if(sum) return sum/count;
    return 0.;
}

int h(char *T){

    int length=strlen(T);
    int conv=0;
    for(int i=length-1; i>-1; i--){
        int powerS=1;
        for(int j=0; j<length-i-1; j++){
            powerS*=S;
            
            //  skorzystałem z zaleznosci, ze (A+B)%m = A%m + B%m oraz (A*B)%m = A%m * B%m
            //  wiec skoro ostatecznie bede dodawal iloczyny znaków i potegi B, a następnie liczył modulo,
            //  to to samo wyjdzie, gdy od razu policzę modulo (nie chciałem wykraczać poza zakres inta)
            powerS=powerS%M;    
        }
        conv+=((int)*(T+i))*powerS;
    }
    return conv%M;
}

int main(){
    struct timespec begin, end;
    double totalTime;
    char input[MAX_WORD_LENGTH];
    int T[M];
    for(int i=0; i<M; i++){
        T[i]=0;
    }

    FILE *plik;
    plik=fopen("3700.txt","r");

    printf("Wartości h(k):\n\n");

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&begin);
    for(int i=0; fscanf(plik,"%s",input)!=EOF && i<M*2; i++){
        int value=h(input);
        printf("%d ", value);
        T[value]++;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&end);
    totalTime=(end.tv_sec+end.tv_nsec/MLD)-(begin.tv_sec+begin.tv_nsec/MLD);

    printf("\n\n\n");
    //for(int i=0; i<M; i++) printf("%d:%d ", i, T[i]);
    int countZeros=0;
    for(int i=0; i<M; i++) if(!T[i]) countZeros++;
    printf("Ilosc zerowych pozycji: %d\n", countZeros);
    printf("Wartosc maksymalna w T: %d\n", getMax(T));
    printf("Srednia wartosc pozycji niezerowych: %f\n\n", getAvg(T));
    printf("Czas: %lf\n",totalTime);

    return 0;
}


/*

I   - małe dane,potęga 2
    m = 64

    Ilosc zerowych pozycji: 8
    Wartosc maksymalna w T: 5
    Srednia wartosc pozycji niezerowych: 2.285714

    Czas: 0.000120

II  - małe dane, liczba pierwsza
    m = 61

    Ilosc zerowych pozycji: 8
    Wartosc maksymalna w T: 5
    Srednia wartosc pozycji niezerowych: 2.301887

    Czas: 0.000100


III - duże dane, potęga 2
    m = 1024
    
    Ilosc zerowych pozycji: 147
    Wartosc maksymalna w T: 9
    Srednia wartosc pozycji niezerowych: 2.335234

    Czas: 0.001701

IV  - duże dane, liczba pierwsza
    m = 1021
    
    Ilosc zerowych pozycji: 127
    Wartosc maksymalna w T: 7
    Srednia wartosc pozycji niezerowych: 2.284116

    Czas: 0.001399


*/