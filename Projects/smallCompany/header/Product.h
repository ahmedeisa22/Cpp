#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

using namespace std;

class Product
{
private:
    int _id;
    string _name;
    double _price;
    static int increamentId;
public:
    Product(string,double);
    int getid()const;
    void setName(string);
    const string& getName()const;
    void setPrice(double);
    double getPrice()const;
};

#endif // PRODUCT_H
