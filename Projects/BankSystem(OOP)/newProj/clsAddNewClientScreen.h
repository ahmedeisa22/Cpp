#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsAddNewClientScreen:protected clsScreen
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
    static void _Print(clsBankClient Clinet)
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

    static void AddNewClient() {
        if (!CheckAccessRights(clsUser::enMainMenuePermissions::pAddNewClient)) {
            return;
        }
        _DrawScreenHeader("\t Add New Client Screen");

        string accountNumber;

        accountNumber = clsInputValidate::ReadStringNumber("Please Enter AccountNumber: ");

        while (clsBankClient::IsClientExists(accountNumber)) {
            accountNumber = clsInputValidate::ReadStringNumber("this Account Number Already Exists try another one: ");
        }

        clsBankClient client = clsBankClient::getAddNewClientObject(accountNumber);

        cout << "\n\nAdd New Client Info:\n";
        _ReadClientInfo(client);

        clsBankClient::enSaveResult saveResult;
        saveResult = client.Save();
        switch (saveResult)
        {
        case clsBankClient::svFaildEmployeObject: {
            cout << "\nError Account wasn't add because it was empty\n";
            break;
        }
        case clsBankClient::svSucceeded: {
            cout << "\nAccount add Successfully :)\n";
            _Print(client);
            break;
        }
        case clsBankClient::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }

        }
    }

};

