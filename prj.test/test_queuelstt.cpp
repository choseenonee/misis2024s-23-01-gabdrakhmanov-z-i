#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <queuelstt/queuelstt.hpp>

#include <string>
#include <vector>
#include <limits>

#define TESTED_TYPES int, double, std::string

static const int little_data_len = 50000;

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

TEST_CASE_TEMPLATE("push, check, pop, check, queue", T, TESTED_TYPES) {
    std::vector<T> data = GetData<T>();

    QueueLstT<T> queue;

    CHECK(queue.IsEmpty());

    for (T &i: data) {
        queue.Push(i);
    }

    CHECK_FALSE(queue.IsEmpty());

    for (int i = 0; i < data.size(); i++) {
        auto a = queue.Top();
        auto b = data[i];
        CHECK(Compare(b, a));
        CHECK_NOTHROW(queue.Pop());
    }

    CHECK_THROWS(queue.Top());
    CHECK(queue.IsEmpty());
}

TEST_CASE_TEMPLATE("Clear", T, TESTED_TYPES) {
    std::vector<T> data = GetData<T>();

    QueueLstT<T> queue;

    CHECK(queue.IsEmpty());

    for (T &i: data) {
        queue.Push(i);
    }

    CHECK_FALSE(queue.IsEmpty());

    queue.Clear();

    CHECK(queue.IsEmpty());
    CHECK_THROWS(queue.Top());
}


TEST_CASE_TEMPLATE("Copy", T, TESTED_TYPES) {
    std::vector<T> data = GetData<T>();

    QueueLstT<T> lhs;
    QueueLstT<T> rhs;

    for (T &i: data) {
        lhs.Push(i);
    }

    for (int i = data.size() - 1; i >= 0; i--) {
        rhs.Push(data[i]);
    }

    // равные по длине
    lhs = rhs;

    for (int i = data.size() - 1; i >= 0; i--) {
        CHECK_EQ(lhs.Top(), data[i]);
        CHECK_NOTHROW(lhs.Pop());
    }
    CHECK(lhs.IsEmpty());

    // правый длинее
    lhs = rhs;
    for (int i = data.size() - 1; i >= 0; i--) {
        CHECK_EQ(lhs.Top(), data[i]);
        CHECK_NOTHROW(lhs.Pop());
    }
    CHECK(lhs.IsEmpty());

    rhs.Clear();

    for (int i = data.size() - 1; i > data.size() / 2; i--) {
        rhs.Push(data[i]);
    }

    // левый длинее
    lhs = rhs;

    for (int i = data.size() - 1; i > data.size() / 2; i--) {
        if (lhs.IsEmpty()) {
            break;
        }
        auto a = lhs.Top();
        auto b = data[i];
        CHECK_EQ(a, b);
        CHECK_NOTHROW(lhs.Pop());
    }
    CHECK(lhs.IsEmpty());

    lhs.Clear();

    // левый пустой
    lhs = rhs;

    for (int i = data.size() - 1; i > data.size() / 2; i--) {
        if (lhs.IsEmpty()) {
            break;
        }
        CHECK_EQ(lhs.Top(), data[i]);
        CHECK_NOTHROW(lhs.Pop());
    }
    CHECK(lhs.IsEmpty());

    rhs.Clear();

    lhs = rhs;

    CHECK(lhs.IsEmpty());
}

TEST_CASE_TEMPLATE("copy ctor", T, TESTED_TYPES) {
    std::vector<T> data = GetData<T>();

    QueueLstT<T> lhs;

    for (T &i: data) {
        lhs.Push(i);
    }

    QueueLstT<T> rhs(lhs);

    for (T &i: data) {
        CHECK_EQ(rhs.Top(), i);
        rhs.Pop();
    }

    for (T &i: data) {
        CHECK_EQ(lhs.Top(), i);
        lhs.Pop();
    }
}