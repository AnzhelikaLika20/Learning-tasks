#include "rational.h"

Rational::Rational() {
    Set(0, 1);
}

Rational::Rational(int value) {
    Set(value, 1);
}

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    if (denom < 0) {
        numer *= (-1);
        denom *= (-1);
    }
    int64_t gcd_numer_denom = std::gcd(numer, denom);
    denom_ = static_cast<int>(denom / gcd_numer_denom);
    numer_ = static_cast<int>(numer / gcd_numer_denom);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numer = lhs.GetNumerator() * denom / lhs.GetDenominator() + rhs.GetNumerator() * denom / rhs.GetDenominator();
    lhs.Set(numer, denom);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int numer = lhs.GetNumerator() * rhs.GetNumerator();
    int denom = lhs.GetDenominator() * rhs.GetDenominator();
    lhs.Set(numer, denom);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    int numer = ratio.GetNumerator() + ratio.GetDenominator();
    ratio.Set(numer, ratio.GetDenominator());
    return ratio;
}  // faster than += 1

Rational& operator--(Rational& ratio) {
    int numer = ratio.GetNumerator() - ratio.GetDenominator();
    ratio.Set(numer, ratio.GetDenominator());
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    int numer = 1;
    int denom = 1;
    is >> numer;
    if (is.peek() == '/') {
        is.ignore(1);
        is >> denom;
    }
    ratio.Set(numer, denom);
    return is;
}

Rational operator+(const Rational& ratio) {
    int numer = ratio.GetNumerator();
    int denom = ratio.GetDenominator();
    return Rational(numer, denom);
}

Rational operator-(const Rational& ratio) {
    int numer = ratio.GetNumerator();
    int denom = ratio.GetDenominator();
    return Rational(-numer, denom);
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs = lhs / rhs;
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numer = lhs.GetNumerator() * denom / lhs.GetDenominator() + rhs.GetNumerator() * denom / rhs.GetDenominator();
    return Rational(numer, denom);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numer = lhs.GetNumerator() * denom / lhs.GetDenominator() - rhs.GetNumerator() * denom / rhs.GetDenominator();
    return Rational(numer, denom);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int numer = lhs.GetNumerator() * rhs.GetNumerator();
    int denom = lhs.GetDenominator() * rhs.GetDenominator();
    return Rational(numer, denom);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int numer = lhs.GetNumerator() * rhs.GetDenominator();
    int denom = lhs.GetDenominator() * rhs.GetNumerator();
    return Rational(numer, denom);
}

Rational operator++(Rational& ratio, int) {
    int old_numer = ratio.GetNumerator();
    int old_denom = ratio.GetDenominator();
    ratio += 1;
    return Rational(old_numer, old_denom);
}

Rational operator--(Rational& ratio, int) {
    int old_numer = ratio.GetNumerator();
    int old_denom = ratio.GetDenominator();
    ratio -= 1;
    return Rational(old_numer, old_denom);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    int denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numer1 = lhs.GetNumerator() * denom / lhs.GetDenominator();
    int numer2 = rhs.GetNumerator() * denom / rhs.GetDenominator();
    return numer1 < numer2;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    int denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numer1 = lhs.GetNumerator() * denom / lhs.GetDenominator();
    int numer2 = rhs.GetNumerator() * denom / rhs.GetDenominator();
    return numer1 > numer2;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    int denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numer1 = lhs.GetNumerator() * denom / lhs.GetDenominator();
    int numer2 = rhs.GetNumerator() * denom / rhs.GetDenominator();
    return numer1 == numer2;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        return os << ratio.GetNumerator();
    }
    return os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
}
