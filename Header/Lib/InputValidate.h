#pragma once
#include <iostream>
#include <string>
#include "Date.h"
#include "String.h"

class InputValidate {

public:
    static bool isnumberBetween(int number, int From, int To) {
        if (number >= From && number <= To)
            return true;
        else
            return false;
    }

    static bool isnumberBetween(double number, double From, double To) {
        if (number >= From && number <= To)
            return true;
        else
            return false;
    }

    static bool isDateBetween(Date date, Date From, Date To) {
        // Date>=From && Date<=To
        if ((Date::isDate1AfterDate2(date, From) || Date::isDate1EqualDate2(date, From)) &&
            (Date::isDate1BeforeDate2(date, To) || Date::isDate1EqualDate2(date, To))) {
            return true;
        }

        // Date>=To && Date<=From
        if ((Date::isDate1AfterDate2(date, To) || Date::isDate1EqualDate2(date, To)) &&
            (Date::isDate1BeforeDate2(date, From) || Date::isDate1EqualDate2(date, From))) {
            return true;
        }

        return false;
    }


    static short readShortnumber(string ErrorMessage = "Invalid number, Enter again\n") {
        short number;
        while (!(cin >> number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return number;
    }

    static int readIntnumber(string ErrorMessage = "Invalid number, Enter again\n") {
        int number;
        while (!(cin >> number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return number;
    }

    static short readShortnumberBetween(short From, short To,
                                        string ErrorMessage = "number is not within range, Enter again:\n") {
        int number = readShortnumber();

        while (!isnumberBetween(number, From, To)) {
            cout << ErrorMessage;
            number = readShortnumber();
        }
        return number;
    }

    static int readIntnumberBetween(int From, int To,
                                    string ErrorMessage = "number is not within range, Enter again:\n") {
        int number = readIntnumber();

        while (!isnumberBetween(number, From, To)) {
            cout << ErrorMessage;
            number = readIntnumber();
        }
        return number;
    }

    static double readFloatnumber(string ErrorMessage = "Invalid number, Enter again\n") {
        float number;
        while (!(cin >> number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return number;
    }

    static double readFloatnumberBetween(double From, double To,
                                         string ErrorMessage = "number is not within range, Enter again:\n") {
        float number = readFloatnumber();

        while (!isnumberBetween(number, From, To)) {
            cout << ErrorMessage;
            number = readFloatnumber();
        }
        return number;
    }

    static double readDblnumber(string ErrorMessage = "Invalid number, Enter again\n") {
        double number;
        while (!(cin >> number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return number;
    }

    static double readDblnumberBetween(double From, double To,
                                       string ErrorMessage = "number is not within range, Enter again:\n") {
        double number = readDblnumber();

        while (!isnumberBetween(number, From, To)) {
            cout << ErrorMessage;
            number = readDblnumber();
        }
        return number;
    }

    static bool isValideDate(Date date) { return Date::isValidDate(date); }

    static string readString() {
        string S1 = "";
        // Usage of std::ws will extract allthe whitespace character
        getline(cin >> ws, S1);
        return S1;
    }
};
