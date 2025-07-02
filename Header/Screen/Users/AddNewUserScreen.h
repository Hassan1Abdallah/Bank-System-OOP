#pragma once

#include <iomanip>
#include <iostream>
#include "InputValidate.h"
#include "Screen.h"
#include "User.h"

class addNewUserScreen : protected Screen {
private:
    static void _readUserInfo(User &user) {
        cout << "\nEnter FirstName: ";
        user.firstName = InputValidate::readString();

        cout << "\nEnter LastName: ";
        user.lastName = InputValidate::readString();

        cout << "\nEnter Email: ";
        user.email = InputValidate::readString();

        cout << "\nEnter Phone: ";
        user.phone = InputValidate::readString();

        cout << "\nEnter Password: ";
        user.Password = InputValidate::readString();

        cout << "\nEnter Permission: ";
        user.Permissions = _readPermissionsToset();
    }

    static void _printUser(User user) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.firstName;
        cout << "\nLastName    : " << user.lastName;
        cout << "\nFull Name   : " << user.fullName();
        cout << "\nEmail       : " << user.email;
        cout << "\nPhone       : " << user.phone;
        cout << "\nUser Name   : " << user.UserName;
        cout << "\nPassword    : " << user.Password;
        cout << "\nPermissions : " << user.Permissions;
        cout << "\n___________________\n";
    }

    static int _readPermissionsToset() {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {


            Permissions += User::enPermissions::pListClients;
        }

        cout << "\nadd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += User::enPermissions::paddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += User::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += User::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += User::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += User::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += User::enPermissions::pManageUsers;
        }

        cout << "\nLogin Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            Permissions += User::enPermissions::pLoginRegister;
        }

        return Permissions;
    }

public:
    static void showaddNewUserScreen() {

        _drawScreenHeader("\t  add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = InputValidate::readString();
        while (User::isUserExist(UserName)) {
            cout << "\nUserName is Already Used, Choose another one: ";
            UserName = InputValidate::readString();
        }

        User NewUser = User::getaddNewUserObject(UserName);

        _readUserInfo(NewUser);

        User::enSaveResults SaveResult;

        SaveResult = NewUser.save();

        switch (SaveResult) {
            case User::enSaveResults::svSucceeded: {
                cout << "\nUser addeded Successfully :-)\n";
                _printUser(NewUser);
                break;
            }
            case User::enSaveResults::svFaildEmptyObject: {
                cout << "\nError User was not saved because it's Empty";
                break;
            }
            case User::enSaveResults::svFaildUserExists: {
                cout << "\nError User was not saved because UserName is used!\n";
                break;
            }
        }
    }
};
