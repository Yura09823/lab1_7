#include "Money.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

const double Money::nominals[15] = { 500, 200, 100, 50, 20, 10, 5, 2, 1, 0.50, 0.25, 0.10, 0.05, 0.02, 0.01 };

void Money::distributeFromTotal(double totalAmount) {
    long totalKopecks = round(totalAmount * 100);
    for (int i = 0; i < 15; ++i) {
        long nominalKopecks = round(nominals[i] * 100);
        counts[i] = totalKopecks / nominalKopecks;
        totalKopecks %= nominalKopecks;
    }
}

double Money::getTotal() const {
    double total = 0;
    for (int i = 0; i < 15; ++i) {
        total += counts[i] * nominals[i];
    }
    return total;
}

bool Money::Init(double amount) {
    if (amount < 0) return false;
    distributeFromTotal(amount);
    return true;
}

void Money::Read() {
    double amount;
    do {
        cout << "¬вед≥ть суму: ";
        cin >> amount;
    } while (!Init(amount));
}

void Money::Display() const {
    cout << toString() << endl;
}

string Money::toString() const {
    stringstream sout;
    double total = getTotal();
    long grn = floor(total);
    long kop = round((total - grn) * 100);
    sout << grn << "," << setfill('0') << setw(2) << kop << " грн";
    return sout.str();
}

Money Money::add(const Money& other) const {
    Money result;
    result.Init(this->getTotal() + other.getTotal());
    return result;
}

Money Money::sub(const Money& other) const {
    Money result;
    double diff = this->getTotal() - other.getTotal();
    result.Init(diff >= 0 ? diff : 0);
    return result;
}

double Money::div(const Money& other) const {
    if (other.getTotal() == 0) return 0;
    return this->getTotal() / other.getTotal();
}

Money Money::div(double scalar) const {
    Money result;
    if (scalar > 0) result.Init(this->getTotal() / scalar);
    else result.Init(0);
    return result;
}

Money Money::mul(double scalar) const {
    Money result;
    if (scalar > 0) result.Init(this->getTotal() * scalar);
    else result.Init(0);
    return result;
}

bool Money::isEqual(const Money& other) const { return abs(this->getTotal() - other.getTotal()) < 0.001; }
bool Money::isGreater(const Money& other) const { return this->getTotal() > other.getTotal(); }
bool Money::isLess(const Money& other) const { return this->getTotal() < other.getTotal(); }