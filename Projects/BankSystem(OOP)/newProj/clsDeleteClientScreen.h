#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
class clsDeleteClientScreen: protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Clinet)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Clinet.FirstName;
        cout << "\nLastName    : " << Clinet.LastName;
        cout << "\nFull Name   : " << Clinet.FullName();
        cout << "\nEmail       : " << Clinet.Email;
        cout << "\nPhone       : " << Clinet.Phone;
        cout << "\nAcc. Number : " << Clinet.getAccountNumber();
        cout << "\nPassword    : " << Clinet.PinCode;
        cout << "\nBalance     : " << Clinet.AccountBalance;
        cout << "\n___________________\n";

    }
public:
    static void ShowDeleteClientScreen() {
        if (!CheckAccessRights(clsUser::enMainMenuePermissions::pDeleteClient)) {
            return;
        }
        _DrawScreenHeader("\tDelete Screen");

        string AccountNumber = clsInputValidate::ReadStringNumber("Please enter account number? ");
        while (!clsBankClient::IsClientExists(AccountNumber)) {
            AccountNumber = clsInputValidate::ReadStringNumber("AccountNumber is notfound choose another one! ");
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        cout << "Card\n";
        _PrintClient(Client);

        cout << "\n Are you sure you want to delete this account (y/n)? ";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {

            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _PrintClient(Client);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }

        }

    }
};

