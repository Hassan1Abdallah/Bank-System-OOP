#pragma once
#include <iomanip>
#include <iostream>
#include "InputValidate.h"
#include "Screen.h"
#include "DepositScreen.h"
#include "WithdrawScreen.h"
#include "TotalBalancesScreen.h"
#include "TransferScreen.h"
#include "TransferLogScreen.h"

using namespace std;

class TransactionsScreen : protected Screen {


private:
    enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eTransfer = 4, eTransferLog = 5, eShowMainMenue = 6 };

    static short readTransactionsMenueOption() {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 6]? ";
        short Choice = InputValidate::readShortnumberBetween(1, 6, "Enter number between 1 to 6? ");
        return Choice;
    }

    static void _showDepositScreen() { 
              
        DepositScreen::showDepositScreen();
    }

    static void _showWithdrawScreen() {
        
        WithdrawScreen::showWithdrawScreen();
    }

    static void _showTotalBalancesScreen() { 
            
        TotalBalancesScreen::showTotalBalances();
    }

    static void _showTransferScreen() { 
            
        TransferScreen::showTransferScreen();
    }

    static void _showTransferLogScreen() { 
        TransferLogScreen::showTransferLogScreen();
    }

    static void _goBackToTransactionsMenue() {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        showTransactionsMenue();
    }

    static void _performTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption) {
        switch (TransactionsMenueOption) {
            case enTransactionsMenueOptions::eDeposit: {
                system("cls");
                _showDepositScreen();
                _goBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eWithdraw: {
                system("cls");
                _showWithdrawScreen();
                _goBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eShowTotalBalance: {
                system("cls");
                _showTotalBalancesScreen();
                _goBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eTransfer: {
                system("cls");
                _showTransferScreen();
                _goBackToTransactionsMenue();
                break;
            }

            case enTransactionsMenueOptions::eTransferLog: {
                system("cls");
                _showTransferLogScreen();
                _goBackToTransactionsMenue();
                break;
            }


            case enTransactionsMenueOptions::eShowMainMenue: {

                // do nothing here the main screen will handle it :-) ;
            }
        }
    }


public:
    static void showTransactionsMenue() {

        if (!checkAccessRights(User::enPermissions::pTranactions)) {
            return;
        }

        system("cls");
        _drawScreenHeader("\t  Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n"; 
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] deposit.\n";
        cout << setw(37) << left << "" << "\t[2] withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] transfer.\n";
        cout << setw(37) << left << "" << "\t[5] transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _performTransactionsMenueOption((enTransactionsMenueOptions) readTransactionsMenueOption());
    }
};
