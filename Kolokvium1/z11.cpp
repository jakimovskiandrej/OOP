#include <iostream>
#include <cstring>
using namespace std;

class Ucesnik
{
private:
    char *ime;
    bool pol;
    int vozrast;
public:
    Ucesnik()
    {
        ime = new char[0];
    }
    Ucesnik(char *ime, bool pol, int vozrast)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->pol = pol;
        this->vozrast = vozrast;
    }
    Ucesnik(const Ucesnik &u)
    {
        this->ime = new char[strlen(u.ime)+1];
        strcpy(this->ime, u.ime);
        this->pol = u.pol;
        this->vozrast = u.vozrast;
    }
    Ucesnik& operator=(const Ucesnik &u)
    {
        if(this!=&u)
        {
            delete []ime;
            this->ime = new char[strlen(u.ime)+1];
            strcpy(this->ime, u.ime);
            this->pol = u.pol;
            this->vozrast = u.vozrast;
        }
        return *this;
    }
    bool operator>(Ucesnik &u1)
    {
        return this->vozrast > u1.vozrast;
    }
    friend ostream& operator<<(ostream &o, Ucesnik &uc)
    {
        o<<uc.ime<<endl;
        if(uc.pol == 0)
        {
            cout<<"zhenski"<<endl;
        }
        if(uc.pol == 1)
        {
            cout<<"mashki"<<endl;
        }
        o<<uc.vozrast<<endl;
        return o;
    }
    int getVozrast()
    {
        return vozrast;
    }
    ~Ucesnik()
    {
        delete []ime;
    }
};

class Maraton
{
private:
    char lokacija[100];
    Ucesnik *ucesnici;
    int n;
public:
    Maraton()
    {
        n = 0;
        ucesnici = new Ucesnik[0];
    }
    Maraton(char *lokacija)
    {
        n = 0;
        ucesnici = new Ucesnik[0];
        strcpy(this->lokacija, lokacija);
    }
    Maraton(const Maraton &m)
    {
        n = m.n;
        ucesnici = new Ucesnik[m.n];
        for(int i=0;i<n;i++)
        {
            this->ucesnici[i] = m.ucesnici[i];
        }
        strcpy(this->lokacija, m.lokacija);
    }
    Maraton& operator=(const Maraton &m)
    {
        if(this!=&m)
        {
            n = m.n;
            ucesnici = new Ucesnik[m.n];
            for(int i=0;i<n;i++)
            {
                this->ucesnici[i] = m.ucesnici[i];
            }
            strcpy(this->lokacija, m.lokacija);
        }
        return *this;
    }
    Maraton& operator+=(Ucesnik &nov)
    {
        Ucesnik *temp = new Ucesnik[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i] = ucesnici[i];
        }
        temp[n] = nov;
        n++;
        delete []ucesnici;
        ucesnici = temp;
        return *this;
    }
    double prosecnoVozrast()
    {
        double average = 0;
        for(int i=0;i<n;i++)
        {
            average+=ucesnici[i].getVozrast();
        }
        return average / n;
    }
    void pecatiPomladi(Ucesnik &u)
    {
        for(int i=0;i<n;i++)
        {
            if(ucesnici[i].getVozrast() < u.getVozrast())
            {
                cout<<ucesnici[i];
            }
        }
    }
    ~Maraton()
    {
        delete []ucesnici;
    }
};

int main()
{
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i)
    {
        delete u[i];
    }
    delete [] u;
    return 0;
}