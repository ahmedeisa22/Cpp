#pragma once
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;
class clsTransactionScreen : protected clsScreen
{
private:
	enum enTranscationMenueOptions {
		eDepoiste = 1, eWithDraw = 2,
		eTotalBalance = 3, eTranfer = 4,eTransferLog = 5,eMainMenu = 6,
	};
	static short ReadTransactionMenueOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1,6,"Enter Number in [1:6]: ");
		
		return Choice;
	}
	static void _GoBackToTransMenue() {
		cout << "\nPress any key to go back Transaction menu...\n";
		system("pause>nul");
		ShowTransationMenu();
	}
	static void _showDepoisteScreen(){
		//cout << "Deposite screen will be here!\n";
		clsDepositeScreen::showDepoisteScreen();
	}
	static void _showWithDrawScreen() {
		//cout << "Withdraw screen will be here!\n";
		clsWithdrawScreen::showWothdrawScreen();
	}
	static void _ShowTotalBalancesScreen() {
		//cout << "totalBalance screen will be here!\n";
		clsTotalBalancesScreen::ShowTotalBalances();
	}
	static void _ShowTransfer() {
		//cout << "Tranfer Screen will be here \n";
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLog() {
		//cout << "Tranfer Login Screen will be here \n";
		clsTransferLogScreen::ShowTransferLogScreen();
	}
	static void PerfromTranscationMenueOption(enTranscationMenueOptions transcationMenu) {
		switch (transcationMenu)
		{
		case enTranscationMenueOptions::eDepoiste: {
			system("cls");
			_showDepoisteScreen();
			_GoBackToTransMenue();
			break;
		}
		case enTranscationMenueOptions::eWithDraw: {
			system("cls");
			_showWithDrawScreen();
			_GoBackToTransMenue();
			break;
		}
		case enTranscationMenueOptions::eTotalBalance: {
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransMenue();
			break;
		}
		case enTranscationMenueOptions::eTranfer: {
			system("cls");
			_ShowTransfer();
			_GoBackToTransMenue();
			break;
		}
		case enTranscationMenueOptions::eTransferLog: {
			system("cls");
			_ShowTransferLog();
			_GoBackToTransMenue();
			break;
		}
		case enTranscationMenueOptions::eMainMenu: {
			//clsMainScreen::ShowMainMenu();
			break;
		}
		}
	}
public:
	static void ShowTransationMenu(){
		if (!CheckAccessRights(clsUser::enMainMenuePermissions::pTranactions)) {
			return;
		}
		system("cls");
		_DrawScreenHeader("\t Transaction Menu Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\tTranscation Menu Screen\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t [1] Deposite.\n";
		cout << setw(37) << left << "" << "\t [2] WithDraw.\n";
		cout << setw(37) << left << "" << "\t [3] Total Balance.\n";
		cout << setw(37) << left << "" << "\t [4] Transfer.\n";
		cout << setw(37) << left << "" << "\t [5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t [6] Main Menu.\n";
		cout << setw(37) << left << "" << "===========================================\n";
		PerfromTranscationMenueOption((enTranscationMenueOptions)ReadTransactionMenueOption());
	}
};

