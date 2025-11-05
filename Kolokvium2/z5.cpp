#include <iostream>
#include <cstring>
#define MAX 50
using namespace std;

class UserExistsException{
public:
    UserExistsException(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

enum typeC{STANDARD,LOYAL,VIP};

class Customer{
private:
    char ime[50];
    char adresa[50];
    typeC tC;
    static int osnoven;
    const static int dopolnitelen;
    int brKupeni;
public:
    Customer(){}
    Customer(char *ime, char *adresa, typeC tC, int brKupeni){
        strcpy(this->ime, ime);
        strcpy(this->adresa, adresa);
        this->tC = tC;
        this->brKupeni = brKupeni;
    }
    static void setDiscount1(int o){
        osnoven = o;
    }
    void setVid(typeC nov){
        this->tC = nov;
    }
    typeC getTip(){
        return tC;
    }
    char* getAdresa(){
        return adresa;
    }
    int getBrKupeni(){
        return brKupeni;
    }
    char* getIme(){
        return ime;
    }
    friend ostream& operator<<(ostream &o, Customer &c){
        o<<c.ime<<endl;
        o<<c.adresa<<endl;
        o<<c.brKupeni<<endl;
        int popust=0;
        if(c.tC==0){
            o<<"standard ";
        }
        if(c.tC==1){
            o<<"loyal ";

        }
        if(c.tC==2){
            o<<"vip ";

        }
        if(c.tC==LOYAL){
            o<<osnoven<<endl;
        }
        else if(c.tC==VIP){
            o<<dopolnitelen+osnoven<<endl;
        }
        else{
            o<<"0"<<endl;
        }
        return o;
    }
    ~Customer(){}
};

int Customer::osnoven = 10;
const int Customer::dopolnitelen = 20;

class FINKI_bookstore{
private:
    Customer *kupuvaci;
    int n;
public:
    FINKI_bookstore(){
        n = 0;
        kupuvaci = new Customer[0];
    }
    FINKI_bookstore(Customer *kupuvaci, int n){
        this->n = n;
        this->kupuvaci = new Customer[n];
        for(int i=0;i<n;i++){
            this->kupuvaci[i] = kupuvaci[i];
        }
    }
    FINKI_bookstore& operator+=(Customer &nov){
        for(int i=0;i<n;i++){
            if(strcmp(kupuvaci[i].getAdresa(), nov.getAdresa())==0){
                throw UserExistsException();
            }
        }
        Customer *temp = new Customer[n+1];
        for(int i=0;i<n;i++){
            temp[i] = kupuvaci[i];
        }
        temp[n++] = nov;
        delete []kupuvaci;
        kupuvaci = temp;
        return *this;
    }
    void update(){
        for(int i=0;i<n;i++){
            if(kupuvaci[i].getBrKupeni() > 5 && kupuvaci[i].getTip()==STANDARD){
                kupuvaci[i].setVid(LOYAL);
            }else if(kupuvaci[i].getBrKupeni() > 10 && kupuvaci[i].getTip()==LOYAL){
                kupuvaci[i].setVid(VIP);
            }
        }
    }
    Customer* setCustomers(Customer niza[], int n){
        this->n = n;
        this->kupuvaci = new Customer[n];
        for(int i=0;i<this->n;i++){
            this->kupuvaci[i] = niza[i];
        }
        return kupuvaci;
    }
    friend ostream& operator<<(ostream &o, FINKI_bookstore &fc){
        for(int i=0;i<fc.n;i++){
            o<<fc.kupuvaci[i];
        }
        return o;
    }
    ~FINKI_bookstore(){
        delete []kupuvaci;
    }
};
int main()
{
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1)
    {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2)
    {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3)
    {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4)
    {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try
        {
            fc+=c;
        }
        catch(UserExistsException e)
        {

        }

        cout << fc;
    }

    if (testCase == 5)
    {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try
        {
            fc+=c;
        }
        catch(UserExistsException e)
        {

        }

        cout << fc;
    }

    if (testCase == 6)
    {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
