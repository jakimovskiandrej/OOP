#include <stdio.h>
#include <string.h>

typedef struct
{
    char ime[100];
    int zdrastveno;
    int pregledi;
}Pacient;

typedef struct
{
    char ime[100];
    int br_pac;
    Pacient niza[200];
    float cena;
}doktor;

void najuspesen_doktor(doktor *md,int n)
{
    float max=0;
    int index;
    int maxVkupnoPregledi=0;
    for(int i=0;i<n;i++)
    {
        float zarabotka = 0;
        int vkupnoPregledi=0;
        for(int j=0;j<md[i].br_pac;j++)
        {
            if(md[i].niza[j].zdrastveno==0)
            {
                zarabotka+=md[i].niza[j].pregledi * md[i].cena;
            }
            vkupnoPregledi +=md[i].niza[j].pregledi;
        }

        if(zarabotka > max)
        {
            max = zarabotka;
            index=i;
            maxVkupnoPregledi = vkupnoPregledi;
        }
        else if(zarabotka==max)
        {
            if(vkupnoPregledi > maxVkupnoPregledi)
            {
                index =i;
                maxVkupnoPregledi = vkupnoPregledi;
            }
        }
    }
    printf("%s %.2f %d",md[index].ime,max,maxVkupnoPregledi);
}
int main()
{
    int i, j, n, broj;
    doktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        //ime na doktor
        scanf("%s", &md[i].ime);
        //broj na pacienti
        scanf("%d", &md[i].br_pac);
        //cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].br_pac; j++){
            scanf("%s", &md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}
