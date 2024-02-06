#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <limits>

struct Complex {
    Complex() = default;
    ~Complex() = default;

    explicit Complex(const double real);
    Complex(const Complex&) = default;

    Complex(const double real, const double imaginary);

    Complex& operator=(const Complex&) = default;

    Complex operator-() const noexcept;

    bool operator==(const Complex& rhs) const noexcept;
    bool operator!=(const Complex& rhs) const noexcept;



    Complex& operator+=(const Complex& rhs) noexcept;
    Complex& operator+=(const double rhs) noexcept;
    Complex& operator-=(const Complex& rhs) noexcept;
    Complex& operator-=(const double rhs) noexcept;
    Complex& operator*=(const Complex& rhs) noexcept;
    Complex& operator*=(const double rhs) noexcept;
    Complex& operator/=(const Complex& rhs);
    Complex& operator/=(const double rhs);

//    Complex operator+(const Complex& rhs) noexcept;
//    Complex operator+(const double rhs) noexcept;
//    Complex operator+(const double lhs) noexcept;

//    Complex operator-(const Complex& rhs) noexcept;
//    Complex operator*(const Complex& rhs) noexcept;
//    Complex operator/(const Complex& rhs);

    std::ostream& WriteTo(std::ostream& ostrm) const noexcept;
    std::istream& ReadFrom(std::istream& istrm) noexcept;

    double re{ 0.0 };
    double im{ 0.0 };

    static const char leftBrace{ '{' };
    static const char separator{ ',' };
    static const char rightBrace{ '}' };
};

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator+(const Complex& lhs, const double rhs) noexcept;
Complex operator+(const double lhs, const Complex& rhs) noexcept;

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator-(const Complex& lhs, const double rhs) noexcept;
Complex operator-(const double lhs, const Complex& rhs) noexcept;

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
Complex operator*(const Complex& lhs, const double rhs) noexcept;
Complex operator*(const double lhs, const Complex& rhs) noexcept;

Complex operator/(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const double rhs);
Complex operator/(const double lhs, const Complex& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs)
{
    return rhs.WriteTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Complex& rhs)
{
    return rhs.ReadFrom(istrm);
}

#endif