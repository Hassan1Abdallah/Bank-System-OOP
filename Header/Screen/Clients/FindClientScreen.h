#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class FindClientScreen : protected Screen {

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
    static void showFindClientScreen() {

        if (!checkAccessRights(User::enPermissions::pFindClient)) {
            return;
        }

        _drawScreenHeader("\tFind Client Screen");

        string Accountnumber;
        cout << "\nPlease Enter Account number: ";
        Accountnumber = InputValidate::readString();
        while (!BankClient::isClientExist(Accountnumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            Accountnumber = InputValidate::readString();
        }

        BankClient Client1 = BankClient::find(Accountnumber);

        if (!Client1.isEmpty()) {
            cout << "\nClient Found :-)\n";
        } else {
            cout << "\nClient Was not Found :-(\n";
        }

        _printClient(Client1);
    }
};
