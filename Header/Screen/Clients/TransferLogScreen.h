#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include "BankClient.h"
#include "Screen.h"


class TransferLogScreen : protected Screen {

private:
    static void printTransferLogRecordLine(BankClient::stTrnsferLogRecord TransferLogRecord) {

        cout << setw(8) << left << ""
             << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountnumber;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountnumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;
    }

public:
    static void showTransferLogScreen() {


        vector<BankClient::stTrnsferLogRecord> vTransferLogRecord = BankClient::getTransfersLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _drawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << ""
             << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (BankClient::stTrnsferLogRecord Record: vTransferLogRecord) {

                printTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << ""
             << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }
};
