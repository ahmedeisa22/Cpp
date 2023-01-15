#pragma once
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
class clsAddNewUserScreen :protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User)
	{
		User.FirstName = clsInputValidate::ReadStringNumber("\nEnter FirstName: ");

		User.LastName = clsInputValidate::ReadStringNumber("\nEnter LastName: ");

		User.Email = clsInputValidate::ReadStringNumber("\nEnter Email: ");

		User.Phone = clsInputValidate::ReadStringNumber("\nEnter Phone: ");

		User.Password = clsUtil::encryptedName(clsInputValidate::ReadStringNumber("\nEnter Password: "),2);

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadSetPermission();
	}
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
	static int _ReadSetPermission() {
		int sum = 0;
		char choice;
		char fullAccess;
		cout << "\nDo You want to give full access? (y/n): ";
		cin >> fullAccess;
		if (tolower(fullAccess) == 'y')
			return -1;

		cout << "\nDo you want to give access to : \n";

		cout << " List users (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pListClients;

		cout << "add new users (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pAddNewClient;

		cout << "Update users (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pUpdateClients;

		cout << "Delete users (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pDeleteClient;

		cout << "Find users (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pFindClient;
		cout << "transaction users (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pTranactions;

		cout << "Manage users (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pManageUsers;

		cout << "ShowLoginUserRegister (y/n): ";
		cin >> choice;
		if (tolower(choice) == 'y')
			sum += (int)clsUser::enMainMenuePermissions::pShowLoginRegister;
		return sum;
	}
public:
	static void ShowAddNewUserScreen() {
		_DrawScreenHeader("\t Add New User Screen");
		string userName = clsInputValidate::ReadStringNumber("Enter User Name: ");
	
		while (clsUser::IsUserExists(userName)) {
			cout << "\User with [" << userName << "] already exists, Enter another userName ? ";
			getline(cin >> ws, userName);
		}

		clsUser user = clsUser::GetAddNewUserObject(userName);
		_ReadUserInfo(user);

		clsUser::enSaveResults SaveResult;

		SaveResult = user.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(user);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;

		}
		case clsUser::enSaveResults::svFaildUserExists:
		{
			cout << "\nError User was not saved because UserName is used!\n";
			break;

		}
		}
	}
};

