#include <vector>
#include <string>
#include <iostream>

#include <queuelstt/queuelstt.hpp>
#include <queuearrt/queuearrt.hpp>
#include <stackarrt/stackarrt.hpp>
#include <stacklstt/stacklstt.hpp>

#define TESTED_TYPES int, double, std::string

static const int data_len = 10000000;

template<class T>
std::string GetTypeName(T& rhs) {
    return "undefined";
}
template<>
std::string GetTypeName(QueueLstT<int>& rhs) {
    return "QueueLst int";
}
template<>
std::string GetTypeName(QueueLstT<double>& rhs) {
    return "QueueLst double";
}
template<>
std::string GetTypeName(QueueLstT<std::string>& rhs) {
    return "QueueLst string";
}
template<>
std::string GetTypeName(QueueArrT<int>& rhs) {
    return "QueueArr int";
}
template<>
std::string GetTypeName(QueueArrT<double>& rhs) {
    return "QueueArr double";
}
template<>
std::string GetTypeName(QueueArrT<std::string>& rhs) {
    return "QueueArr string";
}

template<class T>
std::vector<T> GetData() {
    std::vector<T> data;

    T single_data = T{0};
    for (int i = 0; i < data_len; i++) {
        data.push_back(single_data);
        single_data += 1;
    }

    return data;
}
template<>
std::vector<std::string> GetData() {
    std::vector<std::string> data{};
    std::string single_data = "a";

    for (int i = 0; i < data_len; i++) {
        data.push_back(single_data);
        single_data += char(98+i);
    }

    return data;
}

template<class Atd, class T>
void calculatePushAndClearTime(Atd& queueLst, std::vector<T>& data) {
    auto start = std::chrono::steady_clock::now();

    for (auto& i : data) {
        queueLst.Push(i);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << GetTypeName(queueLst) << " pushing: " << data_len << " elements, time taken: "
    << duration.count() << " microseconds" << std::endl;

    start = std::chrono::steady_clock::now();
    queueLst.Clear();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << GetTypeName(queueLst) << " clearing: " << data_len << " elements, time taken: "
    << duration.count() << " microseconds" << std::endl;
}

int main() {
    std::vector<double> data2 = GetData<double>();

    QueueLstT<double> rhs2 = QueueLstT<double>();
    calculatePushAndClearTime(rhs2, data2);

    QueueArrT<double> lhs2 = QueueArrT<double>();
    calculatePushAndClearTime(lhs2, data2);

    std::vector<int> data = GetData<int>();

    QueueLstT<int> rhs = QueueLstT<int>();
    calculatePushAndClearTime(rhs, data);

    QueueArrT<int> lhs = QueueArrT<int>();
    calculatePushAndClearTime(lhs, data);
}