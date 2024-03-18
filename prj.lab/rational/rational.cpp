#include "rational.hpp"

Rational::Rational(const int64_t num, const int64_t den) {
    if (den == 0) {
        throw std::invalid_argument("denumerator can't be zero");
    }
    num_ = num;
    den_ = den;
    fix();
}

Rational::Rational(Rational&& rhs) noexcept
        : num_(rhs.num_), den_(rhs.den_)
{
    rhs.num_ = 0;
    rhs.den_ = 1;
}

Rational& Rational::operator=(Rational&& rhs) noexcept {
    if (this != &rhs) {
        std::swap(num_, rhs.num_);
        std::swap(den_, rhs.den_);
    }

    return *this;
}

Rational::Rational(int64_t num) {
    num_ = num;
    fix();
}


int64_t Rational::num() const noexcept {
    return num_;
}

int64_t Rational::den() const noexcept {
    return den_;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const
{
    ostrm << num_ << slash_ << den_;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm)
{
    int64_t num = 0;
    char delimiter = 0;
    int64_t den = 0;
    int64_t check_digits = 0;
    istrm >> num;
    istrm.get(delimiter);
//    смотрим, но не вытаскиваем следующий элемент из потока
    check_digits = istrm.peek();
//    проверяем, если это НЕ число, то файлбит
    istrm >> den;
    if (check_digits > '9' || check_digits < '0') {
        istrm.setstate(std::ios_base::failbit);
    } else {
        if (istrm.good() || istrm.eof()) {
            if (den > 0 && delimiter == slash_) {
                num_ = num;
                den_ = den;
                fix();
            }
            else {
                istrm.setstate(std::ios_base::failbit);
            }
        }
    }
    return istrm;
}

bool Rational::operator==(const Rational& rhs) const noexcept {
    return (num_ == rhs.num_) && (den_ == rhs.den_);
};

bool Rational::operator!=(const Rational& rhs) const noexcept {
    return !operator==(rhs);
};

bool Rational::operator>(const Rational& rhs) const noexcept {
    int64_t lhs_v = num_ * rhs.den_;
    int64_t rhs_v = den_ * rhs.num_;
    return lhs_v > rhs_v;
};

bool Rational::operator<(const Rational& rhs) const noexcept {
    int64_t lhs_v = num_ * rhs.den_;
    int64_t rhs_v = den_ * rhs.num_;
    return lhs_v < rhs_v;
};

bool Rational::operator>=(const Rational& rhs) const noexcept {
    int64_t lhs_v = num_ * rhs.den_;
    int64_t rhs_v = den_ * rhs.num_;
    return lhs_v >= rhs_v;
};

bool Rational::operator<=(const Rational& rhs) const noexcept {
    int64_t lhs_v = num_ * rhs.den_;
    int64_t rhs_v = den_ * rhs.num_;
    return lhs_v <= rhs_v;
};

Rational& Rational::operator+=(const Rational& rhs) noexcept {
    if (den_ != rhs.den_) {
        num_ = num_*rhs.den_ + rhs.num_*den_;
        den_ = den_ * rhs.den_;
    }
    else {
        num_ += rhs.num_;
    }
    fix();
    return *this;
};

Rational& Rational::operator+=(const int64_t rhs) noexcept {
    num_ += rhs * den_;
    fix();
    return *this;
}


Rational& Rational::operator-=(const Rational& rhs) noexcept {
    if (den_ != rhs.den_) {
        num_ = num_*rhs.den_ - rhs.num_*den_;
        den_ = den_ * rhs.den_;
    }
    else {
        num_ -= rhs.num_;
    }
    fix();
    return *this;
};

Rational& Rational::operator-=(const int64_t rhs) noexcept {
    num_ -= rhs * den_;
    fix();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    num_ *= rhs.num_;
    den_ *= rhs.den_;
    fix();
    return *this;
};

Rational& Rational::operator*=(const int64_t rhs) noexcept {
    num_ *= rhs;
    fix();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num_ == 0) {
        throw std::invalid_argument("dividing by zero");
    }
    num_ *= rhs.den_;
    den_ *= rhs.num_;
    fix();
    return *this;
};

Rational& Rational::operator/=(const int64_t rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("dividing by zero");
    }
    den_ *= rhs;
    fix();
    return *this;
}

Rational Rational::operator-() const noexcept {
    Rational neg(*this);
    neg = neg*(-1);

    return neg;
}

Rational operator+(const Rational& lhs, const Rational& rhs) noexcept {
    Rational sum(lhs);
    sum += rhs;
    return sum;
};

Rational operator-(const Rational& lhs, const Rational& rhs) noexcept {
    Rational dif(lhs);
    dif -= rhs;
    return dif;
};

Rational operator*(const Rational& lhs, const Rational& rhs) noexcept {
    Rational mult(lhs);
    mult *= rhs;
    return mult;
};

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational div(lhs);
    div /= rhs;
    return div;
};

Rational operator+(const Rational& lhs, const int64_t rhs) noexcept {
    Rational sum(lhs);
    sum+=rhs;
    return sum;
}

Rational operator-(const Rational& lhs, const int64_t rhs) noexcept {
    Rational dif(lhs);
    dif-=rhs;
    return dif;
}

Rational operator*(const Rational& lhs, const int64_t rhs) noexcept {
    Rational mult(lhs);
    mult*=rhs;
    return mult;
}

Rational operator/(const Rational& lhs, const int64_t rhs) {
    Rational div(lhs);
    div/=rhs;
    return div;
}

Rational operator+(const int64_t lhs, const Rational& rhs) noexcept {
    Rational sum(rhs);
    sum+=lhs;
    return sum;
}

Rational operator-(const int64_t lhs, const Rational& rhs) noexcept {
    Rational sum(rhs);
    sum-=lhs;
    return sum;
}

Rational operator*(const int64_t lhs, const Rational& rhs) noexcept {
    Rational sum(rhs);
    sum*=lhs;
    return sum;
}

Rational operator/(const int64_t lhs, const Rational& rhs) {
    Rational sum(rhs);
    sum/=lhs;
    return sum;
}