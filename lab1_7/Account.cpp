// account.cpp
#include "Account.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

bool Account::setSurname(string value) {
    if (!value.empty()) {
        surname = value;
        return true;
    }
    surname = "нев≥домо";
    return false;
}

bool Account::setNomer(unsigned int value) {
    if (value > 0) {
        nomer = value;
        return true;
    }
    else {
        nomer = 0;
        return false;
    }
}

bool Account::setPercent(double value) {
    if (value >= 0.0) {
        percent = value;
        return true;
    }
    else {
        percent = 0.0;
        return false;
    }
}

bool Account::setSumma(Money value) {
    summa = value;
    return true;
}

bool Account::Init(string surname, unsigned int nomer, double percent, Money summa) {
    return setSurname(surname) && setNomer(nomer) && setPercent(percent) && setSumma(summa);
}

void Account::Read() {
    string surname;
    int nomer;
    double percent;
    double amount; // ƒл€ тимчасового зчитуванн€ суми

    cout << "surname = "; cin >> surname;

    Money initial_sum;
    do {
        cout << "nomer   = "; cin >> nomer;
        cout << "percent = "; cin >> percent;
        cout << "summa   = "; cin >> amount;
        initial_sum.Init(amount);
    } while (!Init(surname, nomer, percent, initial_sum));
}

void Account::Display() const {
    cout << "surname = " << surname << endl;
    cout << "nomer   = " << nomer << endl;
    cout << "percent = " << percent << "%" << endl;
    cout << "summa   = " << summa.toString() << endl; // ¬икористанн€ Display з класу Money
}

void Account::change_owner(string newOwner) {
    if (setSurname(newOwner)) {
        cout << "successfully. owner: " << newOwner << endl;
    }
    else {
        cout << "error" << endl;
    }
}

bool Account::zabraty_money(Money amount) {
    if (!summa.isLess(amount) && amount.getTotal() > 0) {
        summa = summa.sub(amount); // ¬икористанн€ методу sub()
        return true;
    }
    return false;
}

void Account::put_money(Money amount) {
    summa = summa.add(amount); // ¬икористанн€ методу add()
}

void Account::calculate_percent() {
    Money interest = summa.mul(percent / 100.0);
    summa = summa.add(interest);
}

double Account::to_dolar(double exchange) const {
    return summa.getTotal() / exchange;
}

double Account::to_euro(double exchange) const {
    return summa.getTotal() / exchange;
}

string Account::toString() const {
    double total = summa.getTotal(); // ќтримуЇмо загальну суму €к double дл€ конвертац≥њ
    int UAH = (int)floor(total);
    int kopecks = (int)round((total - UAH) * 100);

    if (UAH == 0) return "нуль грн. " + to_string(kopecks) + " коп.";

    string ones[] = { "", "одна", "дв≥", "три", "чотири", "п'€ть", "ш≥сть", "с≥м", "в≥с≥м", "дев'€ть" };
    string ones_m[] = { "", "один", "два", "три", "чотири", "п'€ть", "ш≥сть", "с≥м", "в≥с≥м", "дев'€ть" };
    string teens[] = { "дес€ть", "одинадц€ть", "дванадц€ть", "тринадц€ть", "чотирнадц€ть", "п'€тнадц€ть", "ш≥стнадц€ть", "с≥мнадц€ть", "в≥с≥мнадц€ть", "дев'€тнадц€ть" };
    string tens[] = { "", "", "двадц€ть", "тридц€ть", "сорок", "п'€тдес€т", "ш≥стдес€т", "с≥мдес€т", "в≥с≥мдес€т", "дев'€носто" };
    string hundreds[] = { "", "сто", "дв≥ст≥", "триста", "чотириста", "п'€тсот", "ш≥стсот", "с≥мсот", "в≥с≥мсот", "дев'€тсот" };

    string result = "";
    int thousands = (UAH / 1000) % 1000;
    int units = UAH % 1000;

    if (thousands > 0) {
        result += hundreds[thousands / 100] + (thousands / 100 > 0 ? " " : "");
        int th_tens = thousands % 100;
        if (th_tens >= 10 && th_tens <= 19) {
            result += teens[th_tens - 10] + " тис€ч ";
        }
        else {
            result += tens[th_tens / 10] + (th_tens / 10 > 0 ? " " : "");
            result += ones[th_tens % 10] + (th_tens % 10 > 0 ? " " : "");
            if (th_tens % 10 == 1) result += "тис€ча ";
            else if (th_tens % 10 >= 2 && th_tens % 10 <= 4) result += "тис€ч≥ ";
            else result += "тис€ч ";
        }
    }

    if (units > 0) {
        result += hundreds[units / 100] + (units / 100 > 0 ? " " : "");
        int un_tens = units % 100;
        if (un_tens >= 10 && un_tens <= 19) {
            result += teens[un_tens - 10] + " ";
        }
        else {
            result += tens[un_tens / 10] + (un_tens / 10 > 0 ? " " : "");
            result += ones[un_tens % 10] + (un_tens % 10 > 0 ? " " : "");
        }
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    stringstream ss;
    ss << result << " грн. " << (kopecks < 10 ? "0" : "") << kopecks << " коп.";
    return ss.str();
}

Account makeAccount(string o, unsigned int nomer, double percent, Money summa) {
    Account acc;
    if (!acc.Init(o, nomer, percent, summa)) {
        cout << "error" << endl;
        exit(1);
    }
    return acc;
}