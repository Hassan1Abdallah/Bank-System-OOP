#pragma once
#include <iostream>
#include "Global.h"
#include "User.h"
#include "Date.h"

using namespace std;

class clsScreen {
protected:
    
    static void _DrawScreenHeader(string Title, string SubTitle = "") {
        clsDate today = clsDate::GetSystemDate();
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "") {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\tDate: ";
        today.Print();
        cout << endl;
        
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission) {

        if (!CurrentUser.CheckAccessPermission(Permission)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        } else {
            return true;
        }
    }
};
