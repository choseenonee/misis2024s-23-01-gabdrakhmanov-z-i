#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <queuelstt/queuelstt.hpp>
#include <queuearrt/queuearrt.hpp>
#include <stackarrt/stackarrt.hpp>
#include <stacklstt/stacklstt.hpp>

static const int max_data_size = 1050000;

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
std::vector<T> GetData(int data_len) {
    std::vector<T> data;

    T single_data = T{0};
    for (int i = 0; i < data_len; i++) {
        data.push_back(single_data);
        single_data += 1;
    }

    return data;
}
template<>
std::vector<std::string> GetData(int data_len) {
    std::vector<std::string> data{};
    std::string single_data = "a";

    for (int i = 0; i < data_len; i++) {
        data.push_back(single_data);
        single_data += char(98+i);
    }

    return data;
}

template<class Atd, class T>
void calculatePushAndClearTime(Atd& atd, std::vector<T>& data, int max_size, std::ofstream& file) {
    file << GetTypeName(atd) << std::endl;
    for (int data_size = 1; data_size <= max_size; data_size*=2) {
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < data_size; i++) {
            atd.Push(data[i]);
        }

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        file << "Pushing: " << data_size << " elements, time taken: " << duration.count() << " microseconds" << std::endl;

        start = std::chrono::steady_clock::now();
        atd.Clear();
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        file << "Clearing: " << data_size << " elements, time taken: " << duration.count() << " microseconds" << std::endl;
    }
}

int main() {
    std::ofstream timerOutputFile;
    timerOutputFile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.app/timer_output.txt");

    std::vector<int> data = GetData<int>(max_data_size);

    QueueLstT<int> rhs = QueueLstT<int>();
    calculatePushAndClearTime(rhs, data, max_data_size, timerOutputFile);

    QueueArrT<int> lhs = QueueArrT<int>();
    calculatePushAndClearTime(lhs, data, max_data_size, timerOutputFile);

    timerOutputFile.close();
}