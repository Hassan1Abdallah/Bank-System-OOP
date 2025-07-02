#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class clsTransferScreen : protected clsScreen {

private:
    static void _PrintClient(BankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.fullName();
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nBalance     : " << Client.balance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumberFrom() {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!BankClient::isClientExist(AccountNumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static string _ReadAccountNumberTo() {
            string AccountNumber;
            cout << "\nPlease Enter Account Number to Transfer To: ";
            AccountNumber = clsInputValidate::ReadString();
            while (!BankClient::isClientExist(AccountNumber)) {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }
            return AccountNumber;
        }

    static float ReadAmount(BankClient SourceClient) {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadFloatNumber();

        while (Amount > SourceClient.balance) {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

public:
    static void ShowTransferScreen() {

        _DrawScreenHeader("\tTransfer Screen");

        BankClient SourceClient = BankClient::find(_ReadAccountNumberFrom());

        _PrintClient(SourceClient);

        BankClient DestinationClient = BankClient::find(_ReadAccountNumberTo());

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);


        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName)) {
                cout << "\nTransfer done successfully\n";
            } else {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }
};
