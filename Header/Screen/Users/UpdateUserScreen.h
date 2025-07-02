#pragma once
#include <iostream>
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"
#include "User.h"

class UpdateUserScreen : protected Screen

{
private:
    static void _readUserInfo(User &User) {
        cout << "\nEnter FirstName: ";
        User.firstName = InputValidate::readString();

        cout << "\nEnter LastName: ";
        User.lastName = InputValidate::readString();

        cout << "\nEnter Email: ";
        User.email = InputValidate::readString();

        cout << "\nEnter Phone: ";
        User.phone = InputValidate::readString();

        cout << "\nEnter Password: ";
        User.Password = InputValidate::readString();

        cout << "\nEnter Permission: ";
        User.Permissions = _readPermissionsToset();
    }

    static void _printUser(User User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.firstName;
        cout << "\nLastName    : " << User.lastName;
        cout << "\nFull Name   : " << User.fullName();
        cout << "\nEmail       : " << User.email;
        cout << "\nPhone       : " << User.phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
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
    static void showUpdateUserScreen() {

        _drawScreenHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter User UserName: ";
        UserName = InputValidate::readString();

        while (!User::isUserExist(UserName)) {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = InputValidate::readString();
        }

        User User1 = User::find(UserName);

        _printUser(User1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";


            _readUserInfo(User1);

            User::enSaveResults SaveResult;

            SaveResult = User1.save();

            switch (SaveResult) {
                case User::enSaveResults::svSucceeded: {
                    cout << "\nUser Updated Successfully :-)\n";

                    _printUser(User1);
                    break;
                }
                case User::enSaveResults::svFaildEmptyObject: {
                    cout << "\nError User was not saved because it's Empty";
                    break;
                }
            }
        }
    }
};
