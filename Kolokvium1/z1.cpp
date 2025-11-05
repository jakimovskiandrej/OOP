#include <iostream>
#include <cstring>
using namespace std;

enum tip {POP,RAP,ROK};

class Pesna
{
    int minuti;
    tip kojtip;
    char *ime;
public:
    Pesna()
    {
        this->ime = new char[0];
    }
    Pesna(char *ime,int minuti,tip kojtip)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->minuti = minuti;
        this->kojtip = kojtip;
    }

    Pesna(const Pesna &p)
    {
        this->ime = new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->minuti = p.minuti;
        this->kojtip = p.kojtip;
    }
    Pesna& operator=(const Pesna &p)
    {
        if(this!=&p)
        {
            this->ime = new char[strlen(p.ime)+1];
            strcpy(this->ime,p.ime);
            this->minuti = p.minuti;
            this->kojtip = p.kojtip;
        }
        return *this;
    }

    tip getTip()
    {
        return kojtip;
    }
    int getMin()
    {
        return minuti;
    }
    void pecati()
    {
        cout<<"\""<<ime<<"\"-"<<minuti<<"min"<<endl;
    }
    ~Pesna()
    {
        delete []ime;
    }
};


class CD
{
    Pesna pesni[10];
    int n;
    int maxTime;

public :
    CD(){}
    CD(int maxTime)
    {
        this->maxTime = maxTime;
    }
    void dodadiPesna(Pesna p)
    {
        int suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=pesni[i].getMin();
        }
        if(n<9 && (suma + p.getMin())<maxTime)
        {
            pesni[n] = p;
            n++;
        }

    }
    int getBroj()
    {
        return n;
    }
    void pecatiPesniPoTip(tip t)
    {
        for(int i=0;i<n;i++)
        {
            if(pesni[i].getTip()==t)
            {
                pesni[i].pecati();
            }
        }
    }
    Pesna getPesna(int i)
    {
        return pesni[i];
    }
    ~CD(){}
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();

    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
}