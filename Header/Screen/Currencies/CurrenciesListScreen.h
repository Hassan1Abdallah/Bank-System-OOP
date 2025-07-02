#pragma once

#include <iomanip>
#include <iostream>
#include "Currency.h"
#include "Screen.h"

class CurrenciesListScreen : protected Screen {

private:
    static void printCurrencyRecordLine(Currency currency) {

        cout << setw(8) << left << ""
             << "| " << setw(30) << left << currency.country();
        cout << "| " << setw(8) << left << currency.currencyCode();
        cout << "| " << setw(45) << left << currency.currencyName();
        cout << "| " << setw(10) << left << currency.rate();
    }

public:
    static void showCurrenciesListScreen() {


        vector<Currency> vCurrencys = Currency::getCurrenciesList();
        string Title = "\t  Currencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrencys.size()) + ") Currency.";

        _drawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << ""
             << "| " << left << setw(30) << "country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "rate/(1$)";
        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vCurrencys.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else

            for (Currency currency: vCurrencys) {

                printCurrencyRecordLine(currency);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;
    }
};
