#ifndef CLSAUTHOR_H
#define CLSAUTHOR_H
#include <string>
using namespace std;
class clsAuthor
{
private:

    int _id;
    string _name;
    string _phone;
    string _email;

    static int _idIncrementer;
public:
    clsAuthor();
    clsAuthor(string name, string phone, string email);
    int getID();
    void setName(string name);
    string getName();
    void setPhone(string phone);
    string getPhone();
    void setEmail(string email);
    string getEmail();

};
#endif // CLSAUTHOR_H
