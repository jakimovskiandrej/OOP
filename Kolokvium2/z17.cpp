#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa{
protected:
    char coach[100];
    int goals[10];
public:
    FudbalskaEkipa(char *coach, int *goals){
        strcpy(this->coach, coach);
        for(int i=0;i<10;i++){
            this->goals[i] = goals[i];
        }
    }
    FudbalskaEkipa& operator+=(int nov){
        int golovi[10];
        for(int i=0;i<9;i++){
            golovi[i] = goals[i+1];
        }
        golovi[9] = nov;
        for(int i=0;i<10;i++){
            goals[i] = golovi[i];
        }
        return *this;
    }
    friend ostream& operator<<(ostream &o, FudbalskaEkipa &f){
        o<<f.getIme()<<endl;
        o<<f.coach<<endl;
        o<<f.uspeh()<<endl;
        return o;
    }
    virtual char* getIme()=0;
    char* getCoach(){
        return coach;
    }
    virtual int uspeh()=0;
    virtual ~FudbalskaEkipa(){}
};

class Klub : public FudbalskaEkipa{
private:
    char imeKlub[50];
    int brTituli;
public:
    Klub(char *coach, int *goals, char *imeKlub, int brTituli)
            : FudbalskaEkipa(coach,goals){
        strcpy(this->imeKlub, imeKlub);
        this->brTituli = brTituli;
    }
    friend ostream& operator<<(ostream &o, Klub &k){
        o<<k.imeKlub<<endl;
        o<<k.coach<<endl;
        return o;
    }
    char* getIme(){
        return imeKlub;
    }
    int uspeh(){
        int zbir=0;
        for(int i=0;i<10;i++){
            zbir += goals[i];
        }
        return zbir*3+brTituli*1000;
    }
    ~Klub(){}
};

class Reprezentacija : public FudbalskaEkipa{
private:
    char imeDrzhava[50];
    int nastapi;
public:
    Reprezentacija(char *coach, int *goals, char *imeDrzhava, int nastapi)
            : FudbalskaEkipa(coach,goals){
        strcpy(this->imeDrzhava, imeDrzhava);
        this->nastapi = nastapi;
    }
    char* getIme(){
        return imeDrzhava;
    }
    int uspeh(){
        int zbir=0;
        for(int i=0;i<10;i++){
            zbir += goals[i];
        }
        return zbir*3+nastapi*50;
    }
    bool operator>(int pr){
        return this->uspeh() > pr;
    }

    ~Reprezentacija(){}
};

void najdobarTrener(FudbalskaEkipa **ekipi, int n){
    int maxTrener = 0;
    int maxIndex=0;
    for(int i=0;i<n;i++){
        if(ekipi[i]->uspeh()>maxTrener){
            maxTrener = ekipi[i]->uspeh();
            maxIndex = i;
        }
    }
    cout<<*ekipi[maxIndex]<<endl;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
