#pragma once
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"

class TransferScreen : protected Screen {

private:
    static void _printClient(BankClient Client) {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.fullName();
        cout << "\nAcc. number : " << Client.getAccountnumber();
        cout << "\nBalance     : " << Client.balance;
        cout << "\n___________________\n";
    }

    static string _readAccountnumberFrom() {
        string Accountnumber;
        cout << "\nPlease Enter Account number to transfer From: ";
        Accountnumber = InputValidate::readString();
        while (!BankClient::isClientExist(Accountnumber)) {
            cout << "\nAccount number is not found, choose another one: ";
            Accountnumber = InputValidate::readString();
        }
        return Accountnumber;
    }

    static string _readAccountnumberTo() {
            string Accountnumber;
            cout << "\nPlease Enter Account number to transfer To: ";
            Accountnumber = InputValidate::readString();
            while (!BankClient::isClientExist(Accountnumber)) {
                cout << "\nAccount number is not found, choose another one: ";
                Accountnumber = InputValidate::readString();
            }
            return Accountnumber;
        }

    static float readAmount(BankClient SourceClient) {
        float Amount;

        cout << "\nEnter transfer Amount? ";

        Amount = InputValidate::readFloatnumber();

        while (Amount > SourceClient.balance) {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = InputValidate::readDblnumber();
        }
        return Amount;
    }

public:
    static void showTransferScreen() {

        _drawScreenHeader("\tTransfer Screen");

        BankClient SourceClient = BankClient::find(_readAccountnumberFrom());

        _printClient(SourceClient);

        BankClient DestinationClient = BankClient::find(_readAccountnumberTo());

        _printClient(DestinationClient);

        float Amount = readAmount(SourceClient);


        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            if (SourceClient.transfer(Amount, DestinationClient,CurrentUser.UserName)) {
                cout << "\nTransfer done successfully\n";
            } else {
                cout << "\nTransfer Faild \n";
            }
        }

        _printClient(SourceClient);
        _printClient(DestinationClient);
    }
};
