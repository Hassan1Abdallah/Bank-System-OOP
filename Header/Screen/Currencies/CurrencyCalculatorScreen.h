#pragma once
#include <iostream>
#include "Currency.h"
#include "InputValidate.h"
#include "Screen.h"

class CurrencyCalculatorScreen : protected Screen

{
private:
    static float _readAmount() {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;

        Amount = InputValidate::readFloatnumber();
        return Amount;
    }

    static Currency _getCurrency(string Message) {

        string currencyCode;
        cout << Message << endl;

        currencyCode = InputValidate::readString();

        while (!Currency::isCurrencyExist(currencyCode)) {
            cout << "\nCurrency is not found, choose another one: ";
            currencyCode = InputValidate::readString();
        }

        Currency Currency = Currency::findByCode(currencyCode);
        return Currency;
    }


    static void _printCurrencyCard(Currency Currency, string Title = "Currency Card:") {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\ncountry       : " << Currency.country();
        cout << "\nCode          : " << Currency.currencyCode();
        cout << "\nName          : " << Currency.currencyName();
        cout << "\nRate(1$) =    : " << Currency.rate();
        cout << "\n_____________________________\n\n";
    }

    static void _printCalculationsResults(float Amount, Currency Currency1, Currency Currency2) {

        _printCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.convertToUSD(Amount);

        cout << Amount << " " << Currency1.currencyCode() << " = " << AmountInUSD << " USD\n";

        if (Currency2.currencyCode() == "USD") {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _printCurrencyCard(Currency2, "To:");

        float AmountInCurrrency2 = Currency1.convertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.currencyCode() << " = " << AmountInCurrrency2 << " "
             << Currency2.currencyCode();
    }


public:
    static void showCurrencyCalculatorScreen() {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y') {
            system("cls");

            _drawScreenHeader("\tUpdate Currency Screen");

            Currency CurrencyFrom = _getCurrency("\nPlease Enter Currency1 Code: ");
            Currency CurrencyTo = _getCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _readAmount();

            _printCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;
        }
    }
};
