#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsShowCurrencyExchangeMainScreen: protected clsScreen
{
private:
	enum enMainCurrencyExchange {
		eListCurrencies = 1, eFindCurrencies = 2,
		eUpdateCurrencies = 3, eCurrencyCalculator = 4,
		eMainMenu = 5
	};
    static void _GoBackToCurrencyMenue() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Menue...\n";
        system("pause > 0");
        ShowCurrencyExchangeScreen();
    }
	static short _ReadMainCurrencyExchange() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}
    static void ShowListCurrency() {
        //cout << "ShowListCurrency Will be Here...\n";
        clsCurrenciesListScreen::ShowCurrenciesListSCreen();
    }
    static void ShowFindCurrency() {
        //cout << "ShowFindCurrency Will be Here...\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void ShowUpdateCurrency() {
        //cout << "ShowUpdateCurrency Will be Here...\n";
        clsUpdateRateScreen::ShowUpdateRateScreen();
    }
    static void ShowCurrencyCalculator() {
        //cout << "ShowCurrencyCalculator Will be Here...\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }
    static void _PerfromMainMenueOption(enMainCurrencyExchange MainCurrencyExchange) {
        switch (MainCurrencyExchange)
        {
        case enMainCurrencyExchange::eListCurrencies:
        {
            system("cls");
            ShowListCurrency();
            _GoBackToCurrencyMenue();
            break;
        }
        case enMainCurrencyExchange::eFindCurrencies:
            system("cls");
            ShowFindCurrency();
            _GoBackToCurrencyMenue();
            break;

        case enMainCurrencyExchange::eUpdateCurrencies:
            system("cls");
            ShowUpdateCurrency();
            _GoBackToCurrencyMenue();
            break;

        case enMainCurrencyExchange::eCurrencyCalculator:
            system("cls");
            ShowCurrencyCalculator();
            _GoBackToCurrencyMenue();
            break;
        case enMainCurrencyExchange::eMainMenu:
            system("cls");
            break;
        }
    }
public:
	static void ShowCurrencyExchangeScreen(){
        system("cls");
        _DrawScreenHeader("   Currency Exchange Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currency.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] MainMenu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainCurrencyExchange)_ReadMainCurrencyExchange());
    
    }
};

