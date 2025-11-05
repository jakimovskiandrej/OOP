#include <stdio.h>
#include <string.h>

typedef struct
{
    char code[20];
    int cena;
    int zaliha;
}Proizvod;

typedef struct
{
    char ime[15];
    Proizvod p[10];
    int brProizvodi[10];
    int n;
}Narachka;

void pecatiFaktura(Narachka *narachka)
{
    printf("Faktura za %s\n",narachka->ime);
    int napravenaNarachka=1;
    int vkupno=0;
    for(int i=0;i<narachka->n;i++)
    {
        if(narachka->brProizvodi[i] > narachka->p[i].zaliha)
        {
            napravenaNarachka=0;
            break;
        }
    }
    if(napravenaNarachka==0)
    {
        printf("Fakturata ne moze da se izgotvi\n");
        return;//ja zavrsuvame funkcijata pecatiFaktura
    }
    for(int i=0;i<narachka->n;i++)
    {
        int vkupnaCenaPoProizvod = narachka->p[i].cena * narachka->brProizvodi[i];
        vkupno+=vkupnaCenaPoProizvod;
        printf("%s %d %d %d\n",narachka->p[i].code,narachka->p[i].cena,narachka->brProizvodi[i],vkupnaCenaPoProizvod);
        narachka->p[i].zaliha-=narachka->brProizvodi[i];
    }
    printf("Vkupnata suma na fakturata e %d\n",vkupno);
}

void sort(Narachka *narachka)
{
    for(int i=0;i<narachka->n;i++)
    {
        for(int j=0;j<narachka->n-1-i;j++)
        {
            if(strcmp(narachka->p[j].code,narachka->p[j+1].code) >0)
            {
                Proizvod temp = narachka->p[j];
                narachka->p[j] = narachka->p[j+1];
                narachka->p[j+1] = temp;
            }

        }
    }
}
int main() {

    Narachka narachka;
    scanf("%s",narachka.ime);
    scanf("%d",&narachka.n);
    int i;

    for (i = 0; i < narachka.n; ++i) {

        scanf("%s %d %d",narachka.p[i].code,&narachka.p[i].cena,&narachka.p[i].zaliha);
    }
    sort(&narachka);

    int j;
    for (j = 0; j < narachka.n; ++j) {
        scanf("%d",&narachka.brProizvodi[j]);
    }


    pecatiFaktura(&narachka);


    return 0;
}
