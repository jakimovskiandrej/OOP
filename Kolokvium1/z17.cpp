#include <iostream>
#include <cstring>

using namespace std;

enum Tip{LINUX, UNIX, WINDOWS};

class OperativenSistem{
    char *ime;
    float verzija;
    Tip tip;
    float golemina;
public:
    OperativenSistem(){
        ime = new char[0];
    }
    OperativenSistem(char *ime, float verzija, Tip tip, float golemina){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->tip = tip;
        this->verzija = verzija;
        this->golemina = golemina;
    }
    OperativenSistem(const OperativenSistem &os){
        this->ime = new char[strlen(os.ime)+1];
        strcpy(this->ime, ime);
        this->tip = os.tip;
        this->verzija = os.verzija;
        this->golemina = os.golemina;
    }
    OperativenSistem& operator=(const OperativenSistem &os){
        if(this!=&os){
            delete []ime;
            this->ime = new char[strlen(os.ime)+1];
            strcpy(this->ime, os.ime);
            this->tip = os.tip;
            this->verzija = os.verzija;
            this->golemina = os.golemina;
        }
        return *this;
    }
    void pecati(){
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<golemina<<"GB"<<endl;
    }
    bool istaFamilija(const OperativenSistem &os){
        return strcmp(this->ime, os.ime)==0 && this->tip == os.tip;
    }
    bool ednakviSe(const OperativenSistem &os){
        return istaFamilija(os) && this->verzija == os.verzija && this->golemina == os.golemina;
    }
    int sporediVerzija(const OperativenSistem &os){
        if(this->verzija == os.verzija){
            return 0;
        }else if(this->verzija < os.verzija){
            return -1;
        }
        else
            return 1;
    }
    int getVerzija(){
        return verzija;
    }
    ~OperativenSistem(){}
};

class Repozitorium{
    char imeRepo[20];
    OperativenSistem *os;
    int n;
public:
    Repozitorium(){
        this->n = 0;
        os = new OperativenSistem[0];
    }
    Repozitorium(char *imeRepo){
        this->n = 0;
        os = new OperativenSistem[0];
        strcpy(this->imeRepo, imeRepo);
    }
    Repozitorium(const Repozitorium &r){
        this->n = r.n;
        os = new OperativenSistem[r.n];
        for(int i=0;i<n;i++){
            this->os[i] = r.os[i];
        }
        strcpy(this->imeRepo, r.imeRepo);
    }
    Repozitorium& operator=(const Repozitorium &r){
        if(this!=&r){
            delete []os;
            this->n = r.n;
            os = new OperativenSistem[r.n];
            for(int i=0;i<n;i++){
                this->os[i] = r.os[i];
            }
            strcpy(this->imeRepo, r.imeRepo);
        }
        return *this;
    }
    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<imeRepo<<endl;
        for(int i=0;i<n;i++){
            os[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem){
        int flag = 0;
        for(int i=0;i<n;i++){
            if(os[i].ednakviSe(operativenSistem)){
                flag = 1;
                break;
            }
        }
        if(flag==1){
            OperativenSistem *temp = new OperativenSistem[n-1];
            int j=0;
            for(int i=0;i<n;i++){
                if(!os[i].ednakviSe(operativenSistem)){
                    temp[j] = os[i];
                    j++;
                }
            }
            delete []os;
            os = temp;
            n--;
        }
    }
    void izbrishiFamilija(const OperativenSistem &operativenSistem){
        int br=0;
        for(int i=0;i<n;i++){
            if(!os[i].istaFamilija(operativenSistem)){
                br++;
            }
        }
        OperativenSistem *temp = new OperativenSistem[br];
        int j=0;
        for(int i=0;i<n;i++){
            if(!os[i].istaFamilija(operativenSistem)){
                temp[j] = os[i];
                j++;
            }
        }
        delete []os;
        os = temp;
        n = br;
    }
    void dodadi(OperativenSistem &nov){
        int najdePostar=0;
        for(int i=0;i<n;i++){
            if(os[i].istaFamilija(nov) && os[i].getVerzija() < nov.getVerzija()){
                najdePostar = 1;
                os[i] = nov;
            }
        }
        if(najdePostar==0){
            OperativenSistem *temp = new OperativenSistem[n+1];
            for(int i=0;i<n;i++){
                temp[i] = os[i];
            }
            temp[n] = nov;
            delete []os;
            os = temp;
            n++;
        }
    }
    ~Repozitorium(){
        delete []os;
    }
};
int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}