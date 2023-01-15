#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsFindCurrencyScreen: protected clsScreen
{
private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }
public:
    static void ShowFindCurrencyScreen() {
        _DrawScreenHeader("\t Find Currency SCreen");
        cout << "Find By: [1] Code ore [2] Country?";

        int num = clsInputValidate::ReadIntNumber();
        switch (num)
        {
        case 1: {
            string currencyCode = clsInputValidate::ReadStringNumber("Please enter currency code? ");
            while (!clsCurrency::IsCurrencyExist(currencyCode)) {
                currencyCode = clsInputValidate::ReadStringNumber("Invalid Currency Code,Please enter Another currency code? ");
            }
            clsCurrency currency = clsCurrency::FindByCode(currencyCode);

            if (currency.IsEmpty()) {
                cout << "Currency Not Found!:(\n";
            }
            else {
                cout << "Currency Found :)\n\n";
                _PrintCurrency(currency);
            }

            break;
        }
           
        case 2:
        {
            string currencyCountry = clsInputValidate::ReadStringNumber("Please enter currency Country? ");
   
            clsCurrency currency = clsCurrency::FindByCountry(currencyCountry);

            if (currency.IsEmpty()) {
                cout << "Currency Not Found!:(\n";
            }
            else {
                cout << "Currency Found :)\n\n";
                _PrintCurrency(currency);
            }
        }
        }
    }
};

