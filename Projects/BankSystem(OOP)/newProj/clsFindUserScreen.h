#pragma once
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsFindUserScreen :protected clsScreen
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
	static void ShowFindUserScreen() {
		_DrawScreenHeader("\t Find User Screen");
		string userName = clsInputValidate::ReadStringNumber("Please enter UsreName? ");
		while (!clsUser::IsUserExists(userName)) {
			userName = clsInputValidate::ReadStringNumber("UsreName is notfound choose another one! ");
		}
		clsUser user = clsUser::Find(userName);
		if (!user.IsEmpty()) {
			cout << "\nUser Found :)\n";
		}
		else {
			cout << "\nUser is Empty! :(\n";
		}
		_PrintUser(user);
	}
};

