#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include <string>
#include "String.h"

using namespace std;

class Date {

private:
    short _day = 1;
    short _month = 1;
    short _year = 1900;

public:
    Date() {
        time_t t = time(0);
        tm *now = localtime(&t);
        _day = now->tm_mday;
        _month = now->tm_mon + 1;
        _year = now->tm_year + 1900;
    }

    Date(string sDate) {

        vector<string> vDate;
        vDate = String::split(sDate, "/");

        _day = stoi(vDate[0]);
        _month = stoi(vDate[1]);
        _year = stoi(vDate[2]);
    }

    Date(short day, short month, short Year) {

        _day = day;
        _month = month;
        _year = Year;
    }

    Date(short DateOrderInYear, short Year) {
        // This will construct a date by date order in year
        Date Date1 = getDateFromdayOrderInYear(DateOrderInYear, Year);
        _day = Date1.day;
        _month = Date1.month;
        _year = Date1.Year;
    }

    void setday(short day) { _day = day; }

    short getday() { return _day; }
    __declspec(property(get = getday, put = setday)) short day;

    void setmonth(short month) { _month = month; }

    short getmonth() { return _month; }
    __declspec(property(get = getmonth, put = setmonth)) short month;


    void setYear(short Year) { _year = Year; }

    short getYear() { return _year; }
    __declspec(property(get = getYear, put = setYear)) short Year;

    void print() { cout << dateToString() << endl; }

    static Date getSystemDate() {
        // system date
        time_t t = time(0);
        tm *now = localtime(&t);

        short day, month, Year;

        Year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;

        return Date(day, month, Year);
    }

