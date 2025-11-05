#include<iostream>
#include<string.h>
using namespace std;

class Zichara{
    char *mesto;
    int cena;
public:
    Zichara(){
        this->mesto = new char[0];
    }
    Zichara(char *mesto, int cena){
        this->mesto = new char[strlen(mesto)+1];
        strcpy(this->mesto, mesto);
        this->cena = cena;
    }
    Zichara(const Zichara &z){
        this->mesto = new char[strlen(z.mesto)+1];
        strcpy(this->mesto, z.mesto);
        this->cena = z.cena;
    }
    Zichara& operator=(const Zichara &z){
        if(this!=&z){
            delete []mesto;
            this->mesto = new char[strlen(z.mesto)+1];
            strcpy(this->mesto, z.mesto);
            this->cena = z.cena;
        }
        return *this;
    }
    int getCenaKarta(){
        return cena;
    }
    ~Zichara(){
        delete []mesto;
    }
};

class PlaninarskiDom{
    char imeDom[15];
    int ceni[2];
    char klasa;
    bool daliZichara;
    Zichara *z;
public:
    PlaninarskiDom(){}
    PlaninarskiDom(char *imeDom, int *ceni, char klasa){
        strcpy(this->imeDom, imeDom);
        this->ceni[0] = ceni[0];
        this->ceni[1] = ceni[1];
        this->klasa = klasa;
        z = NULL;
    }
    void namaliKlasa(){
        if(klasa < 'F'){
            ++klasa;
        }
    }
    void pecati(){
        cout<<imeDom<<" klasa:"<<klasa;
        if(z!=NULL)
            cout<<" so Zichara"<<endl;
        else
            cout<<endl;
    }
    void setZichara(Zichara &r){
        z = &r;
    }
    bool proveriKlasa(char znak){
        return this->klasa > znak;
    }
    void presmetajDnevenPrestoj(int den, int mesec, int &cena){
        if(den<0 || den>31 || mesec<0 || mesec>12){
            throw 1;
        }
        if(den>=1 && mesec>=4 && den <=31 && mesec<=8){
            cena = ceni[0];
        }else
            cena = ceni[1];
        if(daliZichara){
            cena = cena + z->getCenaKarta();
        }
    }
    ~PlaninarskiDom(){}
};
int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    p.namaliKlasa();
    p.namaliKlasa();

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        p.pecati();
        if (p.proveriKlasa('D'))
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}

