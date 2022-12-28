#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person
{
private:
    int _id;
    string _Name;
    string _Phone;
    string _Gender;

        static int increamentId;
public:
    Person();
    Person(string, string, string);
    void setid(int id);
    int getid()const;
    void setName(string);
    const string& getName()const;
    void setPhone(string);
    const string getPhone()const;
    void setGender(string);
    const string getGender()const;
    virtual void print_extra_info();
};

#endif // PERSON_H
