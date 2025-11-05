#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class Transport{
protected:
    char destinacija[20];
    int cena;
    int rastojanie;
public:
    Transport(char *destinacija="", int cena=0, int rastojanie=0){
        strcpy(this->destinacija, destinacija);
        this->cena = cena;
        this->rastojanie = rastojanie;
    }
    Transport(const Transport &tr){
        strcpy(this->destinacija, tr.destinacija);
        this->cena = tr.cena;
        this->rastojanie = tr.rastojanie;
    }
    char* getDestinacija(){
        return destinacija;
    }
    int getCena(){
        return cena;
    }
    int getRastojanie(){
        return rastojanie;
    }
    virtual int cenaTransport()=0;
    bool operator<(const Transport &t){
        return this->rastojanie < t.rastojanie;
    }
    ~Transport(){}
};

class AvtomobilTransport : public Transport{
private:
    bool shofer;
public:
    AvtomobilTransport(char *destinacija="", int cena=0, int rastojanie=0, bool shofer=false)
            : Transport(destinacija,cena,rastojanie){
        this->shofer = shofer;
    }
    int cenaTransport(){
        int suma = cena;
        if(shofer){
            suma+=cena*0.2;
        }
        return suma;
    }
    ~AvtomobilTransport(){}
};

class KombeTransport : public Transport{
private:
    int lugje;
public:
    KombeTransport(char *destinacija="", int cena=0, int rastojanie=0,int lugje=0)
            : Transport(destinacija,cena,rastojanie){
        this->lugje = lugje;
    }
    int cenaTransport(){
        int suma = cena - lugje * 200;
        return suma;
    }
    ~KombeTransport(){}
};
void pecatiPoloshiPonudi(Transport **ponudi,int n,Transport *t)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(ponudi[j]->getRastojanie()>ponudi[j+1]->getRastojanie() && ponudi[j]->cenaTransport() > ponudi[j+1]->cenaTransport())
            {
                Transport* temp = ponudi[j];
                ponudi[j] = ponudi[j+1];
                ponudi[j+1] = temp;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(ponudi[i]->getCena()>t->getCena()){
            cout<<ponudi[i]->getDestinacija()<<" "<<ponudi[i]->getRastojanie()<<" "<<ponudi[i]->cenaTransport()<<endl;
        }
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,&nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}