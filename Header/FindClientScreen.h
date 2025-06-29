#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class clsFindClientScreen : protected clsScreen {

private:
    static void _PrintClient(BankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.firstName;
        cout << "\nLastName    : " << Client.lastName;
        cout << "\nFull Name   : " << Client.fullName();
        cout << "\nEmail       : " << Client.email;
        cout << "\nPhone       : " << Client.phone;
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nPassword    : " << Client.pinCode;
        cout << "\nBalance     : " << Client.balance;
        cout << "\n___________________\n";
    }

public:
    static void ShowFindClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) {
            return;
        }

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!BankClient::isClientExist(AccountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        BankClient Client1 = BankClient::find(AccountNumber);

        if (!Client1.isEmpty()) {
            cout << "\nClient Found :-)\n";
        } else {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client1);
    }
};
