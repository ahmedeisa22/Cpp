#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsCurrencyCalculatorScreen: protected clsScreen
{
private:
    static float _ReadAmount()
    {
        float Amount = 0;

        Amount = clsInputValidate::ReadDblNumber("\nEnter Amount to Exchange: ");
        return Amount;
    }
    static clsCurrency _GetCurrency(string Message)
    {

        string CurrencyCode;

        CurrencyCode = clsInputValidate::ReadStringNumber(Message);

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
            CurrencyCode = clsInputValidate::ReadStringNumber("\nCurrency is not found, choose another one: ");
        

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }
    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";

    }
    static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {

        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();

    }
    
    /*static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n_____________________________\n";
    }
    static void _PrintExchange(clsCurrency Currency1, clsCurrency Currency2, double amount,double exchange)
    {
        cout << amount << " " << Currency1.CurrencyCode() << " = " << exchange << " "
            << Currency2.CurrencyCode() << endl;
    }
    static double ExchngeToDollar(double amount,clsCurrency CurrencyFrom) {
        return  amount / CurrencyFrom.Rate();
    }
    static void CurrencyExchange(clsCurrency currency1 , clsCurrency currency2) {
        double amount = clsInputValidate::ReadDblNumber("\nPlease enter Amount to Exchaneg: ");
        if (currency2.CurrencyCode() == "USD") {
            double exchange = ExchngeToDollar(amount, currency1);
            cout << "\nConvert From:\n";
            _PrintCurrency(currency1);
            _PrintExchange(currency1, currency2,amount, exchange);
        }
        else {
            double dollar = ExchngeToDollar(amount, currency1);
            double fromdollartocountry = dollar * currency2.Rate();
            _PrintExchange(currency1, currency2, amount, fromdollartocountry);
        }
    }*/
public:

	static void ShowCurrencyCalculatorScreen(){
        _DrawScreenHeader("  Currency Calculator Screen");

         char ans = 'y';
         do
         {
             clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
             clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
             float Amount = _ReadAmount();

             _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
             cout << "Do you want to do another calculation(y/n): ";
             cin >> ans;
         } while (ans == 'Y' || ans == 'y');

         
   
    }
};

