#include <iostream>
#include <complex/complex.hpp>

void TestDivOp() {
    Complex rhs(-2, 1);
    Complex lhs(1, -1);
    Complex ans;

    Complex correct(-1.5, -0.5);

    ans =  rhs / lhs;

    if (ans == correct) {
        std::cout << lhs << " / " << rhs << " = " << correct << " " << "SUCCES" << std::endl;
        return;
    }

    std::cout << lhs << " / " << rhs << " = " << ans << " != " << correct << " " << "FAILED" << std::endl;
}

void TestSumOp() {
    Complex rhs(-2, 1);
    Complex lhs(1, -1);
    Complex ans;

    Complex correct(-1, 0);

    ans = rhs + lhs;

    if (ans == correct) {
        std::cout << lhs << " + " << rhs << " = " << correct << " " << "SUCCES" << std::endl;
        return;
    }

    std::cout << lhs << " + " << rhs << " = " << ans << " != " << correct << " " << "FAILED" << std::endl;
}

void TestSubOp() {
    Complex rhs(-2, 1);
    Complex lhs(1, -1);
    Complex ans;

    Complex correct(-3, 2);

    ans = rhs - lhs;

    if (ans == correct) {
        std::cout << lhs << " - " << rhs << " = " << correct << " " << "SUCCES" << std::endl;
        return;
    }

    std::cout << lhs << " + " << rhs << " = " << ans << " != " << correct << " " << "FAILED" << std::endl;
}

void TestMulOp() {
    Complex rhs(-2, 1);
    Complex lhs(1, -1);
    Complex ans;

    Complex correct(-1, 3);

    ans = rhs * lhs;

    if (ans == correct) {
        std::cout << lhs << " * " << rhs << " = " << correct << " " << "SUCCES" << std::endl;
        return;
    }

    std::cout << lhs << " * " << rhs << " = " << ans << " != " << correct << " " << "FAILED" << std::endl;
}

void TestZeroDivision() {
    Complex rhs(-2, 1);
    Complex lhs(0, 0);

    try {
        rhs /= lhs;
    }
    catch (std::invalid_argument& exception) {
        std::cout << "DIVIDING BY ZERO: " << rhs << " / " << lhs << " CATCHED: " << exception.what() << std::endl;
    }
}

int main()
{
    TestDivOp();
    TestSumOp();
    TestSubOp();
    TestMulOp();
    TestZeroDivision();

    return 0;
}