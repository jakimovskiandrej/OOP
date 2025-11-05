#include <iostream>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;
struct Laptop
{
    char firma[100];
    float dim;
    bool touch;
    int cena;
};

struct ITStore
{
    char ime[100];
    char lokacija[100];
    Laptop l[100];
    int brLaptopi;
};

void print(ITStore *it,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<it[i].ime<<" "<<it[i].lokacija<<endl;
        for(int j=0;j<it[i].brLaptopi;j++)
        {
            cout<<it[i].l[j].firma<<" "<<it[i].l[j].dim<<" "<<it[i].l[j].cena<<endl;
        }
    }
}

void najevtina_ponuda(ITStore *it,int n)
{
    int min = INT_MAX;
    int index;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<it[i].brLaptopi;j++)
        {
            if(it[i].l[j].touch)
            {
                if(it[i].l[j].cena < min)
                {
                    min = it[i].l[j].cena;
                    index = i;
                }
            }

        }
    }
    cout<<"Najeftina ponuda ima prodavnicata: "<<endl;
    cout<<it[index].ime<<" "<<it[index].lokacija<<endl;
    cout<<"Najniskata cena iznesuva: "<<min<<endl;
}

int main() {
    ITStore s[100];
    int n;
    cin >> n; //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i = 0; i < n; i++){
        cin >> s[i].ime;
        cin >> s[i].lokacija;
        cin >> s[i].brLaptopi;
        for(int j = 0; j < s[i].brLaptopi; j++){
            cin >> s[i].l[j].firma;
            cin >> s[i].l[j].dim;
            cin >> s[i].l[j].touch;
            cin >> s[i].l[j].cena;
        }

    }


    //pecatenje na site prodavnici

    print(s, n);


    //povik na glavnata metoda

    najevtina_ponuda(s,n);

    return 0;
}
