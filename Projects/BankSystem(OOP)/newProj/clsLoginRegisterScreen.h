#pragma once
#include "clsScreen.h"
#include "clsUser.h"
class clsLoginRegisterScreen:protected clsScreen
{
private:
		static void PrintLoginUserRecordLine(clsUser::stLoginRegisterRecord LoginUser)
	{

		cout << setw(8) << left << "" << "| " << setw(30) << left << LoginUser.DateTime;
		cout << "| " << setw(20) << left << LoginUser.UserName;
		cout << "| " << setw(12) << left << LoginUser.Password;
		cout << "| " << setw(12) << left << LoginUser.Permissions;
	}
public:
	
	static void ShowLoginRegisterScreen(){
		if (!CheckAccessRights(clsUser::enMainMenuePermissions::pShowLoginRegister)) {
			return;
		}
		vector<clsUser::stLoginRegisterRecord> vLoginUsers = clsUser::GetLoginRegisterList();
		string SubTitle = "\t    (" + to_string(vLoginUsers.size()) + ") Record(s).";
		_DrawScreenHeader("  Login Register List Screen", SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(12) << "Password";
		cout << "| " << left << setw(12) << "Permission";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vLoginUsers.size() == 0)
			cout << "\t\t\t\tNo users Available In the System!";
		else

			for (clsUser::stLoginRegisterRecord loginUser : vLoginUsers)
			{

				PrintLoginUserRecordLine(loginUser);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}

};

