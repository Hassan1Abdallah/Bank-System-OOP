#pragma once

#include <iomanip>
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Screen.h"

class addNewClientScreen : protected Screen {
private:
    static void _readClientInfo(BankClient &Client) {
        cout << "\nEnter FirstName: ";
        Client.firstName = InputValidate::readString();

        cout << "\nEnter LastName: ";
        Client.lastName = InputValidate::readString();

        cout << "\nEnter Email: ";
        Client.email = InputValidate::readString();

        cout << "\nEnter Phone: ";
        Client.phone = InputValidate::readString();

        cout << "\nEnter PinCode: ";
        Client.pinCode = InputValidate::readString();

        cout << "\nEnter Account Balance: ";
        Client.balance = InputValidate::readFloatnumber();
    }

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
    static void showaddNewClientScreen() {

        if (!checkAccessRights(User::enPermissions::paddNewClient)) {
            return; // this will exit the function and it will not continue
        }

        _drawScreenHeader("\t  add New Client Screen");

        string Accountnumber = "";

        cout << "\nPlease Enter Account number: ";
        Accountnumber = InputValidate::readString();
        while (BankClient::isClientExist(Accountnumber)) {
            cout << "\nAccount number is Already Used, Choose another one: ";
            Accountnumber = InputValidate::readString();
        }

        BankClient NewClient = BankClient::getaddNewClientObject(Accountnumber);


        _readClientInfo(NewClient);

        BankClient::enSaveResults SaveResult;

        SaveResult = NewClient.save();

        switch (SaveResult) {
            case BankClient::enSaveResults::svSucceeded: {
                cout << "\nAccount addeded Successfully :-)\n";
                _printClient(NewClient);
                break;
            }
            case BankClient::enSaveResults::svFaildEmptyObject: {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            case BankClient::enSaveResults::svFaildAccountnumberExists: {
                cout << "\nError account was not saved because account number is used!\n";
                break;
            }
        }
    }
};
