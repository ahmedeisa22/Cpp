#include "Product.h"

int Product::increamentId = 1;
Product::Product(string name,double price):_name(name),_price(price)
{
    this->_id = increamentId++;
}

int Product::getid()const{
return this->_id;
}
void Product::setName(string name)
{
    this->_name = name;
}
const string& Product::getName()const
{
    return this->_name;
}
void Product::setPrice(double price)
{
    this->_price = price;
}
double Product::getPrice()const
{
    return this->_price;
}
