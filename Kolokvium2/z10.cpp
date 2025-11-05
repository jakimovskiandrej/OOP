#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class NegativnaVrednost{
private:
    char *msg;
public:
    NegativnaVrednost(char *msg){
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg, msg);
    }
    void message(){
        cout<<msg<<endl;
    }
    ~NegativnaVrednost(){
        delete []msg;
    }
};
class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
public:
    Oglas(char *naslov="", char *kategorija="", char *opis="", float cena=0){
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena = cena;
    }
    Oglas(const Oglas &o){
        strcpy(this->naslov, o.naslov);
        strcpy(this->kategorija, o.kategorija);
        strcpy(this->opis, o.opis);
        this->cena = o.cena;
    }
    float getCena(){
        return cena;
    }
    char* getNaziv(char *naslov){
        return naslov;
    }
    char* getKategorija(){
        return kategorija;
    }
    char* getOpis(){
        return opis;
    }
    bool operator>(Oglas &o1){
        return (this->cena > o1.cena);
    }
    friend ostream& operator<<(ostream &o, Oglas &og){
        o<<og.naslov<<endl<<og.opis<<endl<<og.cena<<" evra "<<endl;
        return o;
    }
    ~Oglas(){}
};

class Oglasnik{
private:
    char naziv[20];
    Oglas *oglasi;
    int n;
public:
    Oglasnik(){
        oglasi = new Oglas[0];
        n = 0;
    }
    Oglasnik(char *naziv=""){
        strcpy(this->naziv, naziv);
        oglasi = new Oglas[0];
        n = 0;
    }
    Oglasnik(const Oglasnik& o){
        strcpy(this->naziv, o.naziv);
        this->n = o.n;
        oglasi  = new Oglas[o.n];
        for(int i=0;i<o.n;i++){
            this->oglasi[i] = o.oglasi[i];
        }
    }
    Oglasnik& operator=(const Oglasnik& o){
        if(this!=&o){
            delete []oglasi;
            strcpy(this->naziv, o.naziv);
            this->n = o.n;
            oglasi  = new Oglas[o.n];
            for(int i=0;i<o.n;i++){
                this->oglasi[i] = o.oglasi[i];
            }
        }
        return *this;
    }
    Oglasnik& operator+=(Oglas &o){
        if(o.getCena()<0){
            throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
        }
        Oglas *temp = new Oglas[n+1];
        for(int i=0;i<n;i++){
            temp[i] = oglasi[i];
        }
        temp[n++] = o;
        delete []oglasi;
        oglasi = temp;
        return *this;
    }
    friend ostream& operator<<(ostream &out, const Oglasnik &ogl){
        out<<ogl.naziv<<endl;
        for(int i=0;i<ogl.n;i++){
            out<<ogl.oglasi[i]<<endl;
        }
        return out;
    }
    ~Oglasnik(){
        delete []oglasi;
    }
    void oglasiOdKategorija(const char *k){
        for(int i=0;i<n;i++){
            if(strcmp(oglasi[i].getKategorija(), k)==0){
                cout<<oglasi[i]<<endl;
            }
        }
    }
    void najniskaCena(){
        int index=0;
        int max=oglasi[0].getCena();
        for(int i=1;i<n;i++){
            if(oglasi[i].getCena() < max){
                max = oglasi[i].getCena();
                index = i;
            }
        }
        cout<<oglasi[index];
    }
};


int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){

        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==4){

        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){

        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &ne)
            {
                ne.message();
            }
        }
        cout<<ogl;


    }
    else if (tip==6){

        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &ne)
            {
                ne.message();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){

        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch(NegativnaVrednost &ne)
            {
                ne.message();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    return 0;
}
