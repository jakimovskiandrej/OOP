#include <iostream>
#include <cstring>
using namespace std;
class Pizza
{
protected:
    char name[100];
    char ingredients[100];
    double inPrice;
public:
    Pizza(){}
    Pizza(char *name, char *ingredients, double inPrice)
    {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->inPrice = inPrice;
    }
    Pizza(const Pizza &p)
    {
        strcpy(this->name, p.name);
        strcpy(this->ingredients, p.ingredients);
        this->inPrice = p.inPrice;
    }
    Pizza& operator=(const Pizza &p)
    {
        if(this!=&p)
        {
            strcpy(this->name, p.name);
            strcpy(this->ingredients, p.ingredients);
            this->inPrice = p.inPrice;
        }
        return *this;
    }
    virtual double price()
    {
        return this->inPrice;
    }
    friend ostream& operator<<(ostream &o, Pizza &p)
    {
        o<<p.name<<": "<<p.ingredients<<", ";
        return o;
    }
    bool operator<(Pizza &p1)
    {
        if(this->price() < p1.price())
        {
            return true;
        }
        else return false;
    }
    ~Pizza(){}
};

enum Size {MALA,GOLEMA,FAMILIJARNA};
class FlatPizza : public Pizza
{
private:
    Size s;
public:
    FlatPizza(char *name, char *ingredients, double inPrice, Size s = (Size)0)
            : Pizza(name,ingredients,inPrice)
    {
        this->s = s;
    }
    FlatPizza(const FlatPizza &fp): Pizza(fp)
    {
        this->s = fp.s;
    }
    double price()
    {
        double osnovna = Pizza::price();
        if(s == MALA)
        {
            return osnovna + (osnovna * 0.1);
        }
        if(s == GOLEMA)
        {
            return osnovna + (osnovna * 0.2);
        }
        if(s == FAMILIJARNA)
        {
            return osnovna + (osnovna * 0.3);
        }
    }
    friend ostream& operator<<(ostream &o, FlatPizza &p)
    {
        o<<p.name<<": "<<p.ingredients<<", ";
        if(p.s==MALA)
        {
            o<<"small ";
        }
        else if(p.s==GOLEMA)
        {
            o<<"big ";
        }
        else if(p.s==FAMILIJARNA)
        {
            o<<"family ";
        }
        o<<"- "<<p.price();
        o<<endl;
        return o;
    }
    ~FlatPizza(){}
};

class FoldedPizza : public Pizza
{
private:
    bool whiteFlour;
public:
    FoldedPizza(char *name, char *ingredients, double inPrice)
            : Pizza(name,ingredients,inPrice)
    {
        this->whiteFlour = true;
    }
    void setWhiteFlour(bool whiteFlour)
    {
        this->whiteFlour = whiteFlour;
    }
    double price()
    {
        double osnovna = Pizza::price();
        if(whiteFlour==true)
        {
            return osnovna + (osnovna*0.1);
        }
        else
        {
            return osnovna + (osnovna*0.3);
        }
    }
    friend ostream& operator<<(ostream &o, FoldedPizza &p)
    {
        o<<p.name<<": "<<p.ingredients<<", ";
        if(p.whiteFlour == true)
        {
            o<<"wf ";
        }
        else
        {
            o<<"nwf ";
        }
        o<<"- "<<p.price();
        o<<endl;
        return o;
    }
    ~FoldedPizza(){}
};

void expensivePizza(Pizza **pici, int n)
{
    double max = pici[0]->price();
    int index = 0;
    for(int i=0;i<n;i++)
    {
        if(pici[i]->price() > max)
        {
            max = pici[i]->price();
            index = i;
        }
    }
    FlatPizza *p1 = dynamic_cast<FlatPizza*>(pici[index]);
    if(p1!=0)
    {
        cout<<*p1;
    }
    FoldedPizza *p2 = dynamic_cast<FoldedPizza*>(pici[index]);
    if(p2!=0)
    {
        cout<<*p2;
    }
}
int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
