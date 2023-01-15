#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen(){
        if (!CheckAccessRights(clsUser::enMainMenuePermissions::pFindClient)) {
            return;
        }
        _DrawScreenHeader("\tFind Client Screen");
        string accountNumber;

        accountNumber = clsInputValidate::ReadStringNumber("Please Enter AccountNumber: ");

        while (!clsBankClient::IsClientExists(accountNumber)) {
            accountNumber = clsInputValidate::ReadStringNumber("Invalid AccountNumber,Enter AccountNumber Again: ");
        }

        clsBankClient client = clsBankClient::Find(accountNumber);

        if (!client.IsEmpty())
            cout << "\nClient Found :)\n";
        else
            cout << "Client not Found :(\n";

        _PrintClient(client);
    }
};

