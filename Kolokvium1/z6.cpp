#include<iostream>
#include <cstring>
using namespace std;

struct Voz{
    char relacija[50];
    float kilometri;
    int patnici;
};

struct ZeleznickaStanica{
    char grad[20];
    Voz niza[30];
    int n;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
    Voz najkratka{};
    for(int i=0;i<n;i++){
        if(strncmp(zs[i].grad, grad, strlen(grad))==0){
            najkratka = zs[i].niza[0];
            for(int j=1;j<zs[i].n;j++){
                if(zs[i].niza[j].kilometri<=najkratka.kilometri){
                    najkratka = zs[i].niza[j];
                }
            }
        }
    }
    cout<<"Najkratka relacija: "<<najkratka.relacija<<" ("<<najkratka.kilometri<<" km)";
}
int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>zStanica[i].grad;
        cin>>zStanica[i].n;
        for(int j=0;j<zStanica[i].n;j++){
            cin>>zStanica[i].niza[j].relacija>>zStanica[i].niza[j].kilometri>>zStanica[i].niza[j].patnici;
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
