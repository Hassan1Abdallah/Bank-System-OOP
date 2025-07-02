#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "String.h"
class Currency {

private:
    enum enMode { EmptyMode = 0, UpdateMode = 1 };
    enMode _mode;

    string _country;
    string _currencyCode;
    string _currencyName;
    float _rate;

    static Currency _convertLinetoCurrencyObject(string Line, string Seperator = "#//#") {
        vector<string> vCurrencyData;
        vCurrencyData = String::split(Line, Seperator);

        return Currency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
                           stod(vCurrencyData[3]));
    }

    static string _converCurrencyObjectToLine(Currency currency, string Seperator = "#//#") {

        string stCurrencyRecord = "";
        stCurrencyRecord += currency.country() + Seperator;
        stCurrencyRecord += currency.currencyCode() + Seperator;
        stCurrencyRecord += currency.currencyName() + Seperator;
        stCurrencyRecord += to_string(currency.rate());

        return stCurrencyRecord;
    }

    static vector<Currency> _loadCurrencysDataFromFile() {

        vector<Currency> vCurrencys;

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        if (MyFile.is_open()) {

            string Line;

            while (getline(MyFile, Line)) {

                Currency Currency = _convertLinetoCurrencyObject(Line);

                vCurrencys.push_back(Currency);
            }

            MyFile.close();
        }

        return vCurrencys;
    }

    static void _saveCurrencyDataToFile(vector<Currency> vCurrencys) {

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::out); 

        string DataLine;

        if (MyFile.is_open()) {

            for (Currency C: vCurrencys) {
                DataLine = _converCurrencyObjectToLine(C);
                MyFile << DataLine << endl;
            }

            MyFile.close();
        }
    }

    void _update() {
        vector<Currency> _vCurrencys;
        _vCurrencys = _loadCurrencysDataFromFile();

        for (Currency &C: _vCurrencys) {
            if (C.currencyCode() == currencyCode()) {
                C = *this;
                break;
            }
        }

        _saveCurrencyDataToFile(_vCurrencys);
    }

    static Currency _getEmptyCurrencyObject() { return Currency(enMode::EmptyMode, "", "", "", 0); }

public:
    Currency(enMode Mode, string country, string currencyCode, string currencyName, float rate) {
        _mode = Mode;
        _country = country;
        _currencyCode = currencyCode;
        _currencyName = currencyName;
        _rate = rate;
    }

    static vector<Currency> getAllUSDRates() { return _loadCurrencysDataFromFile(); }

    bool isEmpty() { return (_mode == enMode::EmptyMode); }

    string country() { return _country; }

    string currencyCode() { return _currencyCode; }

    string currencyName() { return _currencyName; }

    void updateRate(float NewRate) {
        _rate = NewRate;
        _update();
    }

    float rate() { return _rate; }


    static Currency findByCode(string currencyCode) {

        currencyCode = String::upperAllString(currencyCode);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);  

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                Currency currency = _convertLinetoCurrencyObject(Line);
                if (currency.currencyCode() == currencyCode) {
                    MyFile.close();
                    return currency;
                }
            }

            MyFile.close();
        }

        return _getEmptyCurrencyObject();
    }

    static Currency findBycountry(string country) {
        country = String::upperAllString(country);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);  

        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                Currency currency = _convertLinetoCurrencyObject(Line);
                if (String::upperAllString(currency.country()) == country) {
                    MyFile.close();
                    return currency;
                }
            }

            MyFile.close();
        }

        return _getEmptyCurrencyObject();
    }

    static bool isCurrencyExist(string currencyCode) {
        Currency C1 = Currency::findByCode(currencyCode);
        return (!C1.isEmpty());
    }

    static vector<Currency> getCurrenciesList() { return _loadCurrencysDataFromFile(); }

    float convertToUSD(float Amount) { return (float) (Amount / rate()); }

    float convertToOtherCurrency(float Amount, Currency Currency2) {
        float AmountInUSD = convertToUSD(Amount);

        if (Currency2.currencyCode() == "USD") {
            return AmountInUSD;
        }

        return (float) (AmountInUSD * Currency2.rate());
    }
};
