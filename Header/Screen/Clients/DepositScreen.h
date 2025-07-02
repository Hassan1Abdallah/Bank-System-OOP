#pragma once

#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Screen.h"

class DepositScreen : protected Screen {

private:
    static void _printClient(BankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.firstName;
        cout << "\nLastName    : " << Client.lastName;
        cout << "\nFull Name   : " << Client.fullName();
        cout << "\nEmail       : " << Client.email;
        cout << "\nPhone       : " << Client.phone;
        cout << "\nAcc. number : " << Client.getAccountnumber();
        cout << "\nPassword    : " << Client.pinCode;
        cout << "\nBalance     : " << Client.balance;
        cout << "\n___________________\n";
    }

    static string _readAccountnumber() {
        string Accountnumber = "";
        cout << "\nPlease enter Accountnumber? ";
        cin >> Accountnumber;
        return Accountnumber;
    }

public:
    static void showDepositScreen() {
        _drawScreenHeader("\t   deposit Screen");

        string Accountnumber = _readAccountnumber();


        while (!BankClient::isClientExist(Accountnumber)) {
            cout << "\nClient with [" << Accountnumber << "] does not exist.\n";
            Accountnumber = _readAccountnumber();
        }

        BankClient Client1 = BankClient::find(Accountnumber);
        _printClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        Amount = InputValidate::readDblnumber();

        cout << "\nAre you sure you want to perform this transaction? y/n ? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y') {
            Client1.deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance is: " << Client1.balance;

        } else {
            cout << "\nOperation was cancelled.\n";
        }
    }
};
