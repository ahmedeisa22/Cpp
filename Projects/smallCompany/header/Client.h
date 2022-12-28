#ifndef CLIENT_H
#define CLIENT_H
#include "Person.h"

class Client: public Person
{
private:
    string _email;

public:
    Client(string name, string phone, string gender,string email);
    void setEmail(string);
    const string& getEmail()const;
     void print_extra_info();
};

#endif // CLIENT_H
