#ifndef COMPANY_H
#define COMPANY_H
#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>
#include "Person.h"
#include "Product.h"
#include "Order.h"

using namespace std;

class Company
{
private:
    vector<Person*> persons;
    vector<Product> products;
    vector<Order> orders;
public:
    void add_product(const Product& product);
    void add_person(Person* person);
    void add_order(const Order& order);
    void remove_product(int);
    void remove_person(int);
    void remove_order(int);
    void print_person_info(int);
    void print_product_details(int);
    void print_order_details(int);
    void print_person_orders(int);
};

#endif // COMPANY_H
