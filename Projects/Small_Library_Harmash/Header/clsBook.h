#ifndef CLSBOOK_H
#define CLSBOOK_H
#include "clsAuthor.h"
#include <string>
using namespace std;
class clsBook
{
private:
    int _id;
    string _title;
    string _publishing_date;
    int _version;
    clsAuthor _author;

    static int _idIncrementer;
public:
    clsBook();
    clsBook(string ,string,int, const clsAuthor&);
    int getID();
    void setTile(string);
    string getTitle();
    void setPublishDate(string);
    string getPublishDate();
    void setVersion(int);
    int getVersion();
    void setBookAuthor(const clsAuthor& author);
    clsAuthor getBookAuthor();
};



#endif // CLSBOOK_H