    static string getSystemDateTimeString() {
        // system datetime string
        time_t t = time(0);
        tm *now = localtime(&t);

        short day, month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(day) + "/" + to_string(month) + "/" + to_string(Year) + " - " + to_string(Hour) + ":" +
                to_string(Minute) + ":" + to_string(Second));
    }

    static bool isValidDate(Date Date) {

        if (Date.day < 1 || Date.day > 31)
            return false;

        if (Date.month < 1 || Date.month > 12)
            return false;

        if (Date.month == 2) {
            if (isLeapYear(Date.Year)) {
                if (Date.day > 29)
                    return false;
            } else {
                if (Date.day > 28)
                    return false;
            }
        }

        short daysInmonth = numberOfdaysInAmonth(Date.month, Date.Year);

        if (Date.day > daysInmonth)
            return false;

        return true;
    }

    bool isValid() { return isValidDate(*this); }

    static string dateToString(Date Date) {
        return to_string(Date.day) + "/" + to_string(Date.month) + "/" + to_string(Date.Year);
    }

    string dateToString() { return dateToString(*this); }

    static bool isLeapYear(short Year) {

        // if year is divisible by 4 AND not divisible by 100
        // OR if year is divisible by 400
        // then it is a leap year
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool isLeapYear() { return isLeapYear(_year); }

    static short numberOfdaysInAYear(short Year) { return isLeapYear(Year) ? 365 : 366; }

    short numberOfdaysInAYear() { return numberOfdaysInAYear(_year); }

    static short numberOfHoursInAYear(short Year) { return numberOfdaysInAYear(Year) * 24; }

    short numberOfHoursInAYear() { return numberOfHoursInAYear(_year); }

    static int numberOfMinutesInAYear(short Year) { return numberOfHoursInAYear(Year) * 60; }

    int numberOfMinutesInAYear() { return numberOfMinutesInAYear(_year); }

    static int numberOfSecondsInAYear(short Year) { return numberOfMinutesInAYear(Year) * 60; }

    int numberOfSecondsInAYear() { return numberOfSecondsInAYear(); }

    static short numberOfdaysInAmonth(short month, short Year) {

        if (month < 1 || month > 12)
            return 0;

        int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[month - 1];
    }

    short numberOfdaysInAmonth() { return numberOfdaysInAmonth(_month, _year); }

    static short numberOfHoursInAmonth(short month, short Year) { return numberOfdaysInAmonth(month, Year) * 24; }

    short numberOfHoursInAmonth() { return numberOfdaysInAmonth(_month, _year) * 24; }

    static int numberOfMinutesInAmonth(short month, short Year) { return numberOfHoursInAmonth(month, Year) * 60; }

    int numberOfMinutesInAmonth() { return numberOfHoursInAmonth(_month, _year) * 60; }

    static int numberOfSecondsInAmonth(short month, short Year) { return numberOfMinutesInAmonth(month, Year) * 60; }

    int numberOfSecondsInAmonth() { return numberOfMinutesInAmonth(_month, _year) * 60; }

    static short dayOfWeekOrder(short day, short month, short Year) {
        short a, y, m;
        a = (14 - month) / 12;
        y = Year - a;
        m = month + (12 * a) - 2;
        // Gregorian:
        // 0:sun, 1:Mon, 2:Tue...etc
        return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short dayOfWeekOrder() { return dayOfWeekOrder(_day, _month, _year); }

    static string dayShortName(short dayOfWeekOrder) {
        string arrdayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

        return arrdayNames[dayOfWeekOrder];
    }

    static string dayShortName(short day, short month, short Year) {

        string arrdayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

        return arrdayNames[dayOfWeekOrder(day, month, Year)];
    }

    string dayShortName() {

        string arrdayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

        return arrdayNames[dayOfWeekOrder(_day, _month, _year)];
    }

    static string monthShortName(short monthnumber) {
        string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

        return (months[monthnumber - 1]);
    }

    string monthShortName() { return monthShortName(_month); }

    static void printmonthCalendar(short month, short Year) {
        int numberOfdays;

        // Index of the day from 0 to 6
        int current = dayOfWeekOrder(1, month, Year);

        numberOfdays = numberOfdaysInAmonth(month, Year);

        // print the current month name
        printf("\n  _______________%s_______________\n\n", monthShortName(month).c_str());

        // print the columns
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        // print appropriate spaces
        int i;
        for (i = 0; i < current; i++)
            printf("     ");

        for (int j = 1; j <= numberOfdays; j++) {
            printf("%5d", j);


            if (++i == 7) {
                i = 0;
                printf("\n");
            }
        }

        printf("\n  _________________________________\n");
    }

    void printmonthCalendar() { printmonthCalendar(_month, _year); }

    static void printYearCalendar(int Year) {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", Year);
        printf("  _________________________________\n");


        for (int i = 1; i <= 12; i++) {
            printmonthCalendar(i, Year);
        }

        return;
    }

    void printYearCalendar() {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", _year);
        printf("  _________________________________\n");


        for (int i = 1; i <= 12; i++) {
            printmonthCalendar(i, _year);
        }

        return;
    }

    static short daysFromTheBeginingOfTheYear(short day, short month, short Year) {


        short Totaldays = 0;

        for (int i = 1; i <= month - 1; i++) {
            Totaldays += numberOfdaysInAmonth(i, Year);
        }

        Totaldays += day;

        return Totaldays;
    }

    short daysFromTheBeginingOfTheYear() {


        short Totaldays = 0;

        for (int i = 1; i <= _month - 1; i++) {
            Totaldays += numberOfdaysInAmonth(i, _year);
        }

        Totaldays += _day;

        return Totaldays;
    }

    static Date getDateFromdayOrderInYear(short DateOrderInYear, short Year) {

        Date date;
        short Remainingdays = DateOrderInYear;
        short monthdays = 0;

        date.Year = Year;
        date.month = 1;

        while (true) {
            monthdays = numberOfdaysInAmonth(date.month, Year);

            if (Remainingdays > monthdays) {
                Remainingdays -= monthdays;
                date.month++;
            } else {
                date.day = Remainingdays;
                break;
            }
        }

        return date;
    }

    void adddays(short days) {


        short Remainingdays = days + daysFromTheBeginingOfTheYear(_day, _month, _year);
        short monthdays = 0;

        _month = 1;

        while (true) {
            monthdays = numberOfdaysInAmonth(_month, _year);

            if (Remainingdays > monthdays) {
                Remainingdays -= monthdays;
                _month++;

                if (_month > 12) {
                    _month = 1;
                    _year++;
                }
            } else {
                _day = Remainingdays;
                break;
            }
        }
    }

    static bool isDate1BeforeDate2(Date Date1, Date Date2) {
        return (Date1.Year < Date2.Year)
                       ? true
                       : ((Date1.Year == Date2.Year)
                                  ? (Date1.month < Date2.month
                                             ? true
                                             : (Date1.month == Date2.month ? Date1.day < Date2.day : false))
                                  : false);
    }

    bool isDateBeforeDate2(Date Date2) {
        // note: *this sends the current object :-)
        return isDate1BeforeDate2(*this, Date2);
    }

    static bool isDate1EqualDate2(Date Date1, Date Date2) {
        return (Date1.Year == Date2.Year)
                       ? ((Date1.month == Date2.month) ? ((Date1.day == Date2.day) ? true : false) : false)
                       : false;
    }

    bool isDateEqualDate2(Date Date2) { return isDate1EqualDate2(*this, Date2); }

    static bool isLastdayInmonth(Date Date) { return (Date.day == numberOfdaysInAmonth(Date.month, Date.Year)); }

    bool isLastdayInmonth() { return isLastdayInmonth(*this); }

    static bool isLastmonthInYear(short month) { return (month == 12); }

    static Date addOneday(Date Date) {
        if (isLastdayInmonth(Date)) {
            if (isLastmonthInYear(Date.month)) {
                Date.month = 1;
                Date.day = 1;
                Date.Year++;
            } else {
                Date.day = 1;
                Date.month++;
            }
        } else {
            Date.day++;
        }

        return Date;
    }

    void addOneday()

    {
        *this = addOneday(*this);
    }

    static void swapDates(Date &Date1, Date &Date2) {

        Date TempDate;
        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int getDifferenceIndays(Date Date1, Date Date2, bool IncludeEndday = false) {
        // this will take care of negative diff
        int days = 0;
        short SawpFlagValue = 1;

        if (!isDate1BeforeDate2(Date1, Date2)) {
            // Swap Dates
            swapDates(Date1, Date2);
            SawpFlagValue = -1;
        }

        while (isDate1BeforeDate2(Date1, Date2)) {
            days++;
            Date1 = addOneday(Date1);
        }

        return IncludeEndday ? ++days * SawpFlagValue : days * SawpFlagValue;
    }

    int getDifferenceIndays(Date Date2, bool IncludeEndday = false) {
        return getDifferenceIndays(*this, Date2, IncludeEndday);
    }

    static short calculateMyAgeIndays(Date DateOfBirth) {
        return getDifferenceIndays(DateOfBirth, Date::getSystemDate(), true);
    }
    // above no need to have nonstatic function for the object because it does not depend on any data from it.

    static Date increaseDateByOneWeek(Date &Date) {

        for (int i = 1; i <= 7; i++) {
            Date = addOneday(Date);
        }

        return Date;
    }

    void increaseDateByOneWeek() { increaseDateByOneWeek(*this); }

    Date increaseDateByXWeeks(short Weeks, Date &Date) {

        for (short i = 1; i <= Weeks; i++) {
            Date = increaseDateByOneWeek(Date);
        }
        return Date;
    }

    void increaseDateByXWeeks(short Weeks) { increaseDateByXWeeks(Weeks, *this); }

    Date increaseDateByOnemonth(Date &Date) {

        if (Date.month == 12) {
            Date.month = 1;
            Date.Year++;
        } else {
            Date.month++;
        }

        // last check day in date should not exceed max days in the current month
        //  example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should
        //  be 28/2/2022
        short numberOfdaysInCurrentmonth = numberOfdaysInAmonth(Date.month, Date.Year);
        if (Date.day > numberOfdaysInCurrentmonth) {
            Date.day = numberOfdaysInCurrentmonth;
        }

        return Date;
    }

    void increaseDateByOnemonth() { increaseDateByOnemonth(*this); }

    Date increaseDateByXdays(short days, Date &Date) {

        for (short i = 1; i <= days; i++) {
            Date = addOneday(Date);
        }
        return Date;
    }

    void increaseDateByXdays(short days) { increaseDateByXdays(days, *this); }

    Date increaseDateByXmonths(short months, Date &Date) {

        for (short i = 1; i <= months; i++) {
            Date = increaseDateByOnemonth(Date);
        }
        return Date;
    }

    void increaseDateByXmonths(short months) { increaseDateByXmonths(months, *this); }

    static Date increaseDateByOneYear(Date &Date) {
        Date.Year++;
        return Date;
    }

    void increaseDateByOneYear() { increaseDateByOneYear(*this); }

    Date increaseDateByXYears(short Years, Date &Date) {
        Date.Year += Years;
        return Date;
    }

    void increaseDateByXYears(short Years) { increaseDateByXYears(Years); }

    Date increaseDateByOneDecade(Date &Date) {
        // Period of 10 years
        Date.Year += 10;
        return Date;
    }

    void increaseDateByOneDecade() { increaseDateByOneDecade(*this); }

    Date increaseDateByXDecades(short Decade, Date &Date) {
        Date.Year += Decade * 10;
        return Date;
    }

    void increaseDateByXDecades(short Decade) { increaseDateByXDecades(Decade, *this); }

    Date increaseDateByOneCentury(Date &Date) {
        // Period of 100 years
        Date.Year += 100;
        return Date;
    }

    void increaseDateByOneCentury() { increaseDateByOneCentury(*this); }

    Date increaseDateByOneMillennium(Date &Date) {
        // Period of 1000 years
        Date.Year += 1000;
        return Date;
    }

    Date increaseDateByOneMillennium() { increaseDateByOneMillennium(*this); }

    static Date decreaseDateByOneday(Date Date) {
        if (Date.day == 1) {
            if (Date.month == 1) {
                Date.month = 12;
                Date.day = 31;
                Date.Year--;
            } else {

                Date.month--;
                Date.day = numberOfdaysInAmonth(Date.month, Date.Year);
            }
        } else {
            Date.day--;
        }

        return Date;
    }

    void decreaseDateByOneday() { decreaseDateByOneday(*this); }

    static Date decreaseDateByOneWeek(Date &Date) {

        for (int i = 1; i <= 7; i++) {
            Date = decreaseDateByOneday(Date);
        }

        return Date;
    }

    void decreaseDateByOneWeek() { decreaseDateByOneWeek(*this); }

    static Date decreaseDateByXWeeks(short Weeks, Date &Date) {

        for (short i = 1; i <= Weeks; i++) {
            Date = decreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void decreaseDateByXWeeks(short Weeks) { decreaseDateByXWeeks(Weeks, *this); }

    static Date decreaseDateByOnemonth(Date &date) {

        if (date.month == 1) {
            date.month = 12;
            date.Year--;
        } else
            date.month--;


        // last check day in date should not exceed max days in the current month
        // example if date is 31/3/2022 decreasing one month should not be 31/2/2022, it should
        // be 28/2/2022
        short numberOfdaysInCurrentmonth = numberOfdaysInAmonth(date.month, date.Year);
        if (date.day > numberOfdaysInCurrentmonth) {
            date.day = numberOfdaysInCurrentmonth;
        }


        return date;
    }

    void decreaseDateByOnemonth() { decreaseDateByOnemonth(*this); }

    static Date decreaseDateByXdays(short days, Date &Date) {

        for (short i = 1; i <= days; i++) {
            Date = decreaseDateByOneday(Date);
        }
        return Date;
    }

    void decreaseDateByXdays(short days) { decreaseDateByXdays(days, *this); }

    static Date decreaseDateByXmonths(short months, Date &Date) {

        for (short i = 1; i <= months; i++) {
            Date = decreaseDateByOnemonth(Date);
        }
        return Date;
    }

    void decreaseDateByXmonths(short months) { decreaseDateByXmonths(months, *this); }

    static Date decreaseDateByOneYear(Date &Date) {

        Date.Year--;
        return Date;
    }

    void decreaseDateByOneYear() { decreaseDateByOneYear(*this); }

    static Date decreaseDateByXYears(short Years, Date &date) {

        date.Year -= Years;
        return date;
    }

    void decreaseDateByXYears(short Years) { decreaseDateByXYears(Years, *this); }

    static Date decreaseDateByOneDecade(Date &date) {
        // Period of 10 years
        date.Year -= 10;
        return date;
    }

    void decreaseDateByOneDecade() { decreaseDateByOneDecade(*this); }

    static Date decreaseDateByXDecades(short Decades, Date &date) {

        date.Year -= Decades * 10;
        return date;
    }

    void decreaseDateByXDecades(short Decades) { decreaseDateByXDecades(Decades, *this); }

    static Date decreaseDateByOneCentury(Date &date) {
        // Period of 100 years
        date.Year -= 100;
        return date;
    }

    void decreaseDateByOneCentury() { decreaseDateByOneCentury(*this); }

    static Date decreaseDateByOneMillennium(Date &date) {
        // Period of 1000 years
        date.Year -= 1000;
        return date;
    }

    void decreaseDateByOneMillennium() { decreaseDateByOneMillennium(*this); }


    static short isEndOfWeek(Date Date) { return dayOfWeekOrder(Date.day, Date.month, Date.Year) == 6; }

    short isEndOfWeek() { return isEndOfWeek(*this); }

    static bool isWeekEnd(Date date) {
        // Weekends are Fri and Sat
        short dayIndex = dayOfWeekOrder(date.day, date.month, date.Year);
        return (dayIndex == 5 || dayIndex == 6);
    }

    bool isWeekEnd() { return isWeekEnd(*this); }

    static bool isBusinessday(Date date) {
        return !isWeekEnd(date);
    }

    bool isBusinessday() { return isBusinessday(*this); }

    static short daysUntilTheEndOfWeek(Date Date) { return 6 - dayOfWeekOrder(Date.day, Date.month, Date.Year); }

    short daysUntilTheEndOfWeek() { return daysUntilTheEndOfWeek(*this); }

    static short daysUntilTheEndOfmonth(Date Date1) {

        Date EndOfMontDate;
        EndOfMontDate.day = numberOfdaysInAmonth(Date1.month, Date1.Year);
        EndOfMontDate.month = Date1.month;
        EndOfMontDate.Year = Date1.Year;

        return getDifferenceIndays(Date1, EndOfMontDate, true);
    }

    short daysUntilTheEndOfmonth() { return daysUntilTheEndOfmonth(*this); }

    static short daysUntilTheEndOfYear(Date Date1) {

        Date EndOfYearDate;
        EndOfYearDate.day = 31;
        EndOfYearDate.month = 12;
        EndOfYearDate.Year = Date1.Year;

        return getDifferenceIndays(Date1, EndOfYearDate, true);
    }

    short daysUntilTheEndOfYear() { return daysUntilTheEndOfYear(*this); }

    // i added this method to calculate business days between 2 days
    static short calculateBusinessdays(Date DateFrom, Date DateTo) {

        short days = 0;
        while (isDate1BeforeDate2(DateFrom, DateTo)) {
            if (isBusinessday(DateFrom))
                days++;

            DateFrom = addOneday(DateFrom);
        }

        return days;
    }

    static short calculateVacationdays(Date DateFrom, Date DateTo) {
       return calculateBusinessdays(DateFrom, DateTo);
    }
    // above method is eough , no need to have method for the object

    static Date calculateVacationReturnDate(Date DateFrom, short Vacationdays) {

        short WeekEndcounter = 0;

        for (short i = 1; i <= Vacationdays; i++) {

            if (isWeekEnd(DateFrom))
                WeekEndcounter++;

            DateFrom = addOneday(DateFrom);
        }
        // to add weekends
        for (short i = 1; i <= WeekEndcounter; i++)
            DateFrom = addOneday(DateFrom);

        return DateFrom;
    }

    static bool isDate1AfterDate2(Date Date1, Date Date2) {
        return (!isDate1BeforeDate2(Date1, Date2) && !isDate1EqualDate2(Date1, Date2));
    }

    bool isDateAfterDate2(Date Date2) { return isDate1AfterDate2(*this, Date2); }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    static enDateCompare compareDates(Date Date1, Date Date2) {
        if (isDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (isDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;

        return enDateCompare::After;
    }

    enDateCompare compareDates(Date Date2) { return compareDates(*this, Date2); }
};
