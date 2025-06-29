#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class clsDeleteClientScreen : protected clsScreen {

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
    static void ShowDeleteClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
            return; // this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!BankClient::isClientExist(AccountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        BankClient Client1 = BankClient::find(AccountNumber);
        _PrintClient(Client1);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {


            if (Client1.Delete()) {
                cout << "\nClient Deleted Successfully :-)\n";
                _PrintClient(Client1);
            } else {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};
