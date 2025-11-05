#include <iostream>
#include <cstring>

using namespace std;

class SMS{
protected:
    char tel[20];
    float price;
    const static int DDV;
public:
    SMS(char *tel="", float price=0){
        strcpy(this->tel, tel);
        this->price = price;
    }
    friend ostream& operator<<(ostream &o,SMS &s){
        o<<"Tel: "<<s.tel<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
        return o;
    }
    virtual float SMS_cena()=0;
    virtual ~SMS(){}
};

const int SMS::DDV = 18;

class RegularSMS : public SMS{
private:
    bool roam;
    char msg[1000];
    static int regProcent;
public:
    RegularSMS(char *tel="",float price=0,char *msg="", bool roam=false)
            : SMS(tel,price){
        this->roam = roam;
        strcpy(this->msg, msg);
    }
    static void set_rProcent(int r){
        regProcent = r;
    }
    float SMS_cena(){
        float pr;
        if(roam){
            pr = price + price*regProcent/100;
        }else{
            pr = price + price*DDV/100;
        }
        int brPoraki = strlen(msg)/160;
        if(strlen(msg)%160!=0){
            brPoraki++;
        }
        return pr*brPoraki;
    }
};

int RegularSMS::regProcent = 300;

class SpecialSMS : public SMS{
private:
    bool hum;
    static int specProcent;
public:
    SpecialSMS(char *tel="", float price=0, bool hum=false)
            : SMS(tel,price){
        this->hum = hum;
    }
    static void set_sProcent(int p){
        specProcent = p;
    }
    float SMS_cena(){
        float pr;
        if(hum){
            pr = price;
        }else{
            pr = price + price*specProcent/100;
        }
        return pr;
    }
    ~SpecialSMS(){}
};

int SpecialSMS::specProcent = 150;

void vkupno_SMS(SMS **sms, int n){
    int brR=0;
    float vkR=0;
    float vkS=0;
    int brS=0;
    for(int i=0;i<n;i++){
        RegularSMS *r = dynamic_cast<RegularSMS*>(sms[i]);
        if(r!=0){
            brR++;
            vkR+=r->SMS_cena();
        }else{
            SpecialSMS *s = dynamic_cast<SpecialSMS*>(sms[i]);
            brS++;
            vkS+=s->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<brR<<" regularni SMS poraki i nivnata cena e: "<<vkR<<endl;
    cout<<"Vkupno ima "<<brS<<" specijalni SMS poraki i nivnata cena e: "<<vkS<<endl;
}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
