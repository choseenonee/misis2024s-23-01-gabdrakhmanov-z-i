#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <stackarrt/stackarrt.hpp>

#include <string>
#include <vector>
#include <limits>

#define TESTED_TYPES int, double, std::string

static const int little_data_len = 5;

template<class T>
std::vector<T> GetData() {
    std::vector<T> data;

    T single_data = T{0};
    for (int i = 0; i < little_data_len; i++) {
        data.push_back(single_data);
        single_data += 1;
    }

    return data;
}
template<>
std::vector<std::string> GetData() {
    std::vector<std::string> data{};
    std::string single_data = "a";

    for (int i = 0; i < little_data_len; i++) {
        data.push_back(single_data);
        single_data += char(98+i);
    }

    return data;
}

template<class T>
bool Compare(T& lhs, T& rhs) {
    return lhs == rhs;
}
template<>
bool Compare(double& lhs, double& rhs) {
    return abs(lhs - rhs) <= 2 * std::numeric_limits<double>::epsilon();
}

TEST_CASE_TEMPLATE("push, check, pop, check", T, TESTED_TYPES) {
    std::vector<T> data = GetData<T>();

    StackArrT<T> stack;

    CHECK(stack.IsEmpty());

    for (T &i: data) {
        stack.Push(i);
//        auto c = stack.Top();
//        auto d = c;
    }

    CHECK_FALSE(stack.IsEmpty());

    for (int i = data.size()-1; i >= 0; i--) {
        auto a = stack.Top();
        auto b = data[i];
        CHECK(Compare(b, a));
        CHECK_NOTHROW(stack.Pop());
    }
}