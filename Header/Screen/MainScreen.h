#pragma once
#include <iostream>
#include "ClientListScreen.h"
#include "InputValidate.h"
#include "Screen.h"
#include "addNewClientScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateClientScreen.h"
#include "FindClientScreen.h"
#include "TransactionsScreen.h"
#include "ManageUsers.h"
#include "Global.h"
#include "LoginRegisterScreen.h"
#include "CurrencyExchangeMainScreen.h"


using namespace std;

class MainScreen : protected Screen {


private:
    enum enMainMenueOptions {
        eListClients = 1,
        eaddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eLoginRegister =8,
        eCurrencyExchange = 9,
        eExit = 10
    };

    static short _readMainMenueOption() {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 10]? ";
        short Choice = InputValidate::readShortnumberBetween(1, 10, "Enter number between 1 to 10? ");
        return Choice;
    }

    static void _goBackToMainMenue() {
        cout << setw(37) << left << ""
             << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        showMainMenue();
    }

    static void _showAllClientsScreen() {
        clsClientListScreen::showClientsList();
    }

    static void _showaddNewClientsScreen() { 

        addNewClientScreen::showaddNewClientScreen();
    
    }

    static void _showDeleteClientScreen() {
        
        DeleteClientScreen::showDeleteClientScreen();
    }

    static void _showUpdateClientScreen() { 

        UpdateClientScreen::showUpdateClientScreen();
    }

    static void _showFindClientScreen() { 
        
        FindClientScreen::showFindClientScreen();
    
    }

    static void _showTransactionsMenue() { 
        
        TransactionsScreen::showTransactionsMenue();
    }

    static void _showManageUsersMenue() {
          
        ManageUsersScreen::showManageUsersMenue(); 
    }

    static void _showLoginRegisterScreen() {

        LoginRegisterScreen::showLoginRegisterScreen();
    }

    static void _showCurrencyExchangeScreen() {

            CurrencyExchangeMainScreen::showCurrenciesMenue();
        }

    static void _logout() {
        
        CurrentUser = User::find("", "");
    }

    static void _perfromMainMenueOption(enMainMenueOptions MainMenueOption) {
        switch (MainMenueOption) {
            case enMainMenueOptions::eListClients: {
                system("cls");
                _showAllClientsScreen();
                _goBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eaddNewClient: {
                system("cls");
                _showaddNewClientsScreen();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eDeleteClient: {
                system("cls");
                _showDeleteClientScreen();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eUpdateClient: {
                system("cls");
                _showUpdateClientScreen();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eFindClient: {
                system("cls");
                _showFindClientScreen();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eShowTransactionsMenue: {
                system("cls");
                _showTransactionsMenue();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eManageUsers: {
                system("cls");
                _showManageUsersMenue();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eLoginRegister : {
                system("cls");
                _showLoginRegisterScreen();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eCurrencyExchange : {
                system("cls");
                _showCurrencyExchangeScreen();
                _goBackToMainMenue();
                break;
            }

            case enMainMenueOptions::eExit: {
                system("cls");
                _logout();

                break;
            }
        }
    }


public:
    static void showMainMenue() {

        system("cls");
        _drawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t\t\tMain Menue\n";
        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t[1] Show Client List.\n";
        cout << setw(37) << left << ""
             << "\t[2] add New Client.\n";
        cout << setw(37) << left << ""
             << "\t[3] Delete Client.\n";
        cout << setw(37) << left << ""
             << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << ""
             << "\t[5] find Client.\n";
        cout << setw(37) << left << ""
             << "\t[6] Transactions.\n";
        cout << setw(37) << left << ""
             << "\t[7] Manage Users.\n";
        cout << setw(37) << left << ""
             << "\t[8] Login Register.\n";
        cout << setw(37) << left << ""
             << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << ""
             << "\t[10] Logout.\n";
        cout << setw(37) << left << ""
             << "===========================================\n";

        _perfromMainMenueOption((enMainMenueOptions) _readMainMenueOption());
    }
};
