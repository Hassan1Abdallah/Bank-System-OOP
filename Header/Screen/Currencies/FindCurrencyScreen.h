#pragma once
#include <iostream>
#include "Currency.h"
#include "InputValidate.h"
#include "Screen.h"

class FindCurrencyScreen : protected Screen {

private:
    static void _printCurrency(Currency currency) {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\ncountry    : " << currency.country();
        cout << "\nCode       : " << currency.currencyCode();
        cout << "\nName       : " << currency.currencyName();
        cout << "\nRate(1$) = : " << currency.rate();

        cout << "\n_____________________________\n";
    }

    static void _showResults(Currency Currency) {
        if (!Currency.isEmpty()) {
            cout << "\nCurrency Found :-)\n";
            _printCurrency(Currency);
        } else {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:
    static void showFindCurrencyScreen() {

        _drawScreenHeader("\t  find Currency Screen");

        cout << "\nFind By: [1] Code or [2] country ? ";
        short Answer = 1;

        cin >> Answer;

        if (Answer == 1) {
            string currencyCode;
            cout << "\nPlease Enter currencyCode: ";
            currencyCode = InputValidate::readString();
            Currency Currency = Currency::findByCode(currencyCode);
            _showResults(Currency);
        } else {
            string country;
            cout << "\nPlease Enter country Name: ";
            country = InputValidate::readString();
            Currency Currency = Currency::findBycountry(country);
            _showResults(Currency);
        }
    }
};
