#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstdint>
#include <iostream>

class Rational {
public:
    Rational() = default;
    Rational(const int64_t num, const int64_t den);
    explicit Rational(int64_t num);
    Rational(const Rational& rhs) = default;
    Rational(Rational&& rhs) noexcept;
    ~Rational() = default;
    Rational& operator=(const Rational&) = default;
    Rational& operator=(Rational&& rhs) noexcept;

    int64_t num() const noexcept;
    int64_t den() const noexcept;

    bool operator==(const Rational& rhs) const noexcept;
    bool operator!=(const Rational& rhs) const noexcept;
    bool operator>(const Rational& rhs) const noexcept;
    bool operator<(const Rational& rhs) const noexcept;
    bool operator>=(const Rational& rhs) const noexcept;
    bool operator<=(const Rational& rhs) const noexcept;

    Rational& operator+=(const Rational& rhs) noexcept;
    Rational& operator-=(const Rational& rhs) noexcept;
    Rational& operator*=(const Rational& rhs) noexcept;
    Rational& operator/=(const Rational& rhs);

    Rational& operator+=(const int64_t rhs) noexcept;
    Rational& operator-=(const int64_t rhs) noexcept;
    Rational& operator*=(const int64_t rhs) noexcept;
    Rational& operator/=(const int64_t rhs);

    Rational operator-() const noexcept;

    std::ostream& WriteTo(std::ostream& ostrm) const;
    std::istream& ReadFrom(std::istream& istrm);
private:
    int64_t num_ = 0;
    int64_t den_ = 1;
    char slash_ = '/';

//  переносим знак из знаменателя чтобы знаменатель был > 0
//  сокращаем дробь с помощью НОД
    void fix() {
        if (den_ < 0) {
            den_ *= -1;
            num_ *= -1;
        }
        int64_t num = std::abs(num_);
        int64_t den = std::abs(den_);
        int64_t delimiter = 0;
        while ((num != 0) && (den != 0)) {
            if (num > den) {
                num = num % den;
            }
            else {
                den = den % num;
            }
        }
        delimiter = num + den;
        num_ /= delimiter;
        den_ /= delimiter;
    };
};


Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator-(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator*(const Rational& lhs, const int64_t rhs) noexcept;
Rational operator/(const Rational& lhs, const int64_t rhs);

Rational operator+(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator-(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator*(const int64_t lhs, const Rational& rhs) noexcept;
Rational operator/(const int64_t lhs, const Rational& rhs);


inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.WriteTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.ReadFrom(istrm);
}

#endif //RATIONAL_HPP