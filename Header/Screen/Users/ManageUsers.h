#pragma once
#include <iomanip>
#include <iostream>
#include "InputValidate.h"
#include "Screen.h"
#include "UsersListScreen.h"
#include "addNewUserScreen.h"
#include "DeleteUserScreen.h"
#include "UpdateUserScreen.h"
#include "FindUserScreen.h"

using namespace std;

class ManageUsersScreen : protected Screen {

private:
    enum enManageUsersMenueOptions {
        eListUsers = 1,
        eaddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenue = 6
    };

    static short readManageUsersMenueOption() {
        cout << setw(37) << left << ""
             << "Choose what do you want to do? [1 to 6]? ";
        short Choice = InputValidate::readShortnumberBetween(1, 6, "Enter number between 1 to 6? ");
        return Choice;
    }

    static void _goBackToManageUsersMenue() {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        showManageUsersMenue();
    }

    static void _showListUsersScreen() {
        
        ListUsersScreen::showUsersList();
    }

    static void _showaddNewUserScreen() {
        
        addNewUserScreen::showaddNewUserScreen();
    }

    static void _showDeleteUserScreen() {
        
        DeleteUserScreen::showDeleteUserScreen();
    }

    static void _showUpdateUserScreen() { 
        
        UpdateUserScreen::showUpdateUserScreen();    
    }

    static void _showFindUserScreen() {
        
        FindUserScreen::showFindUserScreen();    
    }


    static void _performManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption) {

        switch (ManageUsersMenueOption) {
            case enManageUsersMenueOptions::eListUsers: {
                system("cls");
                _showListUsersScreen();
                _goBackToManageUsersMenue();
                break;
            }

            case enManageUsersMenueOptions::eaddNewUser: {
                system("cls");
                _showaddNewUserScreen();
                _goBackToManageUsersMenue();
                break;
            }

            case enManageUsersMenueOptions::eDeleteUser: {
                system("cls");
                _showDeleteUserScreen();
                _goBackToManageUsersMenue();
                break;
            }

            case enManageUsersMenueOptions::eUpdateUser: {
                system("cls");
                _showUpdateUserScreen();
                _goBackToManageUsersMenue();
                break;
            }

            case enManageUsersMenueOptions::eFindUser: {
                system("cls");

                _showFindUserScreen();
                _goBackToManageUsersMenue();
                break;
            }

            case enManageUsersMenueOptions::eMainMenue: {
                // do nothing here the main screen will handle it :-) ;
            }
        }
    }


public:
    static void showManageUsersMenue() {

        if (!checkAccessRights(User::enPermissions::pManageUsers)) {
            return; 
        }

        system("cls");
        _drawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << ""
             << "===========================================\n";
        cout << setw(37) << left << ""
             << "\t[1] List Users.\n";
        cout << setw(37) << left << ""
             << "\t[2] add New User.\n";
        cout << setw(37) << left << ""
             << "\t[3] Delete User.\n";
        cout << setw(37) << left << ""
             << "\t[4] Update User.\n";
        cout << setw(37) << left << ""
             << "\t[5] find User.\n";
        cout << setw(37) << left << ""
             << "\t[6] Main Menue.\n";
        cout << setw(37) << left << ""
             << "===========================================\n";

        _performManageUsersMenueOption((enManageUsersMenueOptions) readManageUsersMenueOption());
    }
};
