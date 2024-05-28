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
std::vector<long long> calculatePushAndClearTime(Atd& atd, std::vector<T>& data) {
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < data.size(); i++) {
        atd.Push(data[i]);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    long long pushTime = duration.count();

    start = std::chrono::steady_clock::now();
    atd.Clear();
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    long long clearTime = duration.count();

    std::vector<long long> timings = {pushTime, clearTime};

    return timings;
}

template<class Atd, class T>
void writeToFilePushAndClearTime(Atd& atd, std::vector<T>& data, int max_size, std::ofstream& file) {
    file << GetTypeName(atd) << std::endl;
    for (int data_size = 1; data_size <= max_size; data_size*=2) {

        std::vector<long long> timings = calculatePushAndClearTime<Atd, T>(atd, data);
        file << "Pushing: " << data_size << " elements, time taken: " << timings[0] << " microseconds" << std::endl;

        file << "Clearing: " << data_size << " elements, time taken: " << timings[1] << " microseconds" << std::endl;
    }
}

void openFileAndWriteToIt() {
    std::ofstream timerOutputFile;
    timerOutputFile.open("/Users/thechosenone/CLionProjects/https:/github.com/choseenonee/123/misis2024s-23-01-gabdrakhmanov-z-i/prj.app/timer_output.txt");

    std::vector<int> data = GetData<int>(max_data_size);

    QueueLstT<int> rhs = QueueLstT<int>();
    writeToFilePushAndClearTime(rhs, data, max_data_size, timerOutputFile);

    QueueArrT<int> lhs = QueueArrT<int>();
    writeToFilePushAndClearTime(lhs, data, max_data_size, timerOutputFile);

    timerOutputFile.close();
}

int main() {
    auto data = GetData<int>(100);

    int count[data.size()];
    for (int i = 0; i < data.size(); i++) {
        count[i] = i;
    }

    QueueArrT<int> qu = QueueArrT<int>();
    auto timings_vector = calculatePushAndClearTime<QueueArrT<int>, int>(qu, data);

    int timings[timings_vector.size()];
    for (int i = 0; i < timings_vector.size(); i++) {
        timings[i] = timings_vector[i];
    }
}