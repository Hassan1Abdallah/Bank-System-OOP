#pragma once

#include <iomanip>
#include <iostream>
#include "Screen.h"
#include "User.h"

class ListUsersScreen : protected Screen {

private:
    static void _printUserRecordLine(User user) {

        cout << setw(8) << left << ""
             << "| " << setw(12) << left << user.UserName;
        cout << "| " << setw(25) << left << user.fullName();
        cout << "| " << setw(12) << left << user.phone;
        cout << "| " << setw(20) << left << user.email;
        cout << "| " << setw(10) << left << user.Password;
        cout << "| " << setw(12) << left << user.Permissions;
    }

public:
    static void showUsersList() {
        vector<User> vUsers = User::getUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _drawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << ""
             << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (User User: vUsers) {

                _printUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;
    }
};
