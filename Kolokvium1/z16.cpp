#include <stdio.h>
#include <string.h>
#define NEDELI 4
#define DENOVI 5

// ovde strukturata RabotnaNedela

typedef struct RabotnaNedela{
    int brCasovi[5];
    int brNedela;
}RN;

// ovde strukturata Rabotnik

typedef struct Rabotnik{
    char ime[50];
    RN rabNed[4];
}R;

// ovde funkciite
int vkupno(RN niza){
    int zbir=0;
    for(int i=0;i<5;i++){
        zbir+=niza.brCasovi[i];
    }
    return zbir;
}
int maxNedela(R *r){
    int max=0;
    int index=0;
    for(int i=0;i<4;i++){
        vkupno(r->rabNed[i]);
        if(max < vkupno(r->rabNed[i])){
            max = vkupno(r->rabNed[i]);
            index = i;
        }
    }
    return index + 1;
}

void table(R *r, int n){
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0;i<n;i++){
        printf("%s\t", r[i].ime);
        int vkupnoRabCasovi=0;
        for(int j=0;j<NEDELI;j++){
            int vkupnoRabCasoviNedela=0;
            for(int k=0;k<DENOVI;k++){
                vkupnoRabCasoviNedela += r[i].rabNed[j].brCasovi[k];
            }
            printf("%d\t", vkupnoRabCasoviNedela);
            vkupnoRabCasovi += vkupnoRabCasoviNedela;
        }
        printf("%d\n", vkupnoRabCasovi);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &rabotnici[i].rabNed[j].brCasovi[k]);
            }

        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
