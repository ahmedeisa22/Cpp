#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Person.h"

class Employee: public Person
{
private:
    double _salary;
    string _working_time;

public:
    Employee(string name, string phone, string gender,double salary,string working);
    void setSalary(double);
    double getSalary()const;
    void setWorkingTime(string);
    const string& getWorkingTime()const;
    void print_extra_info();
};

#endif // EMPLOYEE_H
