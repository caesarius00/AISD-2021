#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct wezel{
    char napis[20];
    struct wezel *next, *prev;
}wezel, *wskWezla;

wskWezla budujWezel(char napis[]){
    wskWezla w=(wskWezla)malloc(sizeof(wezel));
    strcpy(w->napis,napis);
    w->next=w->prev=NULL;
    return w;
}

bool drukuj(wskWezla L){
    wskWezla doWypisania=L->next;
    bool toReturn=false;
    while(strcmp("",doWypisania->napis)!=0){
        toReturn=true;
        printf("%s ",doWypisania->napis);
        doWypisania=doWypisania->next;
    }
    return toReturn;
}

wskWezla szukaj(char * s, wskWezla L){
    
    wskWezla searched = L->next;
    while(strcmp("",searched->napis)!=0){
        if(strcmp(searched->napis,s)==0){
            return searched;
        }
        searched=searched->next;
    }
    return NULL;
}

void wstawNaPocz1(wskWezla nowy, wskWezla nil){
    nowy->next=nil->next;
    nowy->prev=nil;
    nil->next->prev=nowy;
    nil->next=nowy;

}


wskWezla pustaLista(){
    wskWezla n=budujWezel("");
    n->next=n->prev=n;
    return n;
}

void wstaw(char * s, wskWezla L){
    wskWezla w=budujWezel(s);
    wstawNaPocz1(w,L);
}

bool usun(char *s, wskWezla L){
    wskWezla searched = szukaj(s,L);
    if(searched!=NULL){
        wskWezla loop = L->next;
        while(searched!=loop) loop=loop->next;
        loop->prev->next=loop->next;
        loop->next->prev=loop->prev;
        free(loop);
        return true;
    }
    return false;
}

void kasuj(wskWezla L){
    while(L->next!=L){
        wskWezla toDelete = L->next;
        L->next=L->next->next;
        L->next->prev=L;
        free(toDelete);

    }
}

wskWezla bezPowtorzen(wskWezla L){
    wskWezla nil=pustaLista();
    wskWezla temp=L->next;
    while(temp!=L){
        if(szukaj(temp->napis,nil)==NULL){
            wstaw(temp->napis,nil);
        }
        temp=temp->next;
    }
    return nil;
}

wskWezla scal(wskWezla L1, wskWezla L2){
    L1->prev->next=L2->next; //usuwam wartownika listy 2
    L2->next->prev=L1->prev;
    L2->prev->next=L1;
    L1->prev=L2->prev;
    wskWezla L=L1;
    return L;
}

int main(){
    wskWezla nil=pustaLista();  //inicjalizacja listy (nil to początek [wartownik])
    wskWezla kopia;
    int choice=1;
    while(choice){
        printf("Co chcesz zrobić?\n");
        printf("\t0 - zakoncz\n");
        printf("\t1 - wstaw\n");
        printf("\t2 - drukuj\n");
        printf("\t3 - szukaj\n");
        printf("\t4 - usun\n");
        printf("\t5 - kasuj\n");
        printf("\t6 - skopiuj liste bez powtorzen\n");
        printf("\t7 - polacz listy\n");
        scanf("%d",&choice);
        char str[32];
        switch(choice){
            case 1:
                printf("Co wstawic?\n\t: ");
                scanf("%s",str);
                wstaw(str,nil);
                printf("Dodano %s do listy\n",str);
                break;
            case 2: 
                if(!drukuj(nil)) printf("Lista jest pusta\n");
                printf("\n");
                break;
            case 3:
                printf("Co wyszukac?\n\t: ");
                scanf("%s",str);
                if(szukaj(str,nil)!=NULL) printf("Znaleziono %s w liscie\n",str);
                else printf("Nie ma %s w liscie\n", str);
                break;
            case 4:
                printf("Co usunac?\n\t: ");
                scanf("%s",str);
                if(usun(str,nil)) printf("Usunieto %s z listy\n",str);
                else printf("W tej liscie nie ma %s\n",str);
                break;
            case 5:
                kasuj(nil);
                printf("Skasowano liste\n");
                break;
            case 6:
                kopia=bezPowtorzen(nil);
                printf("Utworzono kopie bez powtorzen:\n");
                drukuj(kopia);
                kasuj(kopia);
                break;
            case 7:
                printf("Stworze kopie listy bez powtorzen i polacze z ta lista\n");
                nil=scal(nil,bezPowtorzen(nil));
                break;


        }
    }

    //if(szukaj("d",nil)==NULL) printf("\nNie znaleziono");
    //else printf("\nZnaleziono");
    //printf("%s ",nil->next->napis);
    //printf("%s ",nil->next->next->napis);
    //printf("|| %s ",nil->next->next->next->next->next->next->next->next->napis);
    return 0;
}