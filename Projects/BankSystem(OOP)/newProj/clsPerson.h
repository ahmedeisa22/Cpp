#pragma once
#include <iostream>
#include "clsInterfaceCommunication.h"
using namespace std;

class clsPerson: public InterfaceCommunication
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;
public:
	clsPerson(string firstName, string lastName,string Email,string phone):
		_FirstName(firstName),_LastName(lastName),_Email(Email),_Phone(phone)
	{}

	// property set & get
	void setFirstName(string firstName) {
		this->_FirstName = firstName;
	}
	string getFirstName()const {
		return this->_FirstName;
	}
	__declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	void setLastName(string lastName) {
		_LastName = lastName;
	}
	string getLastName()const {
		return _LastName;
	}
	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	void setEmail(string email) {
		_Email = email;
	}
	string getEmail()const {
		return _Email;
	}
	__declspec(property(get = getEmail, put = setEmail)) string Email;

	void setPhone(string phone){
		_Phone = phone;
		}
	string getPhone()const {
		return _Phone;
	}
	__declspec(property(get = getPhone, put = setPhone)) string Phone;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}

	void Print()
	{
		cout << "\nInfo:";
		cout << "\n___________________";
		cout << "\nFirstName: " << _FirstName;
		cout << "\nLastName : " << _LastName;
		cout << "\nFull Name: " << FullName();
		cout << "\nEmail    : " << _Email;
		cout << "\nPhone    : " << _Phone;
		cout << "\n___________________\n";

	}
	void SendEmail(string Title, string Body)
	{

	}

	void SendFax(string Title, string Body)
	{

	}

	void SendSMS(string Title, string Body)
	{


	}
};

