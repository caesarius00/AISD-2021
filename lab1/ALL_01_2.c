#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MLD 1000000000.0
/////////////////////////////////////////////
//   PROCEDURY POMOCNICZE                  //
/////////////////////////////////////////////
void utworz_MACIERZ(int n, int ***M){
// alokuje pamięć na tablicę rozmiaru nxn
// i wpisuje losowe wartości 0/1 
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=rand()% 2;
            }
    }
}
/////////////////////////////////////////////
void utworz_MACIERZ_x(int n, int ***M, int x){
// alokuje pami na tablicę rozmiaru nxn
// i wpisuje wszdzie wartości x
int i,j;
    (*M) = (int **)malloc(n*sizeof(int *));
    for(i=0;i<n;i++){
        (*M)[i]=(int *)malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            (*M)[i][j]=x;
            }
    }
}
/////////////////////////////////////////////
void wypisz_MACIERZ(int n, int **M){
// wypisuje wartości tablicy
int i,j;

for(i=0;i<n;i++){
    for(j=0;j<n;j++)
        printf("%d",M[i][j]);
    printf("\n");
    }
}
/////////////////////////////////////////////
void zwolnij_MACIERZ(int n, int **M){
// zwalania pamięć zarezerwowaną dla macierzy
int i;
    for(i=0;i<n;i++)
    {
    free(M[i]);
    }
    free(M);
}
/////////////////////////////////////////////
//   ALGORYTM PIERWSZY                     //
/////////////////////////////////////////////
int ALGO_NAIWNY(int n, int **M){
int x1,y1,x2,y2,x,y;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=n-1;x2>x1-1;x2--)
            for(y2=n-1;y2>y1-1;y2--){
                local_max=0;
                for(x=x1;x<x2+1;x++)
                    for(y=y1;y<y2+1;y++)
                        local_max+=M[x][y];
                if ((local_max==(x2-x1+1)*(y2-y1+1)) && (local_max>max)) max=local_max;
                }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM DRUGI                        //
/////////////////////////////////////////////
int REKURENCJA(int **M,int x1, int y1, int x2, int y2){
if ((x2==x1)&&(y2==y1)) return M[x1][y1];
    else if ((x2-x1)>(y2-y1))
        return REKURENCJA(M,x1,y1,(int)(x1+x2)/2,y2)*REKURENCJA(M,(int)(x1+x2+1)/2,y1,x2,y2);
            else return REKURENCJA(M,x1,y1,x2,(int)(y1+y2)/2)*REKURENCJA(M,x1,(int)(y1+y2+1)/2,x2,y2);
}
/////////////////////////////////////////////
int ALGO_REKURENCYJNY(int n, int **M){
int x1,y1,x2,y2;
int max=0;
int local_max;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++)
        for(x2=x1;x2<n;x2++)
            for(y2=y1;y2<n;y2++){
                local_max=REKURENCJA(M,x1,y1,x2,y2)*(x2-x1+1)*(y2-y1+1);
                if (local_max>max) max=local_max;
            }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM TRZECI                       //
