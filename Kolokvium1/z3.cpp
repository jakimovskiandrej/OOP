#include <iostream>
#include <cstring>
using namespace std;

class StockRecord
{
private:
    char id[12];
    char company[50];
    double price;
    double currPrice;
    int shares;
public:
    StockRecord(){}
    StockRecord(char *id, char *company, double currPrice, int shares)
    {
        strcpy(this->id, id);
        strcpy(this->company, company);
        this->currPrice = currPrice;
        this->shares = shares;
    }
    StockRecord(const StockRecord &sr)
    {
        strcpy(this->id, sr.id);
        strcpy(this->company, sr.company);
        this->currPrice = sr.currPrice;
        this->shares = sr.shares;
    }
    StockRecord& operator=(const StockRecord &sr)
    {
        if(this!=&sr)
        {
            strcpy(this->id, sr.id);
            strcpy(this->company, sr.company);
            this->currPrice = sr.currPrice;
            this->shares = sr.shares;
        }
        return *this;
    }
    int getShares()
    {
        return shares;
    }
    void setNewPrice(double c)
    {
        currPrice = c;
    }
    double value()
    {
        return shares * price;
    }
    double profit()
    {
        return shares * (currPrice - price);
    }
    friend ostream& operator<<(ostream &o, StockRecord &s)
    {
        o<<s.company<<" "<<s.shares<<" "<<" "<<s.price<<" "<<s.currPrice<<" "<<s.profit()<<endl;
        return o;
    }
    ~StockRecord(){}
};

class Client
{
private:
    char clientName[50];
    int clientID;
    StockRecord *records;
    int n;
public:
    Client()
    {
        n = 0;
        records = new StockRecord[0];
    }
    Client(char *clientName, int clientID)
    {
        n = 0;
        records = new StockRecord[0];
        strcpy(this->clientName, clientName);
        this->clientID = clientID;
    }
    Client(const Client &c)
    {
        n = c.n;
        records = new StockRecord[c.n];
        for(int i=0;i<n;i++)
        {
            this->records[i] = c.records[i];
        }
        strcpy(this->clientName, c.clientName);
        this->clientID = c.clientID;
    }
    Client& operator=(const Client &c)
    {
        if(this!=&c)
        {
            delete []records;
            n = c.n;
            records = new StockRecord[c.n];
            for(int i=0;i<n;i++)
            {
                this->records[i] = c.records[i];
            }
            strcpy(this->clientName, c.clientName);
            this->clientID = c.clientID;
        }
        return *this;
    }
    double totalValue()
    {
        double suma = 0;
        for(int i=0;i<n;i++)
        {
            suma+=records[i].value();
        }
        return suma;
    }
    Client& operator+=(StockRecord &nov)
    {
        StockRecord *temp = new StockRecord[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i] = records[i];
        }
        temp[n] = nov;
        n++;
        delete []records;
        records = temp;
        return *this;
    }
    friend ostream& operator<<(ostream &o, Client &c)
    {
        o<<c.clientID<<" "<<c.totalValue()<<endl;
        for(int i=0;i<c.n;i++)
        {
            o<<c.records[i]<<endl;
        }
        return o;
    }
    ~Client()
    {
        delete []records;
    }
};

int main()
{

    int test;
    cin >> test;

    if(test == 1)
    {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2)
    {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i)
        {
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3)
    {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i)
        {
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag)
            {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
