#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "String.h"
#include "Person.h"
using namespace std;

class BankClient : public Person {
private:
    enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 , deleteMode = 3};

    enMode _mode;
    string _accountNumber;
    string _pinCode;
    float _balance;
    bool _markedForDelete = false;

    static BankClient _convertLinetoClientObject(string line, string seperator = "#//#") {

        vector<string> vClientData;
        vClientData = clsString::Split(line, seperator);
        return BankClient(enMode::updateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
                          vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _converClientObjectToLine(BankClient client, string Seperator = "#//#") {

        string stClientRecord = "";
        stClientRecord += client.firstName + Seperator;
        stClientRecord += client.lastName + Seperator;
        stClientRecord += client.email + Seperator;
        stClientRecord += client.phone + Seperator;
        stClientRecord += client.getAccountNumber() + Seperator;
        stClientRecord += client.pinCode + Seperator;
        stClientRecord += to_string(client.balance);

        return stClientRecord;
    }

    static vector<BankClient> _loadClientsDataFromFile() {

        vector<BankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); // read Mode

        if (MyFile.is_open()) {

            string Line;


            while (getline(MyFile, Line)) {

                BankClient Client = _convertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();
        }

        return vClients;
    }

    static void _SaveCleintsDataToFile(vector<BankClient> vClients) {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open()) {

            for (BankClient &C: vClients) {
                if (!C._markedForDelete)
                {
                    DataLine = _converClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _update() {
        vector<BankClient> _vClients;
        _vClients = _loadClientsDataFromFile();

        for (BankClient & C: _vClients) {
            if (C.getAccountNumber() == getAccountNumber()) {
                C = *this;
                break;
            }
        }

        _SaveCleintsDataToFile(_vClients);
    }

    void _addNew() { _AddDataLineToFile(_converClientObjectToLine(*this)); }

    void _AddDataLineToFile(string stDataLine) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static BankClient _getEmptyClientObject() { return BankClient(enMode::emptyMode, "", "", "", "", "", "", 0); }

public:
    BankClient(enMode mode, string firstName, string lastName, string email, string phone, string accountNumber,
               string pinCode, float balance) :
        Person(firstName, lastName, email, phone) {
        _mode = mode;
        _accountNumber = accountNumber;
        _pinCode = pinCode;
        _balance = balance;
    }


    bool isEmpty() { return (_mode == enMode::emptyMode); }

    string getAccountNumber() { return _accountNumber; }

    void setPinCode(string pinCode) { _pinCode = pinCode; }

    string getPinCode() { return _pinCode; }

    __declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

    void setBalance(float balance) { _balance = balance; }

    float getBalance() const { return _balance; }

    __declspec(property(get = getBalance, put = setBalance)) float balance;

    /*  void print() {

          cout << "\nClient card:";
          cout << "\n-------------------------";
          cout << "\nFirst Name: " << firstName;
          cout << "\nLast Name: " << lastName;
          cout << "\nFull Name: " << fullName();
          cout << "\nEmail : " << email;
          cout << "\nPhone : " << phone;
          cout << "\nAcc. Number : " << _accountNumber;
          cout << "\nPassword : " << pinCode;
          cout << "\nAccount Balance: " << balance;
          cout << "\n-------------------------\n";
      }*/

    static BankClient find(string accountNumber) {

        vector<BankClient> vClients;

        fstream myFile;
        myFile.open("clients.txt", ios::in);

        if (myFile.is_open()) {

            string line;
            while (getline(myFile, line)) {

                BankClient client = _convertLinetoClientObject(line);
                if (client.getAccountNumber() == accountNumber) {

                    myFile.close();
                    return client;
                }
                vClients.push_back(client);
            }

            myFile.close();
        }
        return _getEmptyClientObject();
    }

    static BankClient find(string accountNumber, string pinCode) {

        vector<BankClient> vClients;

        fstream myFile;
        myFile.open("clients.txt", ios::in);

        if (myFile.is_open()) {

            string line;
            while (getline(myFile, line)) {

                BankClient client = _convertLinetoClientObject(line);
                if (client.getAccountNumber() == accountNumber && client._pinCode == pinCode) {

                    myFile.close();
                    return client;
                }
                vClients.push_back(client);
            }

            myFile.close();
        }
        return _getEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

    enSaveResults save() {

        switch (_mode) {
            case enMode::emptyMode: {
                if (isEmpty()) {

                    return enSaveResults::svFaildEmptyObject;
                }
            }

            case enMode::updateMode: {


                _update();

                return enSaveResults::svSucceeded;

                break;
            }

            case enMode::addNewMode: {
                // This will add new record to file or database
                if (BankClient::isClientExist(_accountNumber)) {
                    return enSaveResults::svFaildAccountNumberExists;
                } else {
                    _addNew();

                    // We need to set the mode to update after add new
                    _mode = enMode::updateMode;
                    return enSaveResults::svSucceeded;
                }

                break;
            }
        }
    }


    static bool isClientExist(string accountNumber) {

        BankClient client = BankClient::find(accountNumber);
        return (!client.isEmpty());
    }

    static BankClient getAddNewClientObject(string accountNumber) {

        return BankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0);
    }

    bool Delete() {
        vector<BankClient> vClients;
        vClients = _loadClientsDataFromFile();
        for (BankClient &C: vClients) {
            if (C.getAccountNumber() == _accountNumber) {
                C._markedForDelete = true;
                _SaveCleintsDataToFile(vClients);
                *this = _getEmptyClientObject();
                return true;
                break;
            }
        }
        return false;
    }

    static vector<BankClient> getClientsList() {

        vector<BankClient> allClients = _loadClientsDataFromFile();
        vector<BankClient> activeClients;

        for (BankClient &C: allClients) {
            if (!C._markedForDelete) {
                activeClients.push_back(C);
            }
        }

        return activeClients;
    }

    static double getTotalBalances() {
        vector<BankClient> vClients = BankClient::getClientsList();

        double TotalBalances = 0;

        for (BankClient Client: vClients) {

            TotalBalances += Client.balance;
        }

        return TotalBalances;
    }

     void Deposit(double Amount) {
        _balance += Amount;
        save();
    }

    bool Withdraw(double Amount) {
        if (Amount > _balance) {
            return false;
        } else {
            _balance -= Amount;
            save();
            return true;
        }
    }
};
