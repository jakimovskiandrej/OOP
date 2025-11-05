#include <iostream>
#include <cstring>

using namespace std;

enum tip{SMARTPHONE, LAPTOP};

class InvalidProductionDate{
    char *msg;
public:
    InvalidProductionDate(char *msg){
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg, msg);
    }
    void message(){
        cout<<msg<<endl;
    }
    ~InvalidProductionDate(){
        delete []msg;
    }
};

class Device{
    char ime[100];
    tip tipDevice;
    int godina;
    static int pocetniCasovi;
public:
    Device(){}
    Device(char *ime, tip tipDevice, int godina){
        strcpy(this->ime, ime);
        this->tipDevice = tipDevice;
        this->godina = godina;
    }
    static void setPocetniCasovi(int p){
        pocetniCasovi = p;
    }
    friend ostream& operator<<(ostream &o, Device &d){
        int dopCasovi=0;
        o<<d.ime<<endl;
        if(d.tipDevice==LAPTOP){
            o<<"Laptop ";
            dopCasovi += 2;
        }
        if(d.tipDevice==SMARTPHONE){
            o<<"Mobilen ";
        }
        if(d.godina>2015){
            dopCasovi+=2;
        }
        o<<pocetniCasovi + dopCasovi<<endl;
        return o;
    }
    int getGodina(){
        return godina;
    }
    ~Device(){}
};

int Device::pocetniCasovi = 1;

class MobileServis{
    char ime[100];
    Device *d;
    int n;
public:
    MobileServis(){
        n=0;
        d = new Device[n];
    }
    MobileServis(char *ime){
        strcpy(this->ime, ime);
        n = 0;
        d = new Device[n];
    }
    MobileServis(const MobileServis &ms){
        strcpy(this->ime, ms.ime);
        n = ms.n;
        d = new Device[n];
        for(int i=0;i<n;i++){
            this->d[i] = ms.d[i];
        }
    }
    MobileServis& operator=(const MobileServis &ms){
        if(this!=&ms){
            strcpy(this->ime, ms.ime);
            n = ms.n;
            d = new Device[n];
            for(int i=0;i<n;i++){
                this->d[i] = ms.d[i];
            }
        }
        return *this;
    }

    MobileServis& operator+=(Device &nov){
        if(nov.getGodina() < 2000 || nov.getGodina()>2019)
            throw InvalidProductionDate("Невалидна година на производство");
        Device *temp = new Device[n+1];
        for(int i=0;i<n;i++){
            temp[i] = d[i];
        }
        temp[n] = nov;
        n++;
        delete []d;
        d = temp;
        return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<ime<<endl;
        for(int i=0;i<n;i++){
            cout<<d[i];
        }
    }
    ~MobileServis(){
        delete []d;
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &p)
            {
                p.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &p)
            {
                p.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &p)
            {
                p.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &p)
            {
                p.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try
            {
                t+=tmp;
            }
            catch(InvalidProductionDate &p)
            {
                p.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}