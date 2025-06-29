#pragma once

#include <iomanip>
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Screen.h"

class clsAddNewClientScreen : protected clsScreen {
private:
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
    static void ShowAddNewClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
            return; // this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (BankClient::isClientExist(AccountNumber)) {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        BankClient NewClient = BankClient::getAddNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        BankClient::enSaveResults SaveResult;

        SaveResult = NewClient.save();

        switch (SaveResult) {
            case BankClient::enSaveResults::svSucceeded: {
                cout << "\nAccount Addeded Successfully :-)\n";
                _PrintClient(NewClient);
                break;
            }
            case BankClient::enSaveResults::svFaildEmptyObject: {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            case BankClient::enSaveResults::svFaildAccountNumberExists: {
                cout << "\nError account was not saved because account number is used!\n";
                break;
            }
        }
    }
};
