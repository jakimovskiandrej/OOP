#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo{
private:
    char ime[50];
    int godina;
    char zemja[50];
public:
    Delo(){}
    Delo(char *ime, int godina, char *zemja){
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->zemja, zemja);
    }
    char* getIme(){
        return ime;
    }
    int getGodina(){
        return godina;
    }
    char* getZemja(){
        return zemja;
    }
    bool operator==(const Delo &d){
        return strcmp(this->ime, d.ime)==0;
    }
    ~Delo(){}
};

class Pretstava{
protected:
    Delo d;
    int brojProdadeni;
    char data[15];
public:
    Pretstava(){}
    Pretstava(Delo &d, int brojProdadeni, char *data){
        this->d = d;
        this->brojProdadeni = brojProdadeni;
        strcpy(this->data, data);
    }
    Delo& getDelo(){
        return d;
    }
    int getProdadeni(){
        return brojProdadeni;
    }
    void setDelo(Delo &d){
        this->d = d;
    }
    virtual int cena(){
        int M=0;
        if(this->d.getGodina()>=1900 && this->d.getGodina()<=2100){
            M += 50;
        }
        else if(this->d.getGodina()>=1800 && this->d.getGodina()<1900){
            M += 75;
        }
        else if(d.getGodina()<1800){
            M += 100;
        }
        int N;
        if(strcmp(this->d.getZemja(), "Italija")==0){
            N = 100;
        }
        else if(strcmp(this->d.getZemja(), "Rusija")==0){
            N = 150;
        }
        else{
            N = 80;
        }
        return N + M;
    }
    virtual ~Pretstava(){}
};

class Balet : public Pretstava{
private:
    static int cenaBalet;
public:
    Balet() : Pretstava(){}
    Balet(Delo &d, int brojProdadeni, char *data)
            : Pretstava(d,brojProdadeni,data){}
    static void setCenaBalet(int c){
        cenaBalet = c;
    }
    int cena(){
        int osnovna = Pretstava::cena();
        return osnovna + cenaBalet;
    }
    ~Balet(){}
};

int Balet::cenaBalet = 150;

class Opera : public Pretstava{
private:
public:
    Opera() : Pretstava(){}
    Opera(Delo &d, int brojProdadeni, char *data)
            : Pretstava(d,brojProdadeni,data){}
    int cena(){
        return Pretstava::cena();
    }
    ~Opera(){}
};

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int prihod(Pretstava **p, int n){
    int suma=0;
    for(int i=0;i<n;i++){
        suma+= p[i]->cena() * p[i]->getProdadeni();
    }
    return suma;
}

int brojPretstaviNaDelo(Pretstava **p,int n,Delo f){
    int brojac=0;
    for(int i=0;i<n;i++){
        if(p[i]->getDelo()==f){
            brojac++;
        }
    }
    return brojac;
}

int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
