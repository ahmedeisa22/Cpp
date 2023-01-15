#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsUpdateRateScreen: protected clsScreen
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
    static void _UpdateRate(clsCurrency& Currency) {
        float rate = clsInputValidate::ReadDblNumber("Enter New Rate: ");
        Currency.UpdateRate(rate);
    }
public:

    static void ShowUpdateRateScreen() {
        _DrawScreenHeader("\tUpdate Rate SCreen");

       string currencyCode = clsInputValidate::ReadStringNumber("Please Enter Currency Code? ");
   
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
       cout << "\nAre you sure you want to update the rate of this currency(y/n): ";
       char Answer;
       cin >> Answer;
       if (Answer == 'y' || Answer == 'Y') {
           _UpdateRate(currency);
          
           cout << "\n\nUpdate Currency Rate:";
           cout << "\n____________________\n";
           _PrintCurrency(currency);
       }
    }
};

