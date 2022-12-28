#include "Company.h"



void Company::add_product(const Product& product)
{
    this->products.push_back(product);
}
void Company:: add_person(Person* person)
{
    this->persons.push_back(person);
}
void Company::add_order(const Order& order)
{
    this->orders.push_back(order);
}

void Company::remove_product(int id)
{
    bool is_found = true;

    for(int i = 0 ; i < products.size() ; i++)
    {
        if(products[i].getid() == id)
        {
            is_found = false;
            products.erase(products.begin()+i);
        }

    }

    if(is_found)
    {
        cout << "\n This is Invalid Id\n";
        return;
    }
}
void Company::remove_person(int id)
{
    bool is_found = true;

    for(int i = 0 ; i < persons.size() ; i++)
    {
        if(persons[i]->getid() == id)
        {
            is_found = false;
            persons.erase(persons.begin()+i);
        }

    }

    if(is_found)
    {
        cout << "\n This is Invalid Id\n";
        return;
    }
}
void Company::remove_order(int id)
{
    bool is_found = true;

    for(int i = 0 ; i < orders.size() ; i++)
    {
        if(orders[i].getid() == id)
        {
            is_found = false;
            orders.erase(orders.begin()+i);
        }

    }

    if(is_found)
    {
        cout << "\n This is Invalid Id\n";
        return;
    }
}


void Company::print_person_info(int id)
{
    bool is_found = true;

    for(int i = 0 ; i < persons.size() ; i++)
    {
        if(persons[i]->getid() == id)
        {
            cout << "Person with id " << id << " info.\n";
            cout << "Name   : " << persons[i]->getName() << endl;
            cout << "Phone  : " <<  persons[i]->getPhone() << endl;
            cout << "Gender : " <<  persons[i]->getGender() << endl;

            persons[i]->print_extra_info();
            cout << "----------------------------------------\n";
            is_found = false;
            break;
        }
    }
    if(is_found)
    {
        cout << "\n This is Invalid Id\n";
        return;
    }
}

void Company::print_product_details(int id)
{
    bool is_found = true;

    for(int i = 0 ; i < products.size() ; i++)
    {
        if(products[i].getid() == id)
        {
            cout << "product with id " << id << " details.\n";
            cout << "Name : " << products[i].getName()<< "\n";
            cout << "Price : " << products[i].getPrice()<< "\n";
            cout << "----------------------------------------\n";
            is_found = false;
            break;
        }
    }



    if(is_found)
    {
        cout << "\n This is Invalid Id\n";
        return;
    }
}
void Company::print_order_details(int orderId)
{
    bool is_found = true;
    for(int i = 0 ; i < orders.size() ; i++)
    {
        if(orders[i].getid() == orderId)
        {
            double total_proce = 0;
            cout << "> Order: #" << orders[i].getid() << "\n";
            cout << "   Date : " << orders[i].getDate() << "\n";
            cout << "   Is paid : " << (orders[i].getIsPaid() == 1 ? "YES":"NO") << "\n";
            cout << "   Ordered by: : " << orders[i].getPerson()->getName() << "\n";
            cout << "   Products : \n";
            for(auto &p :orders[i].getProducts())
            {
                cout << "   - " << p.getName()  << ": " << p.getPrice() << "\n";
                total_proce+= p.getPrice();
            }

            cout << "   Total Price: " << total_proce << "\n";
            is_found = false;

        }

    }
    if(is_found)
    {
        cout << "\n################################\n";
        cout << " Order with  Id " << orderId << "\n";
        cout << "################################\n";
        return;
    }
}
void Company::print_person_orders(int id)
{
    bool is_found = true;
    for(int i = 0 ; i < orders.size() ; i++)
    {
        if(orders[i].getPerson()->getid() == id)
        {
            print_order_details(orders[i].getid());
            is_found = false;
        }

    }
    cout << "-----------------------------------------------\n";
    if(is_found)
    {
        cout << "\n This is Invalid Id\n";
        return;
    }

}

