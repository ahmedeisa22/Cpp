#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersMenu:protected clsScreen
{
private:
	enum enManageUserOptions {
		eListUser = 1, eAddNewUser = 2,
		eDeleteUser = 3, eUpdateUser = 4,
		eFindUser = 5, eMainMenuManger = 6
	};
	static void _GoBackToMangerUserMenue() {
		cout << "\nPress any key to go back MangerUser menu...\n";
		system("pause>nul");
		ShowMangeUserMenu();
	}
	static short ReadMangeUsersMenueOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number in [1:6]: ");;
		return Choice;
	}
	static void _ShowUserList() {
		//cout << "Show User list will be here ...\n";
		clsListUserScreen::ShowUsersList();
	}
	static void _AddNewUsers() {
		//cout << "AddNew User list will be here ...\n";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}
	static void _ShowDeleteUserScreen() {
		//cout << "Show DeleteUser list will be here ...\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	static void _ShowUpdateUserScreen() {
		//cout << "Show UpdateUser list will be here ...\n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	static void _ShowFindUserScreen() {
		//cout << "Show FindUser list will be here ...\n";
		clsFindUserScreen::ShowFindUserScreen();
	}
	static void PerfromMangeUserMenueOption(enManageUserOptions useroptions) {

		switch (useroptions)
		{
		case enManageUserOptions::eListUser: {
			system("cls");
			_ShowUserList();
			_GoBackToMangerUserMenue();
			break;
		}
		case enManageUserOptions::eAddNewUser: {
			system("cls");
			_AddNewUsers();
			_GoBackToMangerUserMenue();
			break;
		}
		case enManageUserOptions::eDeleteUser: {
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToMangerUserMenue();
			break;
		}
		case enManageUserOptions::eUpdateUser: {
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToMangerUserMenue();
			break;
		}
		case enManageUserOptions::eFindUser: {
			system("cls");
			_ShowFindUserScreen();
			_GoBackToMangerUserMenue();
			break;
		}
		case enManageUserOptions::eMainMenuManger: {
		
			break;
		}
		}
	}
public:
	static void ShowMangeUserMenu(){
		if (!CheckAccessRights(clsUser::enMainMenuePermissions::pManageUsers)) {
			return;
		}
		system("cls");
		_DrawScreenHeader("  Manage User Menu Screen");
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tMangeUser Menu Screen\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t [1] List Users.\n";
		cout << setw(37) << left << "" << "\t [2] Add New Users.\n";
		cout << setw(37) << left << "" << "\t [3] Delete Users.\n";
		cout << setw(37) << left << "" << "\t [4] Update Users.\n";
		cout << setw(37) << left << "" << "\t [5] Find Users.\n";
		cout << setw(37) << left << "" << "\t [6] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		PerfromMangeUserMenueOption((enManageUserOptions)ReadMangeUsersMenueOption());
	}

};

