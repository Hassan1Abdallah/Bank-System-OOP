#pragma once

#include <iomanip>
#include <iostream>
#include "BankClient.h"
#include "Screen.h"

class clsClientListScreen : protected clsScreen {

private:
    static void PrintClientRecordLine(BankClient Client) {

        cout << setw(8) << left << ""
             << "| " << setw(15) << left << Client.getAccountNumber();
        cout << "| " << setw(20) << left << Client.fullName();
        cout << "| " << setw(12) << left << Client.phone;
        cout << "| " << setw(20) << left << Client.email;
        cout << "| " << setw(10) << left << Client.pinCode;
        cout << "| " << setw(12) << left << Client.balance;
    }

public:
    static void ShowClientsList() {

        if (!CheckAccessRights(clsUser::enPermissions::pListClients)) {
            return; // this will exit the function and it will not continue
        }


        vector<BankClient> vClients = BankClient::getClientsList();
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << ""
             << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (BankClient Client: vClients) {

                PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
