#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Tanc
{
    char imeTanc[15];
    char zemja[15];
};
typedef struct Tancer
{
    char ime[20];
    char prezime[20];
    Tanc t[5];
};

void tancuvanje(Tancer *tanceri,int n,char *zemja)
{
    for(int i=0;i<n;i++)
    {
        int flag=0;
        for(int j=0;j<3;j++)
        {
            if(strcmp(zemja,tanceri[i].t[j].zemja)==0)
            {
                flag=1;
                break;
            }
        }
        if(flag){
            printf("%s %s, ",tanceri[i].ime,tanceri[i].prezime);
            for(int j=0;j<3;j++)
            {
                if(strcmp(zemja,tanceri[i].t[j].zemja)==0)
                {
                    printf("%s ",tanceri[i].t[j].imeTanc);
                    break;
                }
            }
            printf("\n");
        }
    }
}
int main()
{
    int n;
    Tancer tanceri[50];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s%s",tanceri[i].ime,tanceri[i].prezime);

        for(int j=0;j<3;j++)
        {
            scanf("%s%s",tanceri[i].t[j].imeTanc,tanceri[i].t[j].zemja);
        }
    }
    char zemja[20];
    scanf("%s",zemja);
    tancuvanje(tanceri,n,zemja);
    return 0;
}
