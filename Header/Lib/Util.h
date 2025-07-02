#pragma once
#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class clsUtil {

public:
    enum enCharType { samallLetter = 1, capitalLetter = 2, digit = 3, MixChars = 4, specialCharacter = 5 };

    static void Srand() {
        // Seeds the random number generator in C++, called only once
        srand((unsigned) time(NULL));
    }

    static int randomnumber(int From, int To) {
        // Function to generate a random number
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char getrandomCharacter(enCharType CharType) {

        // updated this method to accept mixchars
        if (CharType == MixChars) {
            // capital/Samll/digits only
            CharType = (enCharType) randomnumber(1, 3);
        }

        switch (CharType) {

            case enCharType::samallLetter: {
                return char(randomnumber(97, 122));
                break;
            }
            case enCharType::capitalLetter: {
                return char(randomnumber(65, 90));
                break;
            }
            case enCharType::specialCharacter: {
                return char(randomnumber(33, 47));
                break;
            }
            case enCharType::digit: {
                return char(randomnumber(48, 57));
                break;
            }
            defualt: {
                return char(randomnumber(65, 90));
                break;
            }
        }
    }

    static string generateWord(enCharType CharType, short Length)

    {
        string Word;

        for (int i = 1; i <= Length; i++)

        {

            Word = Word + getrandomCharacter(CharType);
        }
        return Word;
    }

    static string generateKey(enCharType CharType = capitalLetter) {

        string Key = "";


        Key = generateWord(CharType, 4) + "-";
        Key = Key + generateWord(CharType, 4) + "-";
        Key = Key + generateWord(CharType, 4) + "-";
        Key = Key + generateWord(CharType, 4);


        return Key;
    }

    static void generateKeys(short numberOfKeys, enCharType CharType) {

        for (int i = 1; i <= numberOfKeys; i++)

        {
            cout << "Key [" << i << "] : ";
            cout << generateKey(CharType) << endl;
        }
    }

    static void fillArrayWithrandomnumbers(int arr[100], int arrLength, int From, int To) {
        for (int i = 0; i < arrLength; i++)
            arr[i] = randomnumber(From, To);
    }

    static void fillArrayWithrandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength) {
        for (int i = 0; i < arrLength; i++)
            arr[i] = generateWord(CharType, Wordlength);
    }

    static void fillArrayWithrandomKeys(string arr[100], int arrLength, enCharType CharType) {
        for (int i = 0; i < arrLength; i++)
            arr[i] = generateKey(CharType);
    }

    static void Swap(int &A, int &B) {
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(double &A, double &B) {
        double Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(bool &A, bool &B) {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(char &A, char &B) {
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(string &A, string &B) {
        string Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(Date &A, Date &B) { Date::swapDates(A, B); }

    static void shuffleArray(int arr[100], int arrLength) {

        for (int i = 0; i < arrLength; i++) {
            Swap(arr[randomnumber(1, arrLength) - 1], arr[randomnumber(1, arrLength) - 1]);
        }
    }

    static void shuffleArray(string arr[100], int arrLength) {

        for (int i = 0; i < arrLength; i++) {
            Swap(arr[randomnumber(1, arrLength) - 1], arr[randomnumber(1, arrLength) - 1]);
        }
    }

    static string Tabs(short numberOfTabs) {
        string t = "";

        for (int i = 1; i < numberOfTabs; i++) {
            t = t + "\t";
            cout << t;
        }
        return t;
    }


    static string numberToText(int number) {

        if (number == 0) {
            return "";
        }

        if (number >= 1 && number <= 19) {
            string arr[] = {"",         "One",     "Two",     "Three",     "Four",     "Five",    "Six",
                            "Seven",    "Eight",   "Nine",    "Ten",       "Eleven",   "Twelve",  "Thirteen",
                            "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

            return arr[number] + " ";
        }

        if (number >= 20 && number <= 99) {
            string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return arr[number / 10] + " " + numberToText(number % 10);
        }

        if (number >= 100 && number <= 199) {
            return "One Hundred " + numberToText(number % 100);
        }

        if (number >= 200 && number <= 999) {
            return numberToText(number / 100) + "Hundreds " + numberToText(number % 100);
        }

        if (number >= 1000 && number <= 1999) {
            return "One Thousand " + numberToText(number % 1000);
        }

        if (number >= 2000 && number <= 999999) {
            return numberToText(number / 1000) + "Thousands " + numberToText(number % 1000);
        }

        if (number >= 1000000 && number <= 1999999) {
            return "One Million " + numberToText(number % 1000000);
        }

        if (number >= 2000000 && number <= 999999999) {
            return numberToText(number / 1000000) + "Millions " + numberToText(number % 1000000);
        }

        if (number >= 1000000000 && number <= 1999999999) {
            return "One Billion " + numberToText(number % 1000000000);
        } else {
            return numberToText(number / 1000000000) + "Billions " + numberToText(number % 1000000000);
        }
    }

    static string EncryptText(string Text, short EncryptionKey = 2) {

        for (int i = 0; i <= Text.length(); i++) {

            Text[i] = char((int) Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey = 2) {

        for (int i = 0; i <= Text.length(); i++) {

            Text[i] = char((int) Text[i] - EncryptionKey);
        }
        return Text;
    }
};
