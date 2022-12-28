#include "Employee.h"
#include<iostream>

Employee::Employee(string name, string phone, string gender,double salary,string working):
    Person(name,phone,gender),_salary(salary),_working_time(working)
{

}

void Employee::setSalary(double salary)
{
    this->_salary = salary;
}
double Employee::getSalary()const
{
    return this->_salary;
}
void Employee::setWorkingTime(string working)
{
    this->_working_time = working;
}
const string& Employee::getWorkingTime()const
{
    return this->_working_time;
}
void Employee::print_extra_info()
{
    std::cout << "Salary: " << getSalary() << "\n";
    std::cout << "Working time: " << getWorkingTime() << "\n";
}
