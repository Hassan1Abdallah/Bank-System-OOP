#pragma once
#include <iostream>
#include "Global.h"
#include "User.h"
#include "Date.h"

using namespace std;

class Screen {
protected:
    
    static void _drawScreenHeader(string Title, string SubTitle = "") {
        Date today = Date::getSystemDate();
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "") {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\tDate: ";
        today.print();
        cout << endl;
        
    }

    static bool checkAccessRights(User::enPermissions Permission) {

        if (!CurrentUser.checkAccessPermission(Permission)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        } else {
            return true;
        }
    }
};
