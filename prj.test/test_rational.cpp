#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <rational/rational.hpp>

TEST_CASE("rational ctor") {
    Rational r_def;
    CHECK(0 == r_def.num());
    CHECK(1 == r_def.den());

    Rational r_int(3);
    CHECK(3 == r_int.num());
    CHECK(1 == r_int.den());

    CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("rational arithmetic") {
    Rational r_positive(3, 2);
    Rational r_negative(-2, 6);
    Rational sum;
    sum = r_positive + r_negative;

    CHECK(7 == sum.num());
    CHECK(6 == sum.den());

    sum = sum + 5;

    CHECK(37 == sum.num());
    CHECK(6 == sum.den());

    Rational dif;
    dif = r_positive - r_negative;

    CHECK(11 == dif.num());
    CHECK(6 == dif.den());

    dif = dif - 1;

    CHECK(5 == dif.num());
    CHECK(6 == dif.den());

    Rational prod;
    prod = r_negative * r_positive;

    CHECK(-1 == prod.num());
    CHECK(2 == prod.den());

    prod = prod * (-2);

    CHECK(1 == prod.num());
    CHECK(1 == prod.den());

    Rational div;
    div = r_positive/r_negative;

    CHECK(-9 == div.num());
    CHECK(2 == div.den());

    div = div / (-3);

    CHECK(3 == div.num());
    CHECK(2 == div.den());

    Rational r_zero(0, 1);

    CHECK_THROWS(Rational(1, 0));
    CHECK_THROWS(r_negative / r_zero);
}

TEST_CASE("rational IO") {
    std::istringstream istream("2/3");
    Rational reading;

    istream >> reading;
    CHECK_FALSE(istream.fail());
    CHECK(reading.num() == 2);
    CHECK(reading.den() == 3);

    std::istringstream istream2("16/8");
    istream2 >> reading;
    CHECK(reading.num() == 2);
    CHECK(reading.den() == 1);

    std::istringstream istream3("    7/8");
    istream3 >> reading;
    CHECK(reading.num() == 7);
    CHECK(reading.den() == 8);

    std::istringstream istream4("7/ 8");
    istream4 >> reading;
    CHECK(istream4.fail());

    std::istringstream istream5("4/-54");
    istream5 >> reading;
    CHECK(istream5.fail());

    std::ostringstream ostream1;

    ostream1 << Rational(2, 3);
    CHECK(ostream1.str() == "2/3");

    std::ostringstream ostream2;
    ostream2 << Rational(-2, 3);
    CHECK(ostream2.str() == "-2/3");
}