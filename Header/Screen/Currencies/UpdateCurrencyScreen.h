#pragma once
#include <iostream>
#include "Currency.h"
#include "InputValidate.h"
#include "Screen.h"

class clsUpdateCurrencyScreen : protected clsScreen {

private:
    static void _PrintCurrency(clsCurrency Currency) {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";
    }

    static float _ReadRate() {
        cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;
    }

public:

    static void ShowUpdateCurrencyScreen() { 
        
        _DrawScreenHeader("\t  Update Currency Screen"); 
        string code = "";
        
        cout << "PLZ enter currency code: ";
        code = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(code)) {

            cout << "Currency is NOT found, Enter another currency code: ";
            code = clsInputValidate::ReadString();

        }

        clsCurrency currency = clsCurrency::FindByCode(code);
        _PrintCurrency(currency);


        cout << "\nAre you sure you want to update this Rate  y/n? ";
    
        char answer = 'n';
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            currency.UpdateRate(_ReadRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(currency);

    
        }
    }

};
