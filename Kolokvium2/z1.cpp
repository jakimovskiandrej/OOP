#include <iostream>
#include <cstring>

using namespace std;

class Book{
protected:
    char isbn[20];
    char title[50];
    char author[30];
    float cena;
public:
    Book(char *isbn="", char *title="", char *author="", float cena=0){
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->cena = cena;
    }
    friend bool operator>(const Book &k1, const Book &k2){
        return (k1.cena > k2.cena);
    }
    friend ostream& operator<<(ostream &o, Book &k){
        o<<k.isbn<<": "<<k.title<<", "<<k.author<<" "<<k.bookPrice()<<endl;
        return o;
    }
    float getPrice(){
        return cena;
    }
    void setISBN(char *isbn){
        strcpy(this->isbn, isbn);
    }
    virtual float bookPrice()=0;
    virtual ~Book(){}
    void pecati(){
        cout<<isbn<<": "<<title<<", "<<author<<" "<<bookPrice()<<endl;
    }
};

class OnlineBook : public Book{
private:
    char *url;
    int size;
public:
    OnlineBook(char *isbn="", char *title="", char *author="", float cena=0, char *url="", int size=0)
            : Book(isbn,title,author,cena){
        this->url = new char[strlen(url)+1];
        strcpy(this->url, url);
        this->size = size;
    }
    OnlineBook(const OnlineBook &ok) : Book(ok){
        this->url = new char[strlen(ok.url)+1];
        strcpy(this->url, ok.url);
        this->size = ok.size;
    }
    OnlineBook& operator=(const OnlineBook &ok){
        if(this!=&ok){
            delete []url;
            Book::operator=(ok);
            this->url = new char[strlen(ok.url)+1];
            strcpy(this->url, ok.url);
            this->size = ok.size;
        }
        return *this;
    }
    friend ostream& operator<<(ostream &o, OnlineBook &k){
        o<<k.isbn<<": "<<k.title<<", "<<k.author<<" "<<k.bookPrice()<<endl;
        return o;
    }
    float bookPrice(){
        if(size > 20){
            return (0.2 * getPrice())+getPrice();
        } else return getPrice();
    }
    ~OnlineBook(){
        delete []url;
    }
};

class PrintBook : public Book{
private:
    float weight;
    bool inStock;
public:
    PrintBook(char *isbn="", char *title="", char *author="", float cena=0, float weight=0, bool inStock=false)
            : Book(isbn,title,author,cena){
        this->weight = weight;
        this->inStock = inStock;
    }
    PrintBook(const PrintBook &pb): Book(pb){
        this->weight = pb.weight;
        this->inStock = pb.inStock;
    }
    friend ostream& operator<<(ostream &o, PrintBook &k){
        o<<k.isbn<<": "<<k.title<<", "<<k.author<<" "<<k.bookPrice()<<endl;
        return o;
    }
    float bookPrice(){
        if(weight > 0.7){
            return (0.15*getPrice())+getPrice();
        } else return getPrice();
    }
    ~PrintBook(){}
};

void mostExpensiveBook(Book** books, int n)
{
    float maxKniga=0;
    int maxIndex=0;
    int online=0;
    int pecatena=0;
    for(int i=0;i<n;i++){
        if(OnlineBook* onlineBook = dynamic_cast<OnlineBook*>(books[i])){
            online++;
        }else{
            pecatena++;
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<pecatena<<endl;
    for (int i = 0 ; i < n ; i++)
    {
        if (books[i]->bookPrice() > maxKniga){
            maxKniga=books[i]->bookPrice();
            maxIndex=i;
        }
    }
    cout<<"The most expensive book is:"<<endl;
    books[maxIndex]->pecati();
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){

        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;

    }
    if (testCase == 3){

        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];

    }
    if (testCase == 4){

        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
