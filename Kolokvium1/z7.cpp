#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Vozenje{
    char ime[100];
    int traenje;
    float cena;
    int popust;
}Vozenje;

typedef struct ZabavenPark{
    char imePark[100];
    char lokacija[100];
    Vozenje array[100];
    int n;
}ZabavenPark;

void print(ZabavenPark *array, int n){
    for(int i=0;i<n;i++){
        printf("%s %s\n", array[i].imePark, array[i].lokacija);
        for(int j=0;j<array[i].n;j++){
            printf("%s %d %.2f\n", array[i].array[j].ime, array[i].array[j].traenje, array[i].array[j].cena);
        }
    }
}

void najdobarPark(ZabavenPark *array, int n){
    int maxI=0, maxV=0, maxVremetraenje=0;
    for(int i=0;i<n;i++){
        int br=0;
        int vreme=0;
        for(int j=0;j<array[i].n;j++){
            if(array[i].array[j].popust==1)
                br++;
            vreme+= array[i].array[j].traenje;
        }
        if(br>maxV){
            maxV = br;
            maxI = i;
            maxVremetraenje = vreme;
        }
        else if(br==maxV&&vreme>maxVremetraenje){
            maxI = i;
            maxVremetraenje = vreme;
        }
    }
    printf("Najdobar park: %s %s\n", array[maxI].imePark, array[maxI].lokacija);
}
int main(){
    int i, j, n, broj;
    //kreiraj niza od maksimum 100 zabavni parkovi
    ZabavenPark ff[100];
    scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
        //ime na festivalot
        scanf("%s", ff[i].imePark);
        //mesto
        scanf("%s", ff[i].lokacija);
        //broj na filmovi
        scanf("%d", &ff[i].n);

        for (j = 0; j < ff[i].n; j++){
            scanf("%s", ff[i].array[j].ime);  			/* Ime na filmot */
            scanf("%d", &ff[i].array[j].traenje); 		/* Vremetraenje   */
            scanf("%f", &ff[i].array[j].cena); 	/* Cena */
            scanf("%d", &ff[i].array[j].popust);	/* Popust */
        }
    }
    print(ff,n);
    najdobarPark(ff,n);
    return 0;
}
