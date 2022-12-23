#include <iostream>
#include <string>
#include <math.h>

using namespace std;
const int MAX_SPEC = 20;
const int MAX_PATIENT = 5;
string specialization[MAX_SPEC][MAX_PATIENT];
int numberOfSpec[MAX_SPEC] {0};
int status[MAX_SPEC][MAX_PATIENT] {0};
void AddNewPatient()
{
    int spec,sta,cnt = 0;
    string name;

    cout << "Enter specialization, name, status: ";
    cin >> spec >> name >> sta;

    spec--;
    cnt =  numberOfSpec[spec];
    if(sta == 0 && cnt < MAX_PATIENT)
    {
        specialization[spec][cnt] = name;
        status[spec][cnt] = 0;

    }
    else if(sta == 1 && cnt < MAX_PATIENT)
    {
        for(int i = cnt  ; i > 0 ; i--)
        {
            specialization[spec][i] =  specialization[spec][i-1];
            status[spec][i] = status[spec][i-1];
        }


        specialization[spec][0] = name;
        status[spec][0] = 1;

    }
//    else
//    {
//
//        cout << "Invalid input please try again\n";
//        return;
//    }

    if(cnt == MAX_PATIENT)
    {
        cout << "Sorry we cann't add more patients for this specialization\n";
        return;
    }
    // add to spec
    numberOfSpec[spec]++;
}
void PrintAllPatient()
{
    cout << "\n****************************************\n";
    for(int i = 0 ; i < MAX_SPEC ; i++)
    {
        if(numberOfSpec[i])
        {
            cout << "There are " << numberOfSpec[i] << " patients in Specialization " << i+1 << ":\n";
            for(int j = 0 ; j < numberOfSpec[i] ; j++ )
            {
                cout << specialization[i][j] << " ";
                if(status[i][j] == 0)
                    cout << "Regular\n";
                else
                    cout << "Urgent\n";
            }

            cout << endl << endl;
        }
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


    for(int i = 0 ; i < numberOfSpec[spec]-1 ; i++)
    {
        specialization[spec][i] = specialization[spec][i+1];
        status[spec][i] = status[spec][i+1];
    }
    numberOfSpec[spec]--;
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



