#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class UpdateClientScreen : protected Screen

{
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

public:
    static void showUpdateClientScreen() {

        if (!checkAccessRights(User::enPermissions::pUpdateClients)) {
            return; 
        }

        _drawScreenHeader("\tUpdate Client Screen");

        string Accountnumber = "";

        cout << "\nPlease Enter client Account number: ";
        Accountnumber = InputValidate::readString();

        while (!BankClient::isClientExist(Accountnumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            Accountnumber = InputValidate::readString();
        }

        BankClient Client1 = BankClient::find(Accountnumber);

        _printClient(Client1);

        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";


            _readClientInfo(Client1);

            BankClient::enSaveResults SaveResult;

            SaveResult = Client1.save();

            switch (SaveResult) {
                case BankClient::enSaveResults::svSucceeded: {
                    cout << "\nAccount Updated Successfully :-)\n";

                    _printClient(Client1);
                    break;
                }
                case BankClient::enSaveResults::svFaildEmptyObject: {
                    cout << "\nError account was not saved because it's Empty";
                    break;
                }
            }
        }
    }
};
