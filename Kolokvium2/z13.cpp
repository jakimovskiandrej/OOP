#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image{
protected:
    char *title;
    char user[50];
    int width;
    int heigth;
public:
    Image(char *title = "untitled",char user[50]="unknown", int width=800, int heigth=800){
        this->title = new char[strlen(title)];
        strcpy(this->title,title);
        strcpy(this->user,user);
        this->width=width;
        this->heigth=heigth;
    }
    virtual int filesize(){
        return width*heigth*3;
    }
    friend ostream &operator<<(ostream &os, Image &i){
        os<<i.title<<" "<<i.user<<" "<<i.filesize()<<endl;
        return os;
    }
    friend ostream &operator<<(ostream &os, Image *i){
        os<<i->title<<" "<<i->user<<" "<<i->filesize()<<endl;
        return os;
    }
    bool operator>(Image &i){
        return this->filesize()>i.filesize();
    }

};
class TransparentImage : public Image{
private:
    bool transparent;
public:
    TransparentImage(char *title ,char user[50], int width, int heigth,bool transparent = true) : Image(title,user,width,heigth){
        this->transparent=transparent;
    }
    TransparentImage():Image(){
        transparent=true;
    }
    int filesize(){
        return transparent ? width*heigth*4 : width*heigth+(width*heigth)/8;
    }
};

class Folder{
private:
    char title[255];
    char user[50];
    Image **images;
    int num;
public:
    Folder(char title[255], char user[50]="unknown"){
        strcpy(this->title,title);
        strcpy(this->user,user);
        this->num=0;
    }
    Folder(){
        strcpy(this->user,"unknown");
        this->num=0;
    }
    Folder& operator+=(Image &im){
        Image **temp = new Image*[num+1];
        for(int i=0;i<num;i++){
            temp[i]=images[i];
        }
        if(num!=0) delete [] images;
        temp[num++] = &im;
        images=temp;
        return *this;
    }
    int folderSize() const{
        int size = 0;
        for(int i=0;i<num;i++){;
            size+=images[i]->filesize();
        }
        return size;
    }
    Image* getMaxFile(){
        if(num==0) return NULL;
        if(num==1) return images[0];
        Image *max = images[0];
        for(int i=1;i<num;i++){
            if(*images[i]>*max){
                max=images[i];
            }
        }
        return max;
    }
    friend ostream& operator<<(ostream &os,const Folder &f){
        os<<f.title<<" "<<f.user<<endl<<"--"<<endl;
        for(int i=0;i<f.num;i++){
            os<<f.images[i];
        }
        os<<"--"<<endl<<"Folder size: "<<f.folderSize()<<endl;
        return os;
    }
    Image* operator[](int index){
        if(index<0 || index>=num) return NULL;
        return images[index];
    }
};

Folder max_folder_size(Folder *folders, int num){
    if(num==1) return folders[0];
    Folder f = folders[0];
    for(int i=0;i<num;i++){
        if(folders[i].folderSize()>f.folderSize()){
            f=folders[i];
        }
    }
    return f;
}
int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
