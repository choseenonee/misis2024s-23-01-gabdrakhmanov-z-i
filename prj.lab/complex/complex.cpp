#include "complex.hpp"


Complex::Complex(const double real)
        : Complex(real, 0.0)
{
}

Complex::Complex(Complex&& rhs) noexcept
        : re(rhs.re), im(rhs.im)
{
}

Complex& Complex::operator=(Complex&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(re, rhs.re);
        std::swap(im, rhs.im);
    }

    return *this;
}

Complex::Complex(const double real, const double imaginary)
        : re(real)
        , im(imaginary)
{
}

Complex Complex::operator-() const noexcept {
    return Complex{-re, -im};
}

bool Complex::operator==(const Complex& rhs) const noexcept {
    return (std::abs(re - rhs.re) < 2*std::numeric_limits<double>::epsilon()) && (std::abs(im - rhs.im) < 2*std::numeric_limits<double>::epsilon());
}

bool Complex::operator!=(const Complex& rhs) const noexcept {
    return !operator==(rhs);
}

Complex& Complex::operator+=(const Complex& rhs) noexcept
{
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex& Complex::operator+=(const double rhs) noexcept {
    return operator+=(Complex(rhs));
}

Complex& Complex::operator-=(const Complex& rhs) noexcept {
    re -= rhs.re;
    im -= rhs.im;
    return *this;
}

Complex& Complex::operator-=(const double rhs) noexcept {
    return operator-=(Complex(rhs));
}

Complex& Complex::operator*=(const double rhs) noexcept
{
    re *= rhs;
    im *= rhs;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs) noexcept {
    double re_c = re;
    double im_c = im;
    re = re*rhs.re - im*rhs.im;
    im = re_c*rhs.im + im_c*rhs.re;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs) {
    if ((rhs.re == 0) && (rhs.im == 0)) {
        throw std::invalid_argument("division by zero");
    }
    double del = rhs.re*rhs.re + rhs.im*rhs.im;
    double re_c = re;
    double im_c = im;
    re = (re*rhs.re + im*rhs.im) / del;
    im = (rhs.re*im_c - re_c*rhs.im) / del;
    return *this;
}

Complex& Complex::operator/=(const double rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("division by zero");
    }
    re = re/rhs;
    im = im/rhs;
    return *this;
}

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    Complex sum = Complex(lhs);
    sum += rhs;
    return sum;
}

Complex operator+(const Complex& lhs, const double rhs) noexcept {
    Complex sum = Complex(lhs);
    sum += rhs;
    return sum;
}

Complex operator+(const double lhs, const Complex& rhs) noexcept {
    Complex sum = Complex(lhs);
    sum += rhs;
    return sum;
}

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    Complex dif = Complex(lhs);
    dif -= rhs;
    return dif;
}

Complex operator-(const Complex& lhs, const double rhs) noexcept {
    Complex dif = Complex(lhs);
    dif -= rhs;
    return dif;
}

Complex operator-(const double lhs, const Complex& rhs) noexcept {
    Complex dif = Complex(lhs);
    dif -= rhs;
    return dif;
}

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    Complex prod = Complex(lhs);
    prod *= rhs;
    return prod;
}

Complex operator*(const Complex& lhs, const double rhs) noexcept {
    Complex prod = Complex(lhs);
    prod *= rhs;
    return prod;
}

Complex operator*(const double lhs, const Complex& rhs) noexcept {
    Complex prod = Complex(lhs);
    prod *= rhs;
    return prod;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    if (rhs.re == 0 && rhs.im == 0) {
        throw std::invalid_argument("dividing by zero");
    }
    Complex div = Complex(lhs);
    div /= rhs;
    return div;
}

Complex operator/(const Complex& lhs, const double rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("dividing by zero");
    }
    Complex div = Complex(lhs);
    div /= rhs;
    return div;
}

Complex operator/(const double lhs, const Complex& rhs) {
    if (rhs.re == 0 & rhs.im == 0) {
        throw std::invalid_argument("dividing by zero");
    }
    Complex div = Complex(lhs);
    div /= rhs;
    return div;
}



std::ostream& Complex::WriteTo(std::ostream& ostrm) const noexcept
{
    ostrm << leftBrace << re << separator << im << rightBrace;
    return ostrm;
}

std::istream& Complex::ReadFrom(std::istream& istrm) noexcept
{
    char leftBrace(0);
    double real(0.0);
    char comma(0);
    double imaginary(0.0);
    char rightBrace(0);
    istrm >> leftBrace >> real >> comma >> imaginary >> rightBrace;
    if (istrm.good()) {
        if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma) && (Complex::rightBrace == rightBrace)) {
            re = real;
            im = imaginary;
        } else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}