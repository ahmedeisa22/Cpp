#include<bits/stdc++.h>
#include "Person.h"
#include "Client.h"
#include "Employee.h"
#include "Product.h"
#include "Order.h"
#include "Company.h"

using namespace std;


int main ()
{
    Client person1("Mhamad", "+96170123456", "Male", "mhamad@example.com");
    Employee person2("Nadine", "+9631249392", "Female", 800, "8:00 AM to 3:00 PM");


    Client *person1_pointer = &person1;
    Employee *person2_pointer = &person2;

    Product product1 = Product("Keyboard", 15);
    Product product2 = Product("Camera", 45);
    Product product3 = Product("HDD 1TB", 70);
    Product product4 = Product("SSD 1TB", 274.66);
    Product product5 = Product("Mouse", 8);
    Product product6 = Product("Table", 44.55);


    vector<Product> order1Products;
    order1Products.push_back(product1);
    order1Products.push_back(product2);
    order1Products.push_back(product3);

    vector<Product> order2Products;
    order2Products.push_back(product4);

    vector<Product> order3Products;
    order3Products.push_back(product5);
    order3Products.push_back(product6);

    Order order1 = Order("2020-1-1", true, person1_pointer, order1Products);
    Order order2 = Order("2020-2-7", true, person1_pointer, order2Products);
    Order order3 = Order("2020-5-4", false, person2_pointer, order3Products);


    Company company = Company();

    company.add_person(person1_pointer);
    company.add_person(person2_pointer);

    company.add_product(product1);
    company.add_product(product2);
    company.add_product(product3);
    company.add_product(product4);
    company.add_product(product5);
    company.add_product(product6);

    company.add_order(order1);
    company.add_order(order2);
    company.add_order(order3);

    // viewing in the console
    company.print_person_info(1);
    company.print_person_info(2);

    company.print_product_details(1);
    company.print_product_details(2);
    company.print_product_details(3);
    company.print_product_details(4);
    company.print_product_details(5);
    company.print_product_details(6);



    company.print_person_orders(1);
    company.print_person_orders(2);

    company.remove_order(1);
    company.print_order_details(1);
    company.print_person_orders(1);
    return 0;
}
