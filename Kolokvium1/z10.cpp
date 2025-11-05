#include <iostream>
#include <cstring>

using namespace std;
struct Igrac{
    char ime[15];
    int nivo;
    int poeni;
};

struct KompjuterskaIgra{
    char imeIgra[20];
    Igrac lista[30];
    int n;
};

void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int max=0;
    for(int i=1;i<n;i++){
        if(lista[i].n > lista[max].n){
            max = i;
        }
    }
    KompjuterskaIgra najpopularna = lista[max];
    int index=0;
    for(int i=0;i<najpopularna.n;i++){
        if(najpopularna.lista[i].poeni > najpopularna.lista[index].poeni){
            index = i;
        }
        else if(najpopularna.lista[i].poeni == najpopularna.lista[index].poeni){
            if(najpopularna.lista[i].nivo > najpopularna.lista[index].nivo){
                index = i;
            }
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime ";
    cout<<najpopularna.lista[index].ime;
    cout<<" koj ja igra igrata ";
    cout<<najpopularna.imeIgra;
}

int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.imeIgra>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.ime>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
