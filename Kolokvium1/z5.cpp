#include <iostream>
#include <cstring>

using namespace std;

class Gitara{
    char seriski[25];
    float cena;
    int godina;
    char tip[40];
public:
    Gitara(){}
    Gitara(char *tip, char *seriski, int godina, float cena){
        strcpy(this->seriski, seriski);
        strcpy(this->tip, tip);
        this->cena = cena;
        this->godina = godina;
    }
    bool daliIsti(const Gitara &g){
        return strcmp(this->seriski, g.seriski)==0;
    }
    char *getSeriski(){
        return seriski;
    }
    double getNabavna(){
        return cena;
    }
    char* getTip(){
        return tip;
    }
    void pecati(){
        cout<<seriski<<" "<<tip<<" "<<cena<<endl;
    }
    int getGodina(){
        return godina;
    }
    double getCena(){
        return cena;
    }
    ~Gitara(){}
};

class Magacin{
    char ime[30];
    char lokacija[60];
    Gitara *g;
    int n;
    int godina;
public:
    Magacin(){
        n = 0;
        g = new Gitara[0];
    }
    Magacin(char *ime, char *lokacija, int godina){
        n=0;
        g = new Gitara[0];
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->lokacija, lokacija);
    }
    Magacin(char *ime, char *lokacija){
        godina = 0;
        n=0;
        g = new Gitara[0];
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->lokacija, lokacija);
    }
    Magacin(const Magacin &m){
        n=m.n;
        g = new Gitara[m.n];
        for(int i=0;i<n;i++){
            this->g[i] = m.g[i];
        }
        strcpy(this->ime, m.ime);
        this->godina = m.godina;
        strcpy(this->lokacija, m.lokacija);
    }
    Magacin& operator=(const Magacin &m){
        if(this!=&m){
            delete []g;
            n=m.n;
            g = new Gitara[m.n];
            for(int i=0;i<n;i++){
                this->g[i] = m.g[i];
            }
            strcpy(this->ime, m.ime);
            this->godina = m.godina;
            strcpy(this->lokacija, m.lokacija);
        }
        return *this;
    }
    double vrednost(){
        double suma=0;
        for(int i=0;i<n;i++){
            suma+=g[i].getNabavna();
        }
        return suma;
    }
    void dodadi(const Gitara &nova){
        Gitara *temp = new Gitara[n+1];
        for(int i=0;i<n;i++){
            temp[i] = g[i];
        }
        temp[n] = nova;
        delete []g;
        g = temp;
        n++;
    }
    void prodadi(Gitara &ex){
        int br=0;
        for(int i=0;i<n;i++){
            if(!ex.daliIsti(g[i]))
                br++;
        }
        Gitara *temp = new Gitara[br];
        int j=0;
        for(int i=0;i<n;i++){
            if(!ex.daliIsti(g[i])){
                temp[j] = g[i];
                j++;
            }
        }
        delete []g;
        g = temp;
        n = br;
    }
    void pecati(bool daliNovi){
        cout<<ime<<" "<<lokacija<<endl;
        if(daliNovi){
            for(int i=0;i<n;i++){
                if(g[i].getGodina() > godina){
                    g[i].pecati();
                }
            }
        }
        else{
            for(int i=0;i<n;i++){
                g[i].pecati();
            }
        }
    }
    ~Magacin(){
        delete []g;
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
