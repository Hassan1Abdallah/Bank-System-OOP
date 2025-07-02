#pragma once
#include <iostream>
#include "InputValidate.h"
#include "Person.h"
#include "Screen.h"
#include "User.h"

class FindUserScreen : protected Screen {

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
    static void showFindUserScreen() {

        _drawScreenHeader("\t  find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = InputValidate::readString();
        while (!User::isUserExist(UserName)) {
            cout << "\nUser is not found, choose another one: ";
            UserName = InputValidate::readString();
        }

        User User1 = User::find(UserName);

        if (!User1.isEmpty()) {
            cout << "\nUser Found :-)\n";
        } else {
            cout << "\nUser Was not Found :-(\n";
        }

        _printUser(User1);
    }
};
