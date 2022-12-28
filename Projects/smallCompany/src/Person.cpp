#include <iostream>
#include "Person.h"
int Person::increamentId = 1;
Person::Person(string name, string phone, string gender ):_Name(name),_Phone(phone),_Gender(gender)
{
this->_id = increamentId++;
}
void Person::setid(int id)
{
    this->_id = id;
}
int Person::getid()const
{
    return _id;
}
void Person::setName(string name)
{
    this->_Name = name;

}
const string& Person::getName()const
{
    return   this->_Name;
}
void Person::setPhone(string phone)
{
    this->_Phone = phone;
}
const string Person::getPhone()const
{
    return this->_Phone;
}

void Person::setGender(string gender)
{
    this->_Gender = gender;
}
const string Person::getGender()const
{
    return this->_Gender;
}

void Person::print_extra_info()
{
    std::cout << "Person Class\n";
}
