#include "Order.h"


int Order::increamentId = 1;

Order::Order(string date,bool is_paid, Person* person,const vector<Product>& products)
    :_date(date),_is_paid(is_paid),_person(person),_products(products)
{
    this->_id = increamentId++;
}

int Order::getid()const{
    return this->_id;
}
void Order::setDate(string date)
{
    this->_date = date;
}
const string Order::getDate()const
{
    return this->_date ;
}
void Order::setIsPaid(bool isPaid)
{
    this->_is_paid = isPaid;
}
bool Order::getIsPaid()const
{
    return  this->_is_paid;
}

void Order::setPerson(Person* person)
{
    this->_person = person;
}
const Person* Order::getPerson()const
{
    return  this->_person;
}
void Order::setProducts(const vector<Product>& products)
{
    this->_products = products;
}
const vector<Product>& Order::getProducts()const
{
    return this->_products ;
}
