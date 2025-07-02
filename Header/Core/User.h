#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
#include "String.h"
#include "Date.h"
#include "Util.h"

using namespace std;
class User : public Person {
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, addNewMode = 2 };
    enMode _mode;
    string _userName;
    string _password;
    int _permissions;

    bool _markedForDelete = false;

    string _prepareLogInRecord(string Seperator = "#//#") {
        string LoginRecord = "";
        LoginRecord += Date::getSystemDateTimeString() + Seperator;
        LoginRecord += UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(Password) + Seperator;
        LoginRecord += to_string(Permissions);
        return LoginRecord;
    }

    struct stLoginRegisterRecord;
    static stLoginRegisterRecord _convertLoginRegisterLineToRecord(string Line, string Seperator = "#//#") {
        stLoginRegisterRecord LoginRegisterRecord;


        vector<string> LoginRegisterDataLine = String::split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }

    static User _convertLinetoUserObject(string Line, string Seperator = "#//#") {
        vector<string> vUserData;
        vUserData = String::split(Line, Seperator);

        return User(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4],
                       clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
    }

    static string _converUserObjectToLine(User User, string Seperator = "#//#") {

        string UserRecord = "";
        UserRecord += User.firstName + Seperator;
        UserRecord += User.lastName + Seperator;
        UserRecord += User.email + Seperator;
        UserRecord += User.phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;
    }

    static vector<User> _loadUsersDataFromFile() {

        vector<User> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);  

        if (MyFile.is_open()) {

            string Line;


            while (getline(MyFile, Line)) {

                User User = _convertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _saveUsersDataToFile(vector<User> vUsers) {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open()) {

            for (User U: vUsers) {
                if (U.markedForDeleted() == false) {
                    // we only write records that are not marked for delete.
                    DataLine = _converUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _update() {
        vector<User> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (User &U: _vUsers) {
            if (U.UserName == UserName) {
                U = *this;
                break;
            }
        }

        _saveUsersDataToFile(_vUsers);
    }

    void _addNew() { _addDataLineToFile(_converUserObjectToLine(*this)); }

    void _addDataLineToFile(string stDataLine) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static User _getEmptyUserObject() { return User(enMode::EmptyMode, "", "", "", "", "", "", 0); }

public:

    enum enPermissions {
        eAll = -1,
        pListClients = 1,
        paddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pLoginRegister = 128
    };

    User(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName,
            string Password, int Permissions) :
        Person(FirstName, LastName, Email, Phone)

    {
        _mode = Mode;
        _userName = UserName;
        _password = Password;
        _permissions = Permissions;
    }

    bool isEmpty() { return (_mode == enMode::EmptyMode); }

    bool markedForDeleted() { return _markedForDelete; }

    string getUserName() { return _userName; }

    void setUserName(string UserName) { _userName = UserName; }

    __declspec(property(get = getUserName, put = setUserName)) string UserName;

    void setPassword(string Password) { _password = Password; }

    string getPassword() { return _password; }
    __declspec(property(get = getPassword, put = setPassword)) string Password;

    void setPermissions(int Permissions) { _permissions = Permissions; }

    int getPermissions() { return _permissions; }
    __declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

    static User find(string UserName) {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);  

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                User User = _convertLinetoUserObject(Line);
                if (User.UserName == UserName) {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _getEmptyUserObject();
    }

    static User find(string UserName, string Password) {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);  

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                User User = _convertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password) {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }
        return _getEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults save() {

        switch (_mode) {
            case enMode::EmptyMode: {
                if (isEmpty()) {
                    return enSaveResults::svFaildEmptyObject;
                }
            }

            case enMode::UpdateMode: {
                _update();
                return enSaveResults::svSucceeded;

                break;
            }

            case enMode::addNewMode: {
                // This will add new record to file or database
                if (User::isUserExist(_userName)) {
                    return enSaveResults::svFaildUserExists;
                } else {
                    _addNew();
                    // We need to set the mode to update after add new
                    _mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }

                break;
            }
        }
    }

    static bool isUserExist(string UserName) {

        User user = User::find(UserName);
        return (!user.isEmpty());
    }

    bool Delete() {
        vector<User> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (User &U: _vUsers) {
            if (U.UserName == _userName) {
                U._markedForDelete = true;
                break;
            }
        }

        _saveUsersDataToFile(_vUsers);

        *this = _getEmptyUserObject();

        return true;
    }

    static User getaddNewUserObject(string UserName) {
        return User(enMode::addNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<User> getUsersList() { return _loadUsersDataFromFile(); }

    bool checkAccessPermission(enPermissions Permissions) {

        if (this->Permissions == enPermissions::eAll)
            return true;
        if ((Permissions & this->Permissions) == Permissions) {
        
            return true;
        } else {
            return false;
        }
    }

    struct stLoginRegisterRecord {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    void registerLogIn() {

        string stDataLine = _prepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static vector<stLoginRegisterRecord> getLoginRegisterList() {
        vector<stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);  

        if (MyFile.is_open()) {

            string Line;

            stLoginRegisterRecord LoginRegisterRecord;

            while (getline(MyFile, Line)) {

                LoginRegisterRecord = _convertLoginRegisterLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }

            MyFile.close();
        }

        return vLoginRegisterRecord;
    }
};
