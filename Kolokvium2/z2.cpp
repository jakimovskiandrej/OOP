#include <iostream>
#include <cstring>
using namespace std;

class Vozac{
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool veteran;
public:
    Vozac(char *ime, int vozrast, int trki, bool veteran){
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->trki = trki;
        this->veteran = veteran;
    }
    friend ostream& operator<<(ostream &o, Vozac &v){
        o<<v.ime<<endl;
        o<<v.vozrast<<endl;
        o<<v.trki<<endl;
        if(v.veteran){
            o<<"VETERAN"<<endl;
        }
        return o;
    }
    virtual float zarabotuvachka()=0;
    virtual float danok()=0;
    bool operator==(Vozac &v){
        return this->zarabotuvachka() == v.zarabotuvachka();
    }
    ~Vozac(){}
};

class Avtomobilist : public Vozac{
private:
    float cenaAvto;
public:
    Avtomobilist(char *ime, int vozrast, int trki, bool veteran, float cenaAvto)
            : Vozac(ime,vozrast,trki,veteran){
        this->cenaAvto = cenaAvto;
    }
    float zarabotuvachka(){
        return cenaAvto / 5.0;
    }
    float danok(){
        if(trki>10){
            return zarabotuvachka() * 15/100;
        }else{
            return zarabotuvachka() * 10/100;
        }
    }
    ~Avtomobilist(){}
};

class Motociklist : public Vozac{
private:
    int mokjnost;
public:
    Motociklist(char *ime, int vozrast, int trki, bool veteran, int mokjnost)
            : Vozac(ime,vozrast,trki,veteran){
        this->mokjnost = mokjnost;
    }
    float zarabotuvachka(){
        return mokjnost * 20;
    }
    float danok(){
        if(veteran){
            return zarabotuvachka() * 25/100;
        }else{
            return zarabotuvachka() * 20/100;
        }
    }
    ~Motociklist(){}
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx){
    int br=0;
    for(int i=0;i<n;i++){
        if(v[i]->zarabotuvachka()==vx->zarabotuvachka()){
            br++;
        }
    }
    return br;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
