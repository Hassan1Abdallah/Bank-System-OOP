#pragma once

#include <iomanip>
#include <iostream>
#include "Global.h"
#include "MainScreen.h"
#include "Screen.h"
#include "User.h"

class clsLoginScreen : protected clsScreen {

private:
    static bool _Login() {
        bool LoginFaild = false;
        int trials = 0;
        string Username, Password;
        do {

            if (LoginFaild) {
                cout << "\nInvlaid Username/Password!\n";
                trials++;
                cout << "You have " << 3 - trials << " Trials to login\n\n";
                
            }
            if (trials == 3) {
                cout << "Yor locked after 3 faild triald\n\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:
    static bool ShowLoginScreen() {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }
};
