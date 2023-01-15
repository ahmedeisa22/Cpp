#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
class clsUpdateClientScreen: protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client1) {

        Client1.FirstName = clsInputValidate::ReadStringNumber("\nEnter FirstName : ");

        Client1.LastName = clsInputValidate::ReadStringNumber("\nEnter LastName : ");

        Client1.Email = clsInputValidate::ReadStringNumber("\nEnter Email : ");

        Client1.Phone = clsInputValidate::ReadStringNumber("\nEnter Phone : ");

        Client1.PinCode = clsInputValidate::ReadStringNumber("\nEnter PinCode : ");

        Client1.AccountBalance = clsInputValidate::ReadDblNumber("\nEnter Balance : ");
    }
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
  
    static void ShowUpdateClientScreen() {
        if (!CheckAccessRights(clsUser::enMainMenuePermissions::pUpdateClients)) {
            return;
        }
        _DrawScreenHeader("\tUpdate Client Screen");
        string accountNumber;

        accountNumber = clsInputValidate::ReadStringNumber("Please Enter AccountNumber: ");

        while (!clsBankClient::IsClientExists(accountNumber)) {
            accountNumber = clsInputValidate::ReadStringNumber("Invalid AccountNumber,Enter AccountNumber Again: ");
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClient(client);

        cout << "\n\nUpdate Client Info:\n";
        _ReadClientInfo(client);

        clsBankClient::enSaveResult saveResult;
        saveResult = client.Save();
        switch (saveResult)
        {
        case clsBankClient::svFaildEmployeObject: {
            cout << "\nError Account wasn't Saved because it was empty\n";
        }
        case clsBankClient::svSucceeded:
        {
            cout << "\nAccount Saved Successfully :)\n";
            _PrintClient(client);
        }

        }


    }

};

