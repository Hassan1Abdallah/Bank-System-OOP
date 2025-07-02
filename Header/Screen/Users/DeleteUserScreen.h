#pragma once
#include <iostream>
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"
#include "User.h"

class DeleteUserScreen : protected Screen {

private:
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

public:
    static void showDeleteUserScreen() {

        _drawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = InputValidate::readString();
        while (!User::isUserExist(UserName)) {
            cout << "\nUser is not found, choose another one: ";
            UserName = InputValidate::readString();
        }

        User User1 = User::find(UserName);
        _printUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y') {

            if (User1.Delete()) {
                cout << "\nUser Deleted Successfully :-)\n";
                _printUser(User1);
            } else {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }
};