/////////////////////////////////////////////
int ALGO_DYNAMICZNY(int n, int **M){
int x1,x2,y;
int max=0;
int iloczyn;
int **MM;

utworz_MACIERZ_x(n,&MM,0);

for(y=0;y<n;y++)
    for(x1=0;x1<n;x1++){
        iloczyn=1;
        for(x2=x1;x2<n;x2++){
            iloczyn*=M[x2][y];
            MM[x1][x2]=iloczyn*(x2-x1+1+MM[x1][x2]);
            if (MM[x1][x2]>max) max=MM[x1][x2];
        }
    }
return max;
}
/////////////////////////////////////////////
//   ALGORYTM CZWARTY                      //
/////////////////////////////////////////////
int ALGO_CZULY(int n, int **M){
int x1,y1,x2,y2,ymax;
int max=0;
int local_max=0;

for(x1=0;x1<n;x1++)
    for(y1=0;y1<n;y1++){
        local_max=0;
        x2=x1;
        ymax=n-1;
        while ((x2<n)&&(M[x2][y1]==1)){
            y2=y1;
            while((y2<ymax+1)&&(M[x2][y2]==1)){
                y2++;
            }
            ymax=y2-1;
            local_max=(x2-x1+1)*(ymax-y1+1);
            if (local_max>max) max=local_max;
            x2++;
        }
    }
return max;
}
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
int main(){
//int n=40; //wymiar macierzy/
int **Macierz;

struct timespec tp0, tp1;
double Tn, Fn;

srand(time(NULL));

//utworz_MACIERZ(n,&Macierz);
//utworz_MACIERZ_x(n,&Macierz,0);
//utworz_MACIERZ_x(n,&Macierz,1);
//wypisz_MACIERZ(n,Macierz);


for(int n=50; n<751; n+=50){   //dynamiczny i czuły
//for(int n=10; n<110; n+=10){ //naiwny i rekurencyjny

//utworz_MACIERZ(n,&Macierz);

//skrajne przypadki:
utworz_MACIERZ_x(n,&Macierz,0);
//utworz_MACIERZ_x(n,&Macierz,1);

//NAIWNY n^5*sqrt(n)
//Fn=n/1000.0*n*n*n*n*sqrt(n);

//REKURENCYJNY n^6
//Fn=n/1000.0*n*n*n*n*n; 

//DYNAMICZNY n^3
//Fn=n/1000.0*n*n;

//CZULY n^2 (w skrajnym n^4)
Fn=n/1000.0*n;
//Fn=n/1000.0*n*n*n;

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

printf("n=%3d | ", n);

//printf("Wynik 1=%d\t | ",ALGO_NAIWNY(n,Macierz));
//printf("Wynik 2=%d\t | ",ALGO_REKURENCYJNY(n,Macierz));
//printf("Wynik 3=%d\t | ",ALGO_DYNAMICZNY(n,Macierz));
printf("Wynik 4=%d\t | ",ALGO_CZULY(n,Macierz));



clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
printf("Wspolczynnik: %3.5lf | ", Fn/(Tn/1000.0));
printf("czas: %3.10lf \n", Tn);


zwolnij_MACIERZ(n,Macierz);

}

return 1;
}

