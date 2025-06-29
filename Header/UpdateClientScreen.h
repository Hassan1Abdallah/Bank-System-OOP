#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class clsUpdateClientScreen : protected clsScreen

{
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

    static void _ReadClientInfo(BankClient &Client) {
        cout << "\nEnter FirstName: ";
        Client.firstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.lastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.pinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.balance = clsInputValidate::ReadFloatNumber();
    }

public:
    static void ShowUpdateClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
            return; 
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!BankClient::isClientExist(AccountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        BankClient Client1 = BankClient::find(AccountNumber);

        _PrintClient(Client1);

        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";


            _ReadClientInfo(Client1);

            BankClient::enSaveResults SaveResult;

            SaveResult = Client1.save();

            switch (SaveResult) {
                case BankClient::enSaveResults::svSucceeded: {
                    cout << "\nAccount Updated Successfully :-)\n";

                    _PrintClient(Client1);
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
