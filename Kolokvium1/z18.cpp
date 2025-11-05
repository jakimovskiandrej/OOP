#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SkiLift{
    char ime[15];
    int maxKorisnici;
    int voFunkcija;
}skilift;

typedef struct SkiCenter{
    char imeCentar[20];
    char drzhava[20];
    skilift sl[20];
    int brLiftovi;
}skicenter;

int kapacitet(skicenter sc){
    int i, tmp=0;
    for(i=0;i<sc.brLiftovi;i++){
        if(sc.sl[i].voFunkcija==1){
            tmp+=sc.sl[i].maxKorisnici;
        }
    }
    return tmp;
}

void najgolemKapacitet(skicenter *sc, int n){
    int max, maxInd, i, j, tmp;
    max=0;
    maxInd=0;
    for(i=0;i<n;i++){
        tmp = kapacitet(sc[i]);
        if((tmp>max) || (tmp==max&&sc[i].brLiftovi>sc[maxInd].brLiftovi)){
            max = tmp;
            maxInd = i;
        }
    }
    printf("%s\n%s\n%d", sc[maxInd].imeCentar, sc[maxInd].drzhava, max);
}
int main(){
    int n,i,j;
    skicenter sc[20];
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%s", sc[i].imeCentar);
        scanf("%s", sc[i].drzhava);
        scanf("%d", &sc[i].brLiftovi);

        for(j=0;j<sc[i].brLiftovi;j++){
            scanf("%s", sc[i].sl[j].ime);
            scanf("%d", &sc[i].sl[j].maxKorisnici);
            scanf("%d", &sc[i].sl[j].voFunkcija);
        }
    }
    najgolemKapacitet(sc,n);
    return 0;
}
