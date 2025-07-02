#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class DeleteClientScreen : protected Screen {

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


public:
    static void showDeleteClientScreen() {

        if (!checkAccessRights(User::enPermissions::pDeleteClient)) {
            return; // this will exit the function and it will not continue
        }

        _drawScreenHeader("\tDelete Client Screen");

        string Accountnumber = "";

        cout << "\nPlease Enter Account number: ";
        Accountnumber = InputValidate::readString();

        while (!BankClient::isClientExist(Accountnumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            Accountnumber = InputValidate::readString();
        }

        BankClient Client1 = BankClient::find(Accountnumber);
        _printClient(Client1);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {


            if (Client1.Delete()) {
                cout << "\nClient Deleted Successfully :-)\n";
                _printClient(Client1);
            } else {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};
