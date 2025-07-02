#pragma once
#include <iomanip>
#include <iostream>
#include "InputValidate.h"
#include "Screen.h"
#include "CurrenciesListScreen.h"
#include "FindCurrencyScreen.h"
#include "UpdateCurrencyScreen.h"
#include "CurrencyCalculatorScreen.h"

using namespace std;

class CurrencyExchangeMainScreen : protected Screen {

private:
    enum enCurrenciesMainMenueOptions {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateCurrencyRate = 3,
        eCurrencyCalculator = 4,
        eMainMenue = 5
    };

    static short readCurrenciesMainMenueOptions() {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 5]? ";
        short Choice = InputValidate::readShortnumberBetween(1, 5, "Enter number between 1 to 5? ");
        return Choice;
    }

    static void _goBackToCurrenciesMenue() {
        cout << "\n\nPress any key to go back to Currencies Menue...";
        system("pause>0");
        showCurrenciesMenue();
    }

    static void _showCurrenciesListScreen() {
        
        CurrenciesListScreen::showCurrenciesListScreen();    
    }

    static void _showFindCurrencyScreen() { 
        
        FindCurrencyScreen::showFindCurrencyScreen();    
    }

    static void _showUpdateCurrencyRateScreen() { 
        
        UpdateCurrencyScreen::showUpdateCurrencyScreen();    
    }

    static void _showCurrencyCalculatorScreen() {
        
        CurrencyCalculatorScreen::showCurrencyCalculatorScreen();    
    }

    static void _performCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrenciesMainMenueOptions) {

        switch (CurrenciesMainMenueOptions) {
            case enCurrenciesMainMenueOptions::eListCurrencies: {
                system("cls");
                _showCurrenciesListScreen();
                _goBackToCurrenciesMenue();
                break;
            }

            case enCurrenciesMainMenueOptions::eFindCurrency: {
                system("cls");
                _showFindCurrencyScreen();
                _goBackToCurrenciesMenue();
                break;
            }

            case enCurrenciesMainMenueOptions::eUpdateCurrencyRate: {
                system("cls");
                _showUpdateCurrencyRateScreen();
                _goBackToCurrenciesMenue();
                break;
            }

            case enCurrenciesMainMenueOptions::eCurrencyCalculator: {
                system("cls");
                _showCurrencyCalculatorScreen();
                _goBackToCurrenciesMenue();
                break;
            }

            case enCurrenciesMainMenueOptions::eMainMenue: {
                // do nothing here the main screen will handle it :-) ;
            }
        }
    }

public:
    static void showCurrenciesMenue() {

        system("cls");
        _drawScreenHeader("    Currancy Exhange Main Screen");

        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t\t  Currency Exhange Menue\n";
        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t[1] List Currencies.\n";
        cout << setw(37) << left << ""
             << "\t[2] find Currency.\n";
        cout << setw(37) << left << ""
             << "\t[3] Update rate.\n";
        cout << setw(37) << left << ""
             << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << ""
             << "\t[5] Main Menue.\n";
        cout << setw(37) << left << ""
             << "===========================================\n";

        _performCurrenciesMainMenueOptions((enCurrenciesMainMenueOptions) readCurrenciesMainMenueOptions());
    }
};
