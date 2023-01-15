#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsTransferScreen : protected clsScreen
{
private:
	struct stTransferLogin;

    static void _PrintClient(clsBankClient Clinet)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Clinet.FullName();
        cout << "\nAcc. Number : " << Clinet.getAccountNumber();
        cout << "\nBalance     : " << Clinet.AccountBalance;
        cout << "\n___________________\n";

    }
	static string _ReadAccountNumber()
	{
		string AccountNumberFrom = clsInputValidate::ReadStringNumber("Please enter account number to transfer from? ");

		while (!clsBankClient::IsClientExists(AccountNumberFrom))
			AccountNumberFrom = clsInputValidate::ReadStringNumber("\nAccount number is not found, choose another one: ");
		
		return AccountNumberFrom;
	}
	static float ReadAmount(clsBankClient SourceClient)
	{
		double transferAmount = clsInputValidate::ReadDblNumber("Enter amount to transfer: ");

		while (transferAmount > SourceClient.AccountBalance)
			transferAmount = clsInputValidate::ReadDblNumber("\nAmount Exceeds the available Balance, Enter another Amount ? ");
		
		return transferAmount;
	}

public:


	static void ShowTransferScreen() {

		_DrawScreenHeader("\t\tTransfer Screen");


		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(DestinationClient);

		double transferAmount = ReadAmount(SourceClient);

		char ch;
		cout << "Are you sure you want to perform this operation (y/n)? ";
		cin >> ch;
		if (ch == 'y' || ch == 'Y') {

			if(SourceClient.Transfer(transferAmount, DestinationClient,CurrentUser.UserName))
			cout << "transfer done successfully\n";
			else	
				cout << "transfer faild\n";

			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);
		}
	
	}
};

