#include "clsAuthor.h"

int clsAuthor::_idIncrementer = 1;

clsAuthor::clsAuthor()
{
    this->_id = _idIncrementer++;
}
clsAuthor::clsAuthor(string name, string phone, string email):_name(name),_phone(phone),_email(email)
{
    this->_id = _idIncrementer++;
};

int clsAuthor::getID()
{
    return this->_id;
}
void clsAuthor::setName(string name)
{
    this->_name = name;
}
string clsAuthor::getName()
{
    return this->_name;
}
void clsAuthor::setPhone(string phone)
{
    this->_phone = phone;
}
string clsAuthor::getPhone()
{
    return this->_phone;
}
void clsAuthor::setEmail(string email)
{
    this->_email = email;
}
string clsAuthor::getEmail()
{
    return this->_email;
}
