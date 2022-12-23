#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;
bool is_x = true;
bool is_o = true;
bool switchPlayer(char **arr,int n,bool player)
{
    int r,c;

    if(player)
    {
        cout << "player x turn, Enter empty location (r,c): ";
        cin >> r >> c;
    }
    else
    {
        cout << "player o turn, Enter empty location (r,c): ";
        cin >> r >> c;
    }
    r--,c--;
    if(arr[r][c]!='.'||r >= n || c >= n )
    {
        cout << "Invalid input, try again!\n";
        return false;
    }

    if(player)arr[r][c] = 'x';
    else arr[r][c] = 'o';



    return true;
}
void showArray(char **arr,int n)
{
    cout << "**************************************************The Game********************************\n\n";
    for(int i = 0 ; i < n ; i++)
    {

        for(int j = 0 ; j < n ; j++)
            cout <<"\t" <<arr[i][j];


        cout << endl;
    }
    cout << "\n******************************************************************************************\n";
}
bool chechDraw(char **arr,int n)
{
    bool have_free_spaces = false;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            if(arr[i][j]== '.')
                have_free_spaces = true;

    }
    if(!have_free_spaces)
    {
        cout << "\nyou are draw GoodBye!\n";
        return false;
    }
    return true;
}

void deletePtrArr(char **arr,int n)
{
    for(int i = 0; i < n; ++i)
    {
        delete [] arr[i];
    }
    delete [] arr;
}

bool checkRows(char **arr,int n)
{
    // rows
    for(int i = 0 ; i < n ; i++)
    {
        is_x = is_o = true;
        for(int j = 0 ; j < n ; j++)
        {
            if(arr[i][j] != 'x') is_x = false;
            if(arr[i][j] != 'o') is_o = false;
            if(!is_o && !is_x)break;
        }
        if(is_x || is_o) return true;

    }
    return false;
}

bool checkcolumns(char **arr,int n)
{
    //columns
    for(int i = 0 ; i < n ; i++)
    {
        is_x = is_o = true;
        for(int j = 0 ; j < n ; j++)
        {
            if(arr[j][i] != 'x') is_x = false;
            if(arr[j][i] != 'o') is_o = false;
            if(!is_o && !is_x)break;
        }
        if(is_x || is_o) return true;
    }
    return false;
}
bool checkDigonal(char **arr,int n)
{
    //columns
    for(int i = 0 ; i < n ; i++)
    {
        is_x = is_o = true;
        for(int j = 0 ; j < n ; j++)
        {

            if(arr[j][j] != 'x') is_x = false;
            if(arr[j][j] != 'o') is_o = false;
            if(!is_o && !is_x)break;

        }
        if(is_x || is_o) return true;
    }
    return false;
}
bool checkInverseDigonal(char **arr,int n)
{
    //columns

    is_x = is_o = true;
    for(int j = 0 ; j < n ; j++)
    {

        if(arr[j][n-j-1] != 'x') is_x = false;
        if(arr[j][n-j-1] != 'o') is_o = false;
        if(!is_o && !is_x)break;

    }
    if(is_x || is_o) return true;

    return false;
}
int main()
{
    int n;
    cout << "Enter input in range [3:9]:\n";
    cin >> n;
    while(n< 3 || n > 9)
    {
        cout << "try again should be in range [3:9]:\n";
        cin >> n;
    }
    char **arr = new char*[n];
    for(int i = 0; i < n; ++i)
        arr[i] = new char[n];
    // fill array with zeroes
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            arr[i][j]='.';
    }


    bool player = true;
    bool playing = true;
    while(playing)
    {
        //switch palyer
        if(!switchPlayer(arr,n,player))continue;


        // show array
        showArray(arr,n);

        if(checkRows(arr,n))
        {
          cout << "-------------------------------------------------- \n";
            if(is_x) cout << "\n player X Mabrook ya sa7by\n\n";
            else cout << "\n player O Mabrook ya sa7by\n\n";
            cout << "-------------------------------------------------- \n";
            break;
            playing = false;
        }

        if(checkcolumns(arr,n))
        {
            cout << "-------------------------------------------------- \n";
            if(is_x) cout << "\n player X Mabrook ya sa7by\n\n";
            else cout << "\n player O Mabrook ya sa7by\n\n";
         cout << "-------------------------------------------------- \n";
            break;
            playing = false;
        }

        if(checkDigonal(arr,n))
        {
           cout << "-------------------------------------------------- \n";
            if(is_x) cout << "\n player X Mabrook ya sa7by\n\n";
            else cout << "\n player O Mabrook ya sa7by\n\n";
            cout << "-------------------------------------------------- \n";
            break;
            playing = false;
        }


        if(checkInverseDigonal(arr,n))
        {
            cout << "-------------------------------------------------- \n";
            if(is_x) cout << "\n player X Mabrook ya sa7by\n\n";
            else cout << "\n player O Mabrook ya sa7by\n\n";
          cout << "-------------------------------------------------- \n";
            break;
            playing = false;
        }
        // check array is full
        if(!chechDraw(arr,n))playing = false;

        // switch user
        player=!player;
    }

    deletePtrArr(arr,n);
    return 0;
}

