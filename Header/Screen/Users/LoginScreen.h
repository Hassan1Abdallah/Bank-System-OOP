#pragma once

#include <iomanip>
#include <iostream>
#include "Global.h"
#include "MainScreen.h"
#include "Screen.h"
#include "User.h"

class LoginScreen : protected Screen {

private:
    static bool _login() {
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

            CurrentUser = User::find(Username, Password);

            LoginFaild = CurrentUser.isEmpty();

        } while (LoginFaild);
        CurrentUser.registerLogIn();
        MainScreen::showMainMenue();
        return true;
    }

public:
    static bool showLoginScreen() {
        system("cls");
        _drawScreenHeader("\t  Login Screen");
        return _login();

    }
};
