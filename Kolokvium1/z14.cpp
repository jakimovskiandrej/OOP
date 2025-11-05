#include<iostream>
#include<cstring>

using namespace std;


enum Extension{PDF,TXT,EXE};

class File
{
private:
    char *fileName;
    char *fileOwner;
    Extension ext;
    int fileSize;
public:
    File()
    {
        fileName = new char[0];
        fileOwner = new char[0];
        fileSize=0;
    }
    File(char *fileName,char *fileOwner,int fileSize,Extension ext)
    {
        this->fileName = new char[strlen(fileName)+1];
        strcpy(this->fileName,fileName);
        this->fileOwner = new char[strlen(fileOwner)+1];
        strcpy(this->fileOwner,fileOwner);
        this->fileSize = fileSize;
        this->ext = ext;
    }
    File(const File &f)
    {
        this->fileName = new char[strlen(f.fileName)+1];
        strcpy(this->fileName,f.fileName);
        this->fileOwner = new char[strlen(f.fileOwner)+1];
        strcpy(this->fileOwner,f.fileOwner);
        this->fileSize = f.fileSize;
        this->ext = f.ext;
    }
    File& operator=(const File &f)
    {
        if(this!=&f)
        {
            delete []fileName;
            delete []fileOwner;
            this->fileName = new char[strlen(f.fileName)+1];
            strcpy(this->fileName,f.fileName);
            this->fileOwner = new char[strlen(f.fileOwner)+1];
            strcpy(this->fileOwner,f.fileOwner);
            this->fileSize = f.fileSize;
            this->ext = f.ext;
        }
        return *this;
    }
    void print()
    {
        cout<<"File name: "<<fileName<<".";
        if(ext==TXT)
            cout<<"txt"<<endl;
        else if(ext==PDF)
            cout<<"pdf"<<endl;
        else if(ext==EXE)
            cout<<"exe"<<endl;
        cout<<"File owner: "<<fileOwner<<endl;
        cout<<"File size: "<<fileSize<<endl;
    }
    bool equalsType(const File &f)
    {
        return strcmp(this->fileName,f.fileName)==0 && this->ext == f.ext;
    }
    bool equals(const File &f)
    {
        return strcmp(this->fileName,f.fileName)==0 && this->ext == f.ext && strcmp(this->fileOwner,f.fileOwner)==0;
    }
    ~File()
    {
        delete []fileName;
        delete []fileOwner;
    }
};

class Folder
{
private:
    char *ime;
    File *files;
    int n;
public:
    Folder()
    {
        n=0;
        files = new File[0];
    }
    Folder(char *ime)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        n=0;
        files = new File[0];
    }
    Folder(const Folder &f)
    {
        this->ime = new char[strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        n=f.n;
        files = new File[f.n];
        for(int i=0;i<n;i++)
        {
            this->files[i] = f.files[i];
        }
    }
    Folder& operator=(const Folder &f)
    {
        if(this!=&f)
        {
            delete []files;
            this->ime = new char[strlen(f.ime)+1];
            strcpy(this->ime,f.ime);
            n=f.n;
            files = new File[f.n];
            for(int i=0;i<n;i++)
            {
                this->files[i] = f.files[i];
            }
        }

        return *this;
    }
    void print()
    {
        cout<<"Folder name: "<<ime<<endl;
        for(int i=0;i<n;i++)
        {
            files[i].print();
        }
    }

    void remove(const File &file)
    {
        int najde=0;
        for(int i=0;i<n;i++)
        {
            if(files[i].equals(file))
            {
                najde=1;
                break;
            }
        }
        if(najde==1)
        {
            int prva=0;
            File *temp = new File[n-1];
            int j=0;
            for(int i=0;i<n;i++)
            {
                if(files[i].equals(file) && prva==0)
                {
                    prva = 1;
                }
                else if( prva==1)
                {
                    temp[j] = files[i];
                    j++;
                }
                else if(!files[i].equals(file))
                {
                    temp[j] = files[i];
                    j++;
                }
            }
            delete []files;
            n--;
            files = temp;
        }
    }
    void add(const File &nov)
    {
        File *temp = new File[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i] = files[i];
        }
        temp[n] = nov;
        n++;
        delete []files;
        files = temp;
    }
    ~Folder()
    {
        delete []files;
    }
};
int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
