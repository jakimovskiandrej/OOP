#include <iostream>
#include <cstring>

using namespace std;

class Koncert{
private:
    char naziv[20];
    char lokacija[20];
    static float popust;
    float cenaBilet;
public:
    Koncert(){}
    Koncert(char *naziv, char *lokacija, float cenaBilet){
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->cenaBilet = cenaBilet;
    }
    virtual float cena(){
        return cenaBilet-(cenaBilet*popust);
    }
    float getCena(){
        return cenaBilet;
    }
    char* getNaziv(){
        return naziv;
    }
    static float getSezonskiPopust(){
        return popust;
    }
    static void setSezonskiPopust(float novPopust){
        popust = novPopust;
    }
    virtual ~Koncert(){}
};

float Koncert::popust = 0.2;

class ElektronskiKoncert : public Koncert{
private:
    char *imeDJ;
    float casovi;
    bool dnevna;
public:
    ElektronskiKoncert() : Koncert(){
        imeDJ = new char[0];
    }
    ElektronskiKoncert(char *naziv, char *lokacija, float cenaBilet, char *imeDJ, float casovi, bool dnevna)
            : Koncert(naziv,lokacija,cenaBilet){
        this->imeDJ = new char[strlen(imeDJ)+1];
        strcpy(this->imeDJ, imeDJ);
        this->casovi = casovi;
        this->dnevna = dnevna;
    }
    float cena(){
        float total = Koncert::cena();
        if(casovi>7){
            total+=360;
        }else if(casovi>5){
            total+=150;
        }
        if(dnevna){
            total-=50;
        }else{
            total+=100;
        }
        return total;
    }
    ~ElektronskiKoncert(){
        delete []imeDJ;
    }
};

void najskapKoncert(Koncert ** koncerti, int n){
    int index=0;
    float max=koncerti[0]->getCena();
    int br=0;
    for(int i=0;i<n;i++){
        ElektronskiKoncert *ek=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(ek!=0){
            br++;
        }
        if(koncerti[i]->cena()>max){
            max=koncerti[i]->cena();
            index = i;
        }
    }
    cout<<"Najskap koncert: "<<koncerti[index]->getNaziv()<<" "<<koncerti[index]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<br<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    for(int i=0;i<n;i++){
        if(elektronski){
            ElektronskiKoncert *ek = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
            if(ek!=0){
                if(strcmp(ek->getNaziv(), naziv)==0){
                    cout<<ek->getNaziv()<<" "<<ek->cena()<<endl;
                    return true;
                }
            }
        }else{
            if(strcmp(koncerti[i]->getNaziv(), naziv)==0){
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }
    }
    return false;
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        //Koncert::setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
