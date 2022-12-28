#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <vector>
#include "Person.h"
#include "Product.h"

using namespace std;

class Order
{
private:
    int _id;
    string _date;
    bool _is_paid;
    Person* _person;
    vector<Product> _products;
    static int increamentId;
public:
    Order(string date,bool is_paid, Person* person,const vector<Product>& products);
    int getid()const;
    void setDate(string);
    const string getDate()const;
    void setIsPaid(bool);
    bool getIsPaid()const;
    void setPerson( Person*);
    const Person* getPerson()const;
    void setProducts(const vector<Product>&);
    const vector<Product>& getProducts()const;
};

#endif // ORDER_H
