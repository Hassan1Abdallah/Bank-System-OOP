
#include <iostream>
#include "BankClient.h"
#include "InputValidate.h"
#include "Person.h"
#include "Util.h"
#include "MainScreen.h"
#include "LoginScreen.h"
#include <iomanip>


void printClientRecordBalanceLine(BankClient client) {
    cout << "| " << setw(15) << left << client.getAccountNumber();
    cout << "| " << setw(40) << left << client.fullName();
    cout << "| " << setw(12) << left << client.balance;
}

void showTotalBalance() { 

    vector<BankClient> vClients = BankClient::getClientsList();

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double totalBalances = BankClient::getTotalBalances();

    if (vClients.size() == 0) {
        cout << "\t\t\tNo clients available in the system!";
    } else {
        for (BankClient client: vClients) {
            printClientRecordBalanceLine(client);
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Tatal Balances = " << totalBalances << endl;
    cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(totalBalances) << endl;
    }

void readClientInfo(BankClient& client) {

    cout << "\nEnter First Name: ";
    client.firstName = clsInputValidate::ReadString();

    cout << "\Enter Last Name: ";
    client.lastName = clsInputValidate::ReadString();

    cout << "\nEnter email: ";
    client.email = clsInputValidate::ReadString();

    cout << "\nEnter Phone: ";
    client.phone = clsInputValidate::ReadString();

    cout << "\nEnter Pin code: ";
    client.pinCode = clsInputValidate::ReadString();

    cout << "\nEnter Balance: ";
    client.balance = clsInputValidate::ReadFloatNumber();

}

void upDateClient() {
    string accountNumber = "";

    cout << "\nPLZ Enter client Account Number: ";
    accountNumber = clsInputValidate::ReadString();

    while (!BankClient::isClientExist(accountNumber)) {
    
        cout << "\nAccount Number is NOT found, PLZ Enter another client Account Number: ";
        accountNumber = clsInputValidate::ReadString();
    
    }

    BankClient client = BankClient::find(accountNumber);
    client.print();

    cout << "\n\nUpdate client info: ";
    cout << "-----------------------\n";

    readClientInfo(client);

    BankClient::enSaveResults saveResult;

    saveResult = client.save();

    switch (saveResult) {
        case BankClient::enSaveResults::svSucceeded: {
            cout << "\nAccout update succeddfully :-)";
            client.print();
            break;
        }
        case BankClient::enSaveResults::svFaildEmptyObject: {
            
            cout << "\nError account was NOT saved because it's empty";
            break;
        }
        
    }



}

int main()

{
    while (true) {
    
        clsLoginScreen::ShowLoginScreen();
    
    }


    system("pause>0");
    return 0;
}
