#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsDepositeScreen : protected clsScreen
{
private:
	static void _ShowClientINLines(clsBankClient Client) {
		cout << "\nThe Following are the client details:\n";
		cout << "-------------------------------------------------------------\n";
		cout << "Account Number : " << Client.getAccountNumber() << "\n";
		cout << "Code Pin       : " << Client.PinCode << "\n";
		cout << "Name           : " << Client.FullName() << "\n";
		cout << "Phone Number   : " << Client.Phone << "\n";
		cout << "AccountBalance : " << Client.AccountBalance << "\n";
		cout << "----------------------------------------------------------------\n";
	}

public:
	static void showDepoisteScreen() {
		_DrawScreenHeader("\t\ttDeposite Screen");

		vector<clsBankClient> vClients = clsBankClient::GetClientList();
		string AccountNumber = clsInputValidate::ReadStringNumber("Enter Account Number? ");

		while (!clsBankClient::IsClientExists(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadStringNumber("Invalid AccountNumber,Enter AccountNumber Again: ");
		}

		clsBankClient client = clsBankClient::Find(AccountNumber);

		_ShowClientINLines(client);
	
		double amount = clsInputValidate::ReadDblNumber("\nPlease Enter Depoiste Amount? ");
		char ans;
		cout << "\nAre you sure you want to perform thi transaction (y/n)? ";
		cin >> ans;
		if (ans == 'y' || ans == 'Y') {
			client.Deposite( amount);
		cout << "\nDone Successfully,New Balance is: " << client.AccountBalance << "\n";
		}
		else {
			cout << "\nOperation was Canceld\n";
		}

	}
};

