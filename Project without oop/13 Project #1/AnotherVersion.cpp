#include <iostream>
#include <string>
#include <math.h>

using namespace std;
const int MAX_SPEC = 20;
const int MAX_PATIENT = 5;
string specialization[MAX_SPEC][MAX_PATIENT];
int numberOfSpec[MAX_SPEC] {0};
int status[MAX_SPEC][MAX_PATIENT] {0};
void left_shift(int spec,string name[],int st[])
{
    int len = numberOfSpec[spec];

    for(int i = 0 ; i < len ; i++)
    {
        name[i] = name[i+1];
        st[i] = st[i+1];
    }
    numberOfSpec[spec]--;
}
void right_shift(int spec,string name[],int st[])
{
    int len = numberOfSpec[spec];
    for(int i = len  ; i > 0 ; i--)
    {
        name[i] =  name[i-1];
        st[i] = st[i-1];
    }
}
void AddNewPatient()
{
    int spec,sta,cnt = 0;
    string name;

    cout << "Enter specialization, name, status: ";
    cin >> spec >> name >> sta;

    spec--;
    cnt =  numberOfSpec[spec];
    if(cnt == MAX_PATIENT)
    {
        cout << "Sorry we cann't add more patients for this specialization\n";
        return;
    }
    if(sta == 0)
    {
        specialization[spec][cnt] = name;
        status[spec][cnt] = 0;

    }
    else if(sta == 1)
    {
        right_shift(spec,specialization[spec],status[spec]);

        specialization[spec][0] = name;
        status[spec][0] = 1;

    }


    // add to spec
    numberOfSpec[spec]++;
}
void printPatient(int spec,string name[],int st[])
{
    int len = numberOfSpec[spec];

    if(!len)
    {
        return;
    }

    cout << "There are " << len << " patients in Specialization " << spec+1 << ":\n";
    for(int i= 0 ; i < numberOfSpec[spec] ; i++ )
    {
        cout << name[i] << " ";
        if(!status[i])
            cout << "Regular\n";
        else
            cout << "Urgent\n";
    }

    cout << endl << endl;

}
void PrintAllPatient()
{
    cout << "\n****************************************\n";
    for(int i = 0 ; i < MAX_SPEC ; i++)
    {
        printPatient(i,specialization[i],status[i]);
    }
}

void GetNextPatient()
{
    int spec;
    cout << "Enter Specialization: ";
    cin >> spec;

    spec --;
    if(!numberOfSpec[spec])
    {
        cout << "\nMR.Eisa says to you No patient at this moment, Have rest, Dr :)\n\n";
        return;
    }
    cout << specialization[spec][0] << " Please go with the doctor\n";


    left_shift(spec,specialization[spec],status[spec]);
}
int menu()
{
    int ch = -1;
    while(ch == -1)
    {
        cout << "Enter your choice: \n";
        cout << "1) Add new patient\n";
        cout << "2) print All patient\n";
        cout << "3) get next patient\n";
        cout << "4) Exist\n";
        cin >> ch;

        if(!(ch>= 1 && ch <= 4))
        {
            cout << "\nInvalid choice Please try again from [1:4]: \n\n";
            ch = -1;
        }
    }
    return ch;
}

void startSystem()
{

    while(true)
    {

        int choice = menu();
        if(choice == 1)AddNewPatient();
        else if(choice == 2)PrintAllPatient();
        else if(choice == 3) GetNextPatient();
        else
        {
            cout << "Bye Mr.Eissa :)\n";
            break;
        };
    }
}
int main()
{
    startSystem();

    return 0;
}



