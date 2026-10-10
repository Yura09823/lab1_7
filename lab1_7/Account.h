// account.h
#pragma once
#include <string>
#include "Money.h" 

using namespace std;

class Account
{
private:
    string surname;
    unsigned int nomer;
    double percent; 
    Money summa;   

public:
    void change_owner(string newOwner);
    bool zabraty_money(Money amount); 
    void put_money(Money amount);     
    void calculate_percent();
    double to_dolar(double exchange) const;
    double to_euro(double exchange) const;
    string toString() const;

    string getSurname() const { return surname; }
    int getNomer() const { return nomer; }
    double getPercent() const { return percent; }
    Money getSumma() const { return summa; }

    bool setSurname(string value);
    bool setNomer(unsigned int value);
    bool setPercent(double value);
    bool setSumma(Money value);

    bool Init(string surname, unsigned int nomer, double percent, Money summa);
    void Read();
    void Display() const;
};

Account makeAccount(string o, unsigned int nomer, double percent, Money summa);