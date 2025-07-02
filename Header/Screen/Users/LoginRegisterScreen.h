#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include "Screen.h"
#include "User.h"


class LoginRegisterScreen : protected Screen {

private:
    static void printLoginRegisterRecordLine(User::stLoginRegisterRecord LoginRegisterRecord) {

        cout << setw(8) << left << ""
             << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
    }

public:
    static void showLoginRegisterScreen() {

        if (!checkAccessRights(User::enPermissions::pLoginRegister)) {
            return; // this will exit the function and it will not continue
        }

        vector<User::stLoginRegisterRecord> vLoginRegisterRecord = User::getLoginRegisterList();

        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t\t(" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _drawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << ""
             << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (User::stLoginRegisterRecord Record: vLoginRegisterRecord) {

                printLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
