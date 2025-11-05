#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException
{

};
class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
    const static int P;
public:
    Karticka()
    {
        povekjePin = false;
    }
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    virtual int tezinaProbivanje()
    {
        int temp = pin;
        int counter = 0;
        while(temp!=0)
        {
            temp/=10;
            counter++;
        }
        return counter;
    }
    bool getDopolnitelenPin()
    {
        return povekjePin;
    }
    char *getSmetka()
    {
        return smetka;
    }
    friend ostream& operator<<(ostream &o, Karticka &k)
    {
        o<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
        return o;
    }
    virtual ~Karticka(){}
};

class SpecijalnaKarticka : public Karticka
{
private:
    int *dopPinovi;
    int n;
public:
    SpecijalnaKarticka() : Karticka()
    {
        povekjePin = true;
        n = 0;
        dopPinovi = new int[0];
    }
    SpecijalnaKarticka(char* smetka,int pin)
            : Karticka(smetka,pin)
    {
        povekjePin = true;
        this->n = 0;
        dopPinovi = new int[n];
        for(int i=0;i<n;i++)
        {
            this->dopPinovi[i] = dopPinovi[i];
        }
    }
    SpecijalnaKarticka(const SpecijalnaKarticka &sk): Karticka(sk)
    {
        this->n = sk.n;
        dopPinovi = new int[n];
        for(int i=0;i<n;i++)
        {
            this->dopPinovi[i] = sk.dopPinovi[i];
        }
    }
    SpecijalnaKarticka& operator=(const SpecijalnaKarticka &sk)
    {
        if(this!=&sk)
        {
            delete []dopPinovi;
            this->n = sk.n;
            dopPinovi = new int[n];
            for(int i=0;i<n;i++)
            {
                this->dopPinovi[i] = sk.dopPinovi[i];
            }
        }
        return *this;
    }
    int tezinaProbivanje()
    {
        int osnovna = Karticka::tezinaProbivanje();
        return osnovna+n;
    }
    SpecijalnaKarticka& operator+=(int nov)
    {
        if(n==Karticka::P)
        {
            throw OutOfBoundException();
        }
        int *temp = new int[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i] = dopPinovi[i];
        }
        temp[n] = nov;
        n++;
        delete []dopPinovi;
        dopPinovi = temp;
        return *this;
    }
    ~SpecijalnaKarticka()
    {
        delete []dopPinovi;
    }
};

const int Karticka::P = 4;

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    static void setLIMIT(int l)
    {
        LIMIT = l;
    }

    void pecatiKarticki()
    {
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite: "<<endl;
        for(int i=0;i<broj;i++)
        {
            if(karticki[i]->tezinaProbivanje() <= LIMIT)
            {
                cout<<*karticki[i];
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(karticki[i]->getSmetka(), smetka)==0)
            {
                SpecijalnaKarticka *sk = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(sk!=0)
                {
                    *sk+=novPin;
                }
            }
        }
    }
};

int Banka::LIMIT = 7;

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
