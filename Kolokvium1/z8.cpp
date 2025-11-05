#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
typedef struct Laptop
{
    char firma[100];
    float dim;
    bool touch;
    int cena;
}Laptop;
typedef struct ITStore
{
    char ime[100];
    char lokacija[100];
    Laptop l[100];
    int brLaptopi;
}ITStore;

void print(ITStore *it,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%s %s\n",it[i].ime,it[i].lokacija);
        for(int j=0;j<it[i].brLaptopi;j++)
        {
            printf("%s %g %d\n",it[i].l[j].firma,it[i].l[j].dim,it[i].l[j].cena);
        }
    }
}

void najevtina_ponuda(ITStore *it,int n)
{
    int min = INT_MAX;
    int index;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<it[i].brLaptopi;j++)
        {
            if(it[i].l[j].touch)
            {
                if(it[i].l[j].cena < min)
                {
                    min = it[i].l[j].cena;
                    index = i;
                }
            }

        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n");
    printf("%s %s\n",it[index].ime,it[index].lokacija);
    printf("Najniskata cena iznesuva: %d",min);
}
int main()
{
    int n;
    scanf("%d",&n);
    ITStore it[20];
    for(int i=0;i<n;i++)
    {
        scanf("%s%s",it[i].ime,it[i].lokacija);
        scanf("%d",&it[i].brLaptopi);
        for(int j=0;j<it[i].brLaptopi;j++)
        {
            scanf("%s%f%d%d",it[i].l[j].firma,&it[i].l[j].dim,&it[i].l[j].touch,&it[i].l[j].cena);
        }
    }

    print(it,n);
    najevtina_ponuda(it,n);

    return 0;
}