/*
NAIWNY n^5 * sqrt(n) WYNIKI:--------------------------------------------------

MACIERZ 0:
n= 10 | Wynik 1=0        | Wspolczynnik: 862389186.49325 | czas: 0.0003666880 
n= 20 | Wynik 1=0        | Wspolczynnik: 1024344848.08218 | czas: 0.0139707200 
n= 30 | Wynik 1=0        | Wspolczynnik: 1894473054.92303 | czas: 0.0702551990 
n= 40 | Wynik 1=0        | Wspolczynnik: 2079418070.31765 | czas: 0.3114498590 
n= 50 | Wynik 1=0        | Wspolczynnik: 1916650655.49998 | czas: 1.1529011220 
n= 60 | Wynik 1=0        | Wspolczynnik: 1778784091.12077 | czas: 3.3861690860 
n= 70 | Wynik 1=0        | Wspolczynnik: 1660258339.49009 | czas: 8.4696126690

MACIERZ 1:
n= 10 | Wynik 1=100      | Wspolczynnik: 855053256.37134 | czas: 0.0003698340 
n= 20 | Wynik 1=400      | Wspolczynnik: 1111826263.16011 | czas: 0.0128714670 
n= 30 | Wynik 1=900      | Wspolczynnik: 1864547621.44373 | czas: 0.0713827740 
n= 40 | Wynik 1=1600     | Wspolczynnik: 2079936495.30815 | czas: 0.3113722300 
n= 50 | Wynik 1=2500     | Wspolczynnik: 1918029101.36324 | czas: 1.1520725570 
n= 60 | Wynik 1=3600     | Wspolczynnik: 1780240978.94216 | czas: 3.3833979620 
n= 70 | Wynik 1=4900     | Wspolczynnik: 1662647752.48966 | czas: 8.4574408770

MACIERZ LOSOWA:
n= 20 | Wynik 1=8        | Wspolczynnik: 1418864106.03230 | czas: 0.0100861210 
n= 30 | Wynik 1=8        | Wspolczynnik: 1868109558.10250 | czas: 0.0712466680 
n= 40 | Wynik 1=15       | Wspolczynnik: 2074773440.22185 | czas: 0.3121470770 
n= 50 | Wynik 1=15       | Wspolczynnik: 1917028558.67766 | czas: 1.1526738510 
n= 60 | Wynik 1=12       | Wspolczynnik: 1753569718.90863 | czas: 3.4348584120 
n= 70 | Wynik 1=18       | Wspolczynnik: 1625333579.33463 | czas: 8.6516055810 
n= 80 | Wynik 1=13       | Wspolczynnik: 1568546556.30468 | czas: 18.6851898510 
n= 90 | Wynik 1=12       | Wspolczynnik: 1486819119.36602 | czas: 37.6769435750 
n=100 | Wynik 1=16       | Wspolczynnik: 1434281882.65945 | czas: 69.7213017950 
n=110 | Wynik 1=16       | Wspolczynnik: 1366468232.44212 | czas: 123.6118848550

REKURENCYJNY (n^6) WYNIKI:---------------------------------------------------

MACIERZ 0:
n= 10 | Wynik 2=0        | Wspolczynnik: 732046736.79186 | czas: 0.0013660330 
n= 20 | Wynik 2=0        | Wspolczynnik: 1260996455.55570 | czas: 0.0507535130 
n= 30 | Wynik 2=0        | Wspolczynnik: 2045549097.57529 | czas: 0.3563835260 
n= 40 | Wynik 2=0        | Wspolczynnik: 2167470251.49990 | czas: 1.8897606540 
n= 50 | Wynik 2=0        | Wspolczynnik: 2133335687.68032 | czas: 7.3242106670 
n= 60 | Wynik 2=0        | Wspolczynnik: 2214058455.13570 | czas: 21.0726143620 

MACIERZ 1:
n= 10 | Wynik 2=100      | Wspolczynnik: 476533807.45270 | czas: 0.0020984870 
n= 20 | Wynik 2=400      | Wspolczynnik: 1174154288.31326 | czas: 0.0545073170 
n= 30 | Wynik 2=900      | Wspolczynnik: 2087389336.25976 | czas: 0.3492400710 
n= 40 | Wynik 2=1600     | Wspolczynnik: 2172095799.25857 | czas: 1.8857363480 
n= 50 | Wynik 2=2500     | Wspolczynnik: 2117620286.39500 | czas: 7.3785655060 
n= 60 | Wynik 2=3600     | Wspolczynnik: 2205065237.06559 | czas: 21.1585576770 
n= 70 | Wynik 2=4900     | Wspolczynnik: 2302524505.49751 | czas: 51.0956559720 

MACIERZ LOSOWA:
n= 10 | Wynik 2=7        | Wspolczynnik: 719109397.39352 | czas: 0.0013906090 
n= 20 | Wynik 2=6        | Wspolczynnik: 1401905741.90363 | czas: 0.0456521420 
n= 30 | Wynik 2=10       | Wspolczynnik: 2077808874.66886 | czas: 0.3508503640 
n= 40 | Wynik 2=16       | Wspolczynnik: 2140514515.38000 | czas: 1.9135586190 
n= 50 | Wynik 2=12       | Wspolczynnik: 2065992126.23599 | czas: 7.5629523470 
n= 60 | Wynik 2=12       | Wspolczynnik: 2214302739.13476 | czas: 21.0702896110 
n= 70 | Wynik 2=12       | Wspolczynnik: 2306895376.17696 | czas: 50.9988451210 
n= 80 | Wynik 2=15       | Wspolczynnik: 2263296846.54285 | czas: 115.8239584880

DYNAMICZNY n^3 --------------------------------------------------------------

MACIERZ 0:
n= 50 | Wynik 3=0        | Wspolczynnik: 150546544.17397 | czas: 0.0008303080 
n=100 | Wynik 3=0        | Wspolczynnik: 168980802.42900 | czas: 0.0059178320 
n=150 | Wynik 3=0        | Wspolczynnik: 218514122.09831 | czas: 0.0154452260 
n=200 | Wynik 3=0        | Wspolczynnik: 283554340.90328 | czas: 0.0282132870 
n=250 | Wynik 3=0        | Wspolczynnik: 353913844.30097 | czas: 0.0441491630 
n=300 | Wynik 3=0        | Wspolczynnik: 374532043.01958 | czas: 0.0720899600 
n=350 | Wynik 3=0        | Wspolczynnik: 383504211.48001 | czas: 0.1117979900 
n=400 | Wynik 3=0        | Wspolczynnik: 387356098.94932 | czas: 0.1652226470 
n=450 | Wynik 3=0        | Wspolczynnik: 363573911.80333 | czas: 0.2506367950 
n=500 | Wynik 3=0        | Wspolczynnik: 381543528.36138 | czas: 0.3276166170 
n=550 | Wynik 3=0        | Wspolczynnik: 386603110.43981 | czas: 0.4303509090 
n=600 | Wynik 3=0        | Wspolczynnik: 379359865.03753 | czas: 0.5693802110 
n=650 | Wynik 3=0        | Wspolczynnik: 389710304.94771 | czas: 0.7046901160 
n=700 | Wynik 3=0        | Wspolczynnik: 375697411.18448 | czas: 0.9129687610 
n=750 | Wynik 3=0        | Wspolczynnik: 387746922.61708 | czas: 1.0880163720

MACIERZ 1:
n= 50 | Wynik 3=2500     | Wspolczynnik: 130528399.84713 | czas: 0.0009576460 
n=100 | Wynik 3=10000    | Wspolczynnik: 144114479.93119 | czas: 0.0069389280 
n=150 | Wynik 3=22500    | Wspolczynnik: 293180618.80656 | czas: 0.0115116750 
n=200 | Wynik 3=40000    | Wspolczynnik: 301329900.68355 | czas: 0.0265489750 
n=250 | Wynik 3=62500    | Wspolczynnik: 333284337.86939 | czas: 0.0468818910 
n=300 | Wynik 3=90000    | Wspolczynnik: 382738862.85902 | czas: 0.0705441820 
n=350 | Wynik 3=122500   | Wspolczynnik: 374424528.05786 | czas: 0.1145090580 
n=400 | Wynik 3=160000   | Wspolczynnik: 336745634.72819 | czas: 0.1900544310 
n=450 | Wynik 3=202500   | Wspolczynnik: 386277506.93254 | czas: 0.2359055300 
n=500 | Wynik 3=250000   | Wspolczynnik: 382077977.72594 | czas: 0.3271583480 
n=550 | Wynik 3=302500   | Wspolczynnik: 385097644.46760 | czas: 0.4320332840 
n=600 | Wynik 3=360000   | Wspolczynnik: 387994714.25460 | czas: 0.5567086150 
n=650 | Wynik 3=422500   | Wspolczynnik: 388242644.52627 | czas: 0.7073540320 
n=700 | Wynik 3=490000   | Wspolczynnik: 386300763.12443 | czas: 0.8879091960 
n=750 | Wynik 3=562500   | Wspolczynnik: 374442058.69960 | czas: 1.1266763180 

MACIERZ LOSOWA:
n= 50 | Wynik 3=14       | Wspolczynnik: 149541565.37718 | czas: 0.0008358880 
n=100 | Wynik 3=18       | Wspolczynnik: 162080202.14643 | czas: 0.0061697850 
n=150 | Wynik 3=16       | Wspolczynnik: 264227537.25373 | czas: 0.0127730820 
n=200 | Wynik 3=16       | Wspolczynnik: 249963200.73004 | czas: 0.0320047110 
n=250 | Wynik 3=18       | Wspolczynnik: 324982594.45221 | czas: 0.0480794980 
n=300 | Wynik 3=21       | Wspolczynnik: 342526108.22800 | czas: 0.0788261080 
n=350 | Wynik 3=22       | Wspolczynnik: 382512678.36600 | czas: 0.1120877880 
n=400 | Wynik 3=18       | Wspolczynnik: 367661587.45439 | czas: 0.1740731210 
n=450 | Wynik 3=18       | Wspolczynnik: 378727989.48258 | czas: 0.2406080420 
n=500 | Wynik 3=20       | Wspolczynnik: 372565605.29352 | czas: 0.3355113790 
n=550 | Wynik 3=20       | Wspolczynnik: 373374357.78152 | czas: 0.4455983560 
n=600 | Wynik 3=21       | Wspolczynnik: 382541859.24447 | czas: 0.5646440900 
n=650 | Wynik 3=20       | Wspolczynnik: 375266173.88874 | czas: 0.7318138940 
n=700 | Wynik 3=24       | Wspolczynnik: 376662961.34636 | czas: 0.9106284270 
n=750 | Wynik 3=24       | Wspolczynnik: 390201313.27199 | czas: 1.0811726810


CZUŁY n^2-------------------------------------------------------------------

MACIERZ 0:
n= 50 | Wynik 4=0        | Wspolczynnik: 50966321.45478 | czas: 0.0000490520 
n=100 | Wynik 4=0        | Wspolczynnik: 118500260.70057 | czas: 0.0000843880 
n=150 | Wynik 4=0        | Wspolczynnik: 129171522.55909 | czas: 0.0001741870 
n=200 | Wynik 4=0        | Wspolczynnik: 127858026.44743 | czas: 0.0003128470 
n=250 | Wynik 4=0        | Wspolczynnik: 132413571.01393 | czas: 0.0004720060 
n=300 | Wynik 4=0        | Wspolczynnik: 167723948.74356 | czas: 0.0005365960 
n=350 | Wynik 4=0        | Wspolczynnik: 182623759.27654 | czas: 0.0006707780 
n=400 | Wynik 4=0        | Wspolczynnik: 138499719.10526 | czas: 0.0011552370 
n=450 | Wynik 4=0        | Wspolczynnik: 187281678.11782 | czas: 0.0010812590 
n=500 | Wynik 4=0        | Wspolczynnik: 164280870.34691 | czas: 0.0015217840 
n=550 | Wynik 4=0        | Wspolczynnik: 270333309.80019 | czas: 0.0011189890 
n=600 | Wynik 4=0        | Wspolczynnik: 318329970.23615 | czas: 0.0011309020 
n=650 | Wynik 4=0        | Wspolczynnik: 312250799.84243 | czas: 0.0013530790 
n=700 | Wynik 4=0        | Wspolczynnik: 321366054.95622 | czas: 0.0015247410 
n=750 | Wynik 4=0        | Wspolczynnik: 317031972.04032 | czas: 0.0017742690 

MACIERZ 1 (n^4):
n= 50 | Wynik 4=2500     | Wspolczynnik: 703394039.42766 | czas: 0.0088854890 
n=100 | Wynik 4=10000    | Wspolczynnik: 1339953022.85496 | czas: 0.0746294820 
n=150 | Wynik 4=22500    | Wspolczynnik: 1711386777.93156 | czas: 0.2958127330 
n=200 | Wynik 4=40000    | Wspolczynnik: 1736950237.50037 | czas: 0.9211547720 
n=250 | Wynik 4=62500    | Wspolczynnik: 1744531133.26993 | czas: 2.2391403200 
n=300 | Wynik 4=90000    | Wspolczynnik: 1655341127.85214 | czas: 4.8932512240 
n=350 | Wynik 4=122500   | Wspolczynnik: 1736189269.75787 | czas: 8.6432108880 
n=400 | Wynik 4=160000   | Wspolczynnik: 1770655571.13536 | czas: 14.4579219230 

MACIERZ LOSOWA:
n= 50 | Wynik 4=10       | Wspolczynnik: 10717332.49881 | czas: 0.0002332670 
n=100 | Wynik 4=18       | Wspolczynnik: 13208294.80914 | czas: 0.0007571000 
n=150 | Wynik 4=16       | Wspolczynnik: 12779857.58127 | czas: 0.0017605830 
n=200 | Wynik 4=20       | Wspolczynnik: 16299426.99364 | czas: 0.0024540740 
n=250 | Wynik 4=18       | Wspolczynnik: 27249940.37713 | czas: 0.0022935830 
n=300 | Wynik 4=18       | Wspolczynnik: 33341557.58420 | czas: 0.0026993340 
n=350 | Wynik 4=21       | Wspolczynnik: 32582880.87459 | czas: 0.0037596430 
n=400 | Wynik 4=20       | Wspolczynnik: 37083099.05313 | czas: 0.0043146340 
n=450 | Wynik 4=16       | Wspolczynnik: 35410721.52711 | czas: 0.0057186070 
n=500 | Wynik 4=21       | Wspolczynnik: 33957882.17457 | czas: 0.0073620610 
n=550 | Wynik 4=21       | Wspolczynnik: 36557380.04073 | czas: 0.0082746630 
n=600 | Wynik 4=20       | Wspolczynnik: 39621809.82522 | czas: 0.0090859050 
n=650 | Wynik 4=20       | Wspolczynnik: 42287365.11582 | czas: 0.0099911640 
n=700 | Wynik 4=20       | Wspolczynnik: 42869446.26324 | czas: 0.0114300520 
n=750 | Wynik 4=20       | Wspolczynnik: 43933368.11554 | czas: 0.0128034800 
n=800 | Wynik 4=22       | Wspolczynnik: 43583376.15627 | czas: 0.0146844980 
n=850 | Wynik 4=22       | Wspolczynnik: 44221893.89549 | czas: 0.0163380610 
n=900 | Wynik 4=22       | Wspolczynnik: 44596979.57321 | czas: 0.0181626650 
n=950 | Wynik 4=21       | Wspolczynnik: 44342115.56160 | czas: 0.0203531110



*/