#pragma once
#include <iomanip>
#include <iostream>
#include "BankClient.h"
#include "Screen.h"
#include "Util.h"

class TotalBalancesScreen : protected Screen {

private:
    static void printClientRecordBalanceLine(BankClient Client) {
        cout << setw(25) << left << ""
             << "| " << setw(15) << left << Client.getAccountnumber();
        cout << "| " << setw(40) << left << Client.fullName();
        cout << "| " << setw(12) << left << Client.balance;
    }

public:
    static void showTotalBalances() {

        vector<BankClient> vClients = BankClient::getClientsList();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _drawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << ""
             << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << ""
             << "| " << left << setw(15) << "Accout number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << ""
             << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double TotalBalances = BankClient::getTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (BankClient Client: vClients) {
                printClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << setw(25) << left << ""
             << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(8) << left << ""
             << "\t\t\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << ""
             << "\t\t\t\t  ( " << clsUtil::numberToText(TotalBalances) << ")";
    }
};
