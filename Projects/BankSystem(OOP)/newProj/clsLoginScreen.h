#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen: protected clsScreen
{
private:
	static bool _Login() {
		bool LoginFaild = false;
		string userName, password;
		int trials = 3;
		do
		{
			cout << "\nEnter UserName: ";
			cin >> userName;

			cout << "Enter passowrod: ";
			cin >> password;

			CurrentUser = clsUser::Find(userName, password);

			LoginFaild = CurrentUser.IsEmpty();
			if (LoginFaild) {
				cout << "\nInvalid userName/password\n";
		
				cout << "You have " << --trials << " Trials to login\n";
			}

		} while (LoginFaild && trials != 0);
		if (!trials) {
			cout << "\nYou are locked after 3 falid trials\n";
			return false;
		}

		CurrentUser.RegisterLogIn();
			// show me the system
		clsMainScreen::ShowMainMenu();
		return true;
	}
public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}
};

