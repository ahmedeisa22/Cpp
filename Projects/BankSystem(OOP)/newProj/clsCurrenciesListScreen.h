#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
class clsCurrenciesListScreen: protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();
    }


public:
	static void ShowCurrenciesListSCreen(){
        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
        string Title = "\tCurrency List Screen.";
        string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ")currency.";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(10) << "Code";
        cout << "| " << left << setw(35) << "Name";
        cout << "| " << left << setw(10) << "Rate";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsCurrency Currency : vCurrencies)
            {

                _PrintCurrency(Currency);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};

