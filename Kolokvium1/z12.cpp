#include <iostream>
#include <cstring>

using namespace std;

class Pica{
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje;
public:
    Pica(){
        sostojki = new char[0];
    }
    Pica(char *ime, int cena, char *sostojki, int namaluvanje){
        this->sostojki = new char[strlen(sostojki)+1];
        strcpy(this->sostojki, sostojki);
        strcpy(this->ime, ime);
        this->cena = cena;
        this->namaluvanje = namaluvanje;
    }
    Pica(const Pica &p){
        this->sostojki = new char[strlen(p.sostojki)+1];
        strcpy(this->sostojki, p.sostojki);
        strcpy(this->ime, p.ime);
        this->cena = p.cena;
        this->namaluvanje = p.namaluvanje;
    }
    Pica& operator=(const Pica &p){
        if(this!=&p){
            delete []sostojki;
            this->sostojki = new char[strlen(p.sostojki)+1];
            strcpy(this->sostojki, p.sostojki);
            strcpy(this->ime, p.ime);
            this->cena = p.cena;
            this->namaluvanje = p.namaluvanje;
        }
        return *this;
    }
    void pecati(){
        cout << ime << " - " << sostojki << ", " << cena;
    }
    bool istiSe(Pica p){
        if(strcmp(sostojki, p.sostojki)==0){
            return 1;
        }else
            return 0;
    }
    void setNamaluvanje(int namaluvanje){
        this->namaluvanje = namaluvanje;
    }
    void setCena(int cena){
        this->cena = cena;
    }
    char *getIme(){
        return ime;
    }
    int getNamaluvanje(){
        return namaluvanje;
    }
    int getCena(){
        return cena;
    }
    ~Pica(){
        delete []sostojki;
    }
};

class Picerija{
    char imePicerija[15];
    Pica *pici;
    int n;
public:
    Picerija(const char *imePicerija = ""){
        strncpy(this->imePicerija, imePicerija, 14);
        this->imePicerija[14] = 0;
        pici = NULL;
        n = 0;
    }
    Picerija(const char *imePicerija, Pica* pici, int br) {
        strncpy(this->imePicerija, imePicerija, 14);
        this->imePicerija[14] = 0;
        this->n = n;
        this->pici = new Pica[n];
        for (int i = 0; i < n; i++)
            this->pici[i] = pici[i];
    }

    Picerija(const Picerija &p) {
        strcpy(imePicerija, p.imePicerija);
        n = p.n;
        pici = new Pica[n];
        for (int i = 0; i < n; i++)
            pici[i] = p.pici[i];
    }
    Picerija& operator= (const Picerija &p) {
        if (this != &p) {
            strcpy(imePicerija, p.imePicerija);
            n = p.n;
            delete[] pici;
            pici = new Pica[n];
            for (int i = 0; i < n; i++)
                pici[i] = p.pici[i];
        }
        return *this;
    }

    Picerija& operator+=(Pica &p){
        bool imaIsta = false;
        for (int i = 0; i < n; i++)
            if (pici[i].istiSe(p))
                imaIsta = true;
        if (!imaIsta)
        {
            Pica* tmp = new Pica[n + 1];
            for (int i = 0; i < n; i++)
                tmp[i] = pici[i];
            tmp[n++] = p;
            delete[] pici;
            pici = tmp;
        }
        return *this;
    }

    void piciNaPromocija() {
        for (int i = 0; i < n; i++){
            if (pici[i].getNamaluvanje() != 0){
                pici[i].pecati();
                cout << " " << pici[i].getCena() * (1 - pici[i].getNamaluvanje() / 100.0) << endl;
            }
        }

    }
    const char* getIme(){
        return imePicerija;
    }
    void setIme(const char* imePicerija){
        strncpy(this->imePicerija, imePicerija, 14);
        this->imePicerija[14] = 0;
    }
    ~Picerija() {
        delete[] pici;
    }
};
int main(){

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
