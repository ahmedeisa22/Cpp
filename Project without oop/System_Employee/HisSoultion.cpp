#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX = 10000;
string names[MAX];
int ages[MAX];
double salaries[MAX];
char genders[MAX];
int added = 0;


void ReadEmployes()
{
    cout << "Enter name: ";
    cin >> names[added];

    cout << "Enter age: ";
    cin >> ages[added];

    cout << "Enter salary: ";
    cin >> salaries[added];

    cout << "Enter gender (M/F): ";
    cin >> genders[added];
    ++added;
}
void printEmployess()
{
    cout << "****************************\n";
    for (int i = 0; i < added; ++i)
    {
        if (ages[i] != -1)
            cout << names[i] << " " << ages[i] << " " << salaries[i]
                 << " " << genders[i] << "\n";
    }
}
void DelteByAge()
{
    cout << "Enter start and end age: ";
    int start, end;
    cin >> start >> end;

    for (int i = 0; i < added; ++i)
    {
        if (start <= ages[i] && ages[i] <= end)
            ages[i] = -1;// Let's mark a removed entry with -1 (lazy delete)
    }
}
void UpdateBySalary()
{
    cout << "Enter the name and salary: ";
    string name;
    int salary;
    cin >> name >> salary;

    bool is_found = false;
    for (int i = 0; i < added; ++i)
    {
        if (ages[i] != -1 && names[i] == name)
        {
            is_found = true;
            salaries[i] = salary;
            break;
        }
    }
    if (!is_found)
        cout << "No employee with this name!\n";
}
int ReadChoices()
{
    int choice = -1;
    while(choice == -1)
    {
        cout << "\nEnter your choice:\n";
        cout << "1) Add new employee\n";
        cout << "2) Print all employees\n";
        cout << "3) Delete by age\n";
        cout << "4) Update Salary by name\n";
        cout << "5) Exsit\n";

        cin >> choice;
        if(!(1<= choice && choice <= 5))
        {
            cout << "Invaild Number Plaes try Again: \n";
            choice = -1;
            continue;
        }
    }
    return choice;
}
void startSystem()
{
    while (true)
    {
        int choice = ReadChoices();

        if(choice == 1) ReadEmployes();
        else if(choice == 2)printEmployess();
        else if (choice == 3)DelteByAge();
        else if (choice == 4)  UpdateBySalary();
        else break;
    }
}

int main()
{
    //freopen("c.in", "rt", stdin);
    startSystem();

    return 0;
}

