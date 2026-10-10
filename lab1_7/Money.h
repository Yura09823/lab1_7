#pragma once
#include <string>

using namespace std;

class Money {
private:
    int counts[15];
    static const double nominals[15];

    void distributeFromTotal(double totalAmount);

public:
    double getTotal() const;

    bool Init(double amount);
    void Read();
    void Display() const;
    string toString() const;

    Money add(const Money& other) const;
    Money sub(const Money& other) const;
    double div(const Money& other) const;
    Money div(double scalar) const;
    Money mul(double scalar) const;

    bool isEqual(const Money& other) const;
    bool isGreater(const Money& other) const;
    bool isLess(const Money& other) const;
};