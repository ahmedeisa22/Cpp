#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferLogScreen : protected clsScreen
{
private:
	static void PrintTransferRecordLine(clsBankClient::stTransferLogin Transfer)
	{

		cout << setw(8) << left << "" << "| " << setw(25) << left << Transfer.DateTime;
		cout << "| " << setw(10) << left << Transfer.AccountFrom;
		cout << "| " << setw(10) << left << Transfer.AccountTo;
		cout << "| " << setw(10) << left << Transfer.AmountTransfer;
		cout << "| " << setw(10) << left << Transfer.BalanceFrom;
		cout << "| " << setw(10) << left << Transfer.Balanceto;
		cout << "| " << setw(10) << left << Transfer.UserName;
	}
public:
	static void ShowTransferLogScreen() {
		/*if (!CheckAccessRights(clsUser::enMainMenuePermissions::pShowLoginRegister)) {
			return;
		}*/
		vector<clsBankClient::stTransferLogin> vTransfers = clsBankClient::GetTransferterList();
		string SubTitle = "\t    (" + to_string(vTransfers.size()) + ") Record(s).";
		_DrawScreenHeader("  Transfer Log List Screen", SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acc";
		cout << "| " << left << setw(10) << "d.Acc";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(10) << "User";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vTransfers.size() == 0)
			cout << "\t\t\t\tNo Transfer Available In the System!";
		else

			for (clsBankClient::stTransferLogin loginTrans: vTransfers)
			{

				PrintTransferRecordLine(loginTrans);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}
};

