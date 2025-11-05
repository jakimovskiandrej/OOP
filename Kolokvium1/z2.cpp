#include <iostream>
using namespace std;
class List {
private:
    int *niza;
    int broj;
public:
    List()
    {
        this->broj=0;
        this->niza=new int[0];
    }
    List(int *niza,int broj)
    {
        this->broj=broj;
        this->niza=new int[broj];
        for(int i=0;i<broj;i++)
        {
            this->niza[i]=niza[i];
        }
    }
    List (const List &l)
    {
        this->broj=l.broj;
        this->niza=new int[broj];
        for(int i=0;i<broj;i++)
        {
            this->niza[i]=l.niza[i];
        }
    }
    List &operator=(const List &l)
    {
        if(this!=&l)
        {
            this->broj=l.broj;
            delete[]niza;
            this->niza=new int[broj];
            for(int i=0;i<broj;i++)
            {
                this->niza[i]=l.niza[i];
            }
        }
        return *this;
    }
    ~List(){delete []niza;}
    int sum()
    {
        int s=0;
        for(int i=0;i<broj;i++)
        {
            s+=niza[i];
        }
        return s;
    }
    double average()
    {
        return sum()/(float)broj;
    }

    void pecati()
    {
        cout<<broj<<": ";
        for(int i=0;i<broj;i++)
        {
            cout<<niza[i]<<" ";
        }
        cout<<"sum: "<< sum()<<" average: "<<average()<<endl;
    }
    int getBroj()
    {
        return broj;
    }
};
class ListContainer
{
private:
    List *listi;
    int n;
    int attempts;
public:
    ListContainer()
    {
        this->n=0;
        this->listi=new List[0];
        this->attempts=0;
    }
    ListContainer(List *listi,int n,int attempts)
    {
        this->n=n;
        this->listi=new List[n];
        for(int i=0;i<n;i++)
        {
            this->listi[i]=listi[i];
        }
        this->attempts=attempts;
    }
    ListContainer(const ListContainer &l)
    {
        this->n=l.n;
        this->attempts=l.attempts;
        this->listi=new List[n];
        for(int i=0;i<n;i++)
        {
            this->listi[i]=l.listi[i];
        }
    }
    ListContainer& operator=(const ListContainer &l)
    {
        if(this!=&l)
        {
            this->n=l.n;
            this->attempts=l.attempts;
            delete[]listi;
            this->listi=new List[n];
            for(int i=0;i<n;i++)
            {
                this->listi[i]=l.listi[i];
            }
        }
        return *this;

    }
    void addNewList(List &nova)
    {
        attempts++;
        int s=nova.sum();
        for(int i=0;i<n;i++)
        {
            if(s==listi[i].sum())
                return;
        }
        List *temp=new List[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i]=listi[i];
        }
        temp[n]=nova;
        delete[]listi;
        listi=temp;
        n++;
    }
    int sum()
    {
        int suma=0;
        for(int i=0;i<n;i++)
        {
            suma+=listi[i].sum();
        }
        return suma;
    }
    double average()
    {
        int vkupen=0;
        for(int i=0;i<n;i++)
        {
            vkupen+=listi[i].getBroj();
        }
        return sum()/(float)vkupen;
    }


    void print()
    {
        if(n==0)
        {
            cout<<"The list is empty"<<endl;
            return;
        }
        else
        {
            for(int i=0;i<n;i++)
            {
                cout<<"List number: "<<i+1<<" List info: ";
                listi[i].pecati();
            }
            cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<n<<" Failed attempts: "<<attempts-n<<endl;
        }
    }




    ~ListContainer(){delete []listi;}
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}


