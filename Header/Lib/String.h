#pragma once

#include <iostream>
#include <vector>

using namespace std;

class String {

private:
    string _value;

public:
    String() { _value = ""; }

    String(string Value) { _value = Value; }


    void setValue(string Value) { _value = Value; }

    string getValue() { return _value; }

    __declspec(property(get = getValue, put = setValue)) string Value;


    static short length(string S1) { return S1.length(); };

    short length() { return _value.length(); };

    static short countWords(string S1) {

        string delim = " "; // delimiter
        short counter = 0;
        short pos = 0;
        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = S1.find(delim)) != std::string::npos) {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "") {
                counter++;
            }

            // erase() until positon and move to next word.
            S1.erase(0, pos + delim.length());
        }

        if (S1 != "") {
            counter++; // it counts the last word of the string.
        }

        return counter;
    }

    short countWords() { return countWords(_value); };

    static string upperFirstLetterOfEachWord(string S1) {

        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++) {

            if (S1[i] != ' ' && isFirstLetter) {
                S1[i] = toupper(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    void upperFirstLetterOfEachWord() {
        // no need to return value , this function will directly update the object value
        _value = upperFirstLetterOfEachWord(_value);
    }

    static string lowerFirstLetterOfEachWord(string S1) {

        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++) {

            if (S1[i] != ' ' && isFirstLetter) {
                S1[i] = tolower(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    void lowerFirstLetterOfEachWord() {


        // no need to return value , this function will directly update the object value
        _value = lowerFirstLetterOfEachWord(_value);
    }

    static string upperAllString(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

    void upperAllString() { _value = upperAllString(_value); }

    static string lowerAllString(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }

    void lowerAllString() { _value = lowerAllString(_value); }

    static char invertLetterCase(char char1) { return isupper(char1) ? tolower(char1) : toupper(char1); }

    static string invertAllLettersCase(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = invertLetterCase(S1[i]);
        }
        return S1;
    }

    void invertAllLettersCase() { _value = invertAllLettersCase(_value); }

    enum enWhatTocount { SmallLetters = 0, capitalLetters = 1, All = 3 };

    static short countLetters(string S1, enWhatTocount WhatTocount = enWhatTocount::All) {


        if (WhatTocount == enWhatTocount::All) {
            return S1.length();
        }

        short counter = 0;

        for (short i = 0; i < S1.length(); i++) {

            if (WhatTocount == enWhatTocount::capitalLetters && isupper(S1[i]))
                counter++;


            if (WhatTocount == enWhatTocount::SmallLetters && islower(S1[i]))
                counter++;
        }

        return counter;
    }

    static short countcapitalLetters(string S1) {

        short counter = 0;

        for (short i = 0; i < S1.length(); i++) {

            if (isupper(S1[i]))
                counter++;
        }

        return counter;
    }

    short countcapitalLetters() { return countcapitalLetters(_value); }

    static short countSmallLetters(string S1) {

        short counter = 0;

        for (short i = 0; i < S1.length(); i++) {

            if (islower(S1[i]))
                counter++;
        }

        return counter;
    }

    short countSmallLetters() { return countSmallLetters(_value); }

    static short countSpecificLetter(string S1, char Letter, bool MatchCase = true) {

        short counter = 0;

        for (short i = 0; i < S1.length(); i++) {

            if (MatchCase) {
                if (S1[i] == Letter)
                    counter++;
            } else {
                if (tolower(S1[i]) == tolower(Letter))
                    counter++;
            }
        }

        return counter;
    }

    short countSpecificLetter(char Letter, bool MatchCase = true) {
        return countSpecificLetter(_value, Letter, MatchCase);
    }

    static bool isVowel(char Ch1) {
        Ch1 = tolower(Ch1);

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    static short countVowels(string S1) {

        short counter = 0;

        for (short i = 0; i < S1.length(); i++) {

            if (isVowel(S1[i]))
                counter++;
        }

        return counter;
    }

    short countVowels() { return countVowels(_value); }

    static vector<string> split(string S1, string Delim) {

        vector<string> vString;

        short pos = 0;
        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = S1.find(Delim)) != std::string::npos) {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "") {
                vString.push_back(sWord);
            }

            S1.erase(0, pos + Delim.length()); /* erase() until positon and move to next word. */
        }

        if (S1 != "") {
            vString.push_back(S1); // it adds last word of the string.
        }

        return vString;
    }

    vector<string> split(string Delim) { return split(_value, Delim); }

    static string trimLeft(string S1) {


        for (short i = 0; i < S1.length(); i++) {
            if (S1[i] != ' ') {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }

    void trimLeft() { _value = trimLeft(_value); }

    static string trimRight(string S1) {


        for (short i = S1.length() - 1; i >= 0; i--) {
            if (S1[i] != ' ') {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    void trimRight() { _value = trimRight(_value); }

    static string trim(string S1) { return (trimLeft(trimRight(S1))); }

    void trim() { _value = trim(_value); }

    static string joinString(vector<string> vString, string Delim) {

        string S1 = "";

        for (string &s: vString) {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static string joinString(string arrString[], short length, string Delim) {

        string S1 = "";

        for (short i = 0; i < length; i++) {
            S1 = S1 + arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static string reverseWordsInString(string S1) {

        vector<string> vString;
        string S2 = "";

        vString = split(S1, " ");

        // declare iterator
        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin()) {

            --iter;

            S2 += *iter + " ";
        }

        S2 = S2.substr(0, S2.length() - 1); // remove last space.

        return S2;
    }

    void reverseWordsInString() { _value = reverseWordsInString(_value); }

    static string replaceWord(string S1, string StringToreplace, string sRepalceTo, bool MatchCase = true) {

        vector<string> vString = split(S1, " ");

        for (string &s: vString) {

            if (MatchCase) {
                if (s == StringToreplace) {
                    s = sRepalceTo;
                }

            } else {
                if (lowerAllString(s) == lowerAllString(StringToreplace)) {
                    s = sRepalceTo;
                }
            }
        }

        return joinString(vString, " ");
    }

    string replaceWord(string StringToreplace, string sRepalceTo) {
        return replaceWord(_value, StringToreplace, sRepalceTo);
    }

    static string removePunctuations(string S1) {

        string S2 = "";

        for (short i = 0; i < S1.length(); i++) {
            if (!ispunct(S1[i])) {
                S2 += S1[i];
            }
        }

        return S2;
    }

    void removePunctuations() { _value = removePunctuations(_value); }
};
