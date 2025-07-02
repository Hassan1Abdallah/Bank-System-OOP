#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "String.h"
#include "Person.h"
#include "Date.h"
using namespace std;

class BankClient : public Person {
private:
    enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 , deleteMode = 3};

    enMode _mode;
    string _accountnumber;
    string _pinCode;
    float _balance;
    bool _markedForDelete = false;

    static BankClient _convertLinetoClientObject(string line, string seperator = "#//#") {

        vector<string> vClientData;
        vClientData = String::split(line, seperator);
        return BankClient(enMode::updateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
                          vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _converClientObjectToLine(BankClient client, string Seperator = "#//#") {

        string stClientRecord = "";
        stClientRecord += client.firstName + Seperator;
        stClientRecord += client.lastName + Seperator;
        stClientRecord += client.email + Seperator;
        stClientRecord += client.phone + Seperator;
        stClientRecord += client.getAccountnumber() + Seperator;
        stClientRecord += client.pinCode + Seperator;
        stClientRecord += to_string(client.balance);

        return stClientRecord;
    }

    static vector<BankClient> _loadClientsDataFromFile() {

        vector<BankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);  

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

    static void _saveCleintsDataToFile(vector<BankClient> vClients) {

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
            if (C.getAccountnumber() == getAccountnumber()) {
                C = *this;
                break;
            }
        }

        _saveCleintsDataToFile(_vClients);
    }

    void _addNew() { _addDataLineToFile(_converClientObjectToLine(*this)); }

    void _addDataLineToFile(string stDataLine) {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static BankClient _getEmptyClientObject() { return BankClient(enMode::emptyMode, "", "", "", "", "", "", 0); }
    
    string _prepareTransferLogRecord(float Amount, BankClient DestinationClient, string UserName, string Seperator = "#//#") {
        string TransferLogRecord = "";
        TransferLogRecord += Date::getSystemDateTimeString() + Seperator;
        TransferLogRecord += getAccountnumber() + Seperator;
        TransferLogRecord += DestinationClient.getAccountnumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(balance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.balance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _registerTransferLog(float Amount, BankClient DestinationClient, string UserName) {

        string stDataLine = _prepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }
    struct stTrnsferLogRecord;
    static stTrnsferLogRecord _convertTransferLogLineToRecord(string Line, string Seperator = "#//#") {
        stTrnsferLogRecord TrnsferLogRecord;

        vector<string> vTrnsferLogRecordLine = String::split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountnumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountnumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;
    }

public:

    struct stTrnsferLogRecord {
        string DateTime;
        string SourceAccountnumber;
        string DestinationAccountnumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;
    };

    BankClient(enMode mode, string firstName, string lastName, string email, string phone, string accountnumber,
               string pinCode, float balance) :
        Person(firstName, lastName, email, phone) {
        _mode = mode;
        _accountnumber = accountnumber;
        _pinCode = pinCode;
        _balance = balance;
    }


    bool isEmpty() { return (_mode == enMode::emptyMode); }

    string getAccountnumber() { return _accountnumber; }

    void setPinCode(string pinCode) { _pinCode = pinCode; }

    string getPinCode() { return _pinCode; }

    __declspec(property(get = getPinCode, put = setPinCode)) string pinCode;

    void setBalance(float balance) { _balance = balance; }

    float getBalance() const { return _balance; }

    __declspec(property(get = getBalance, put = setBalance)) float balance;

    static BankClient find(string accountnumber) {

        vector<BankClient> vClients;

        fstream myFile;
        myFile.open("clients.txt", ios::in);

        if (myFile.is_open()) {

            string line;
            while (getline(myFile, line)) {

                BankClient client = _convertLinetoClientObject(line);
                if (client.getAccountnumber() == accountnumber) {

                    myFile.close();
                    return client;
                }
                vClients.push_back(client);
            }

            myFile.close();
        }
        return _getEmptyClientObject();
    }

    static BankClient find(string accountnumber, string pinCode) {

        vector<BankClient> vClients;

        fstream myFile;
        myFile.open("clients.txt", ios::in);

        if (myFile.is_open()) {

            string line;
            while (getline(myFile, line)) {

                BankClient client = _convertLinetoClientObject(line);
                if (client.getAccountnumber() == accountnumber && client._pinCode == pinCode) {

                    myFile.close();
                    return client;
                }
                vClients.push_back(client);
            }

            myFile.close();
        }
        return _getEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountnumberExists = 2 };

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
                if (BankClient::isClientExist(_accountnumber)) {
                    return enSaveResults::svFaildAccountnumberExists;
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


    static bool isClientExist(string accountnumber) {

        BankClient client = BankClient::find(accountnumber);
        return (!client.isEmpty());
    }

    static BankClient getaddNewClientObject(string accountnumber) {

        return BankClient(enMode::addNewMode, "", "", "", "", accountnumber, "", 0);
    }

    bool Delete() {
        vector<BankClient> vClients;
        vClients = _loadClientsDataFromFile();
        for (BankClient &C: vClients) {
            if (C.getAccountnumber() == _accountnumber) {
                C._markedForDelete = true;
                _saveCleintsDataToFile(vClients);
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

     void deposit(double Amount) {
        _balance += Amount;
        save();
    }

    bool withdraw(double Amount) {
        if (Amount > _balance) {
            return false;
        } else {
            _balance -= Amount;
            save();
            return true;
        }
    }

    bool transfer(float Amount, BankClient &DestinationClient, string UserName) {
        if (Amount > balance) {
            return false;
        }

        withdraw(Amount);
        DestinationClient.deposit(Amount);
        _registerTransferLog(Amount, DestinationClient, UserName);

        return true;
    }

    static vector<stTrnsferLogRecord> getTransfersLogList() {
        vector<stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::in);  

        if (MyFile.is_open()) {

            string Line;

            stTrnsferLogRecord TransferRecord;

            while (getline(MyFile, Line)) {

                TransferRecord = _convertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);
            }

            MyFile.close();
        }

        return vTransferLogRecord;
    }
};
