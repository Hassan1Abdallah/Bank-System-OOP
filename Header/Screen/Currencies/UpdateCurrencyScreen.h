#pragma once
#include <iostream>
#include "Currency.h"
#include "InputValidate.h"
#include "Screen.h"

class UpdateCurrencyScreen : protected Screen {

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

    static float _readRate() {
        cout << "\nEnter New rate: ";
        float NewRate = 0;

        NewRate = InputValidate::readFloatnumber();
        return NewRate;
    }

public:

    static void showUpdateCurrencyScreen() { 
        
        _drawScreenHeader("\t  Update Currency Screen"); 
        string code = "";
        
        cout << "PLZ enter currency code: ";
        code = InputValidate::readString();

        while (!Currency::isCurrencyExist(code)) {

            cout << "Currency is NOT found, Enter another currency code: ";
            code = InputValidate::readString();

        }

        Currency currency = Currency::findByCode(code);
        _printCurrency(currency);


        cout << "\nAre you sure you want to update this rate  y/n? ";
    
        char answer = 'n';
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            cout << "\n\nUpdate Currency rate:";
            cout << "\n____________________\n";

            currency.updateRate(_readRate());

            cout << "\nCurrency rate Updated Successfully :-)\n";
            _printCurrency(currency);

    
        }
    }

};
