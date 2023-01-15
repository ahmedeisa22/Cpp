#pragma once
#include "clsScreen.h"
#include "clsUser.h"
class clsDeleteUserScreen :protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteUserScreen() {
        _DrawScreenHeader("\t Delete User Screen");
        string userName = clsInputValidate::ReadStringNumber("Please enter UsreName? ");
        while (!clsUser::IsUserExists(userName)) {
            userName = clsInputValidate::ReadStringNumber("UsreName is notfound choose another one! ");
        }
        clsUser user = clsUser::Find(userName);

        cout << "Card\n";
        _PrintUser(user);
        cout << "\n Are you sure you want to delete this account (y/n)? ";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {

            if (user.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _PrintUser(user);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};

