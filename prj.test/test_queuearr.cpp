#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <queuearr/queuearr.hpp>

TEST_CASE("queueList ctor") {
    QueueArr queue;

    CHECK(queue.IsEmpty());

    Complex first_complex(1, 1);

    queue.Push(first_complex);

    CHECK_FALSE(queue.IsEmpty());
    CHECK(queue.Top() == first_complex);

    Complex second_complex(2, 2);
    Complex third_complex(3, 3);

    queue.Push(second_complex);

    queue.Push(third_complex);

    queue.Pop();

    CHECK(queue.Top() == second_complex);

    Complex fourth_complex(4, 4);

    queue.Push(fourth_complex);

    CHECK(queue.Top() == second_complex);

    Complex fifth_complex(5, 5);

    queue.Push(fifth_complex);

    CHECK(queue.Top() == second_complex);

    queue.Pop();

    CHECK_EQ(queue.Top(), third_complex);

    queue.Pop();

    CHECK_EQ(queue.Top(), fourth_complex);

    queue.Pop();

    CHECK_EQ(queue.Top(), fifth_complex);

    queue.Pop();

    CHECK(queue.IsEmpty());
}

//
// Created by Alex on 27.02.2024.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <queuearr/queuearr.hpp>

TEST_CASE("queuearr ctor") {
    QueueArr qa;
    CHECK(qa.Size() == 0);
    qa.Push(Complex(5));
    CHECK(qa.Size() == 1);
    qa.Push(Complex(4));
    CHECK(qa.Size() == 2);
    CHECK(qa.Top() == Complex(5));
    qa.Pop();
    CHECK(qa.Top() == Complex(4));
    qa.Pop();
    CHECK_THROWS(qa.Top());
    qa.Pop();
    CHECK(qa.IsEmpty());
    CHECK(qa.Size() == 0);
}

TEST_CASE("queuearr overflow") {
    QueueArr qa;
    qa.Push(Complex(1));
    qa.Push(Complex(2));
    qa.Push(Complex(3));
    qa.Push(Complex(4));
    qa.Push(Complex(5));
    qa.Push(Complex(6));
    CHECK(qa.Size() == 6);
    CHECK(qa.Top() == Complex(1));
    qa.Pop();
    CHECK(qa.Top() == Complex(2));
    qa.Pop();
    CHECK(qa.Top() == Complex(3));
    qa.Pop();
    CHECK(qa.Top() == Complex(4));
    qa.Pop();
    CHECK(qa.Top() == Complex(5));
    qa.Pop();
    CHECK(qa.Top() == Complex(6));
    qa.Pop();
    CHECK_THROWS(qa.Top());
}

TEST_CASE("queuearr assignment") {
    QueueArr qa1;
    qa1.Push(Complex(4));
    qa1.Push(Complex(3));
    qa1.Push(Complex(2));
    qa1.Push(Complex(1));
    QueueArr qa2(qa1);
    QueueArr qa3;
    qa3 = qa1;
    qa3.Pop();
    CHECK(qa1.Size() == 4);
    CHECK(qa2.Size() == 4);
    CHECK(qa3.Size() == 3);

    qa1.Push(Complex(5));
    qa1.Push(Complex(6));
    qa1.Push(Complex(7));
    qa2 = qa1;
    qa3 = qa2;
    CHECK(qa1.Size() == 7);
    CHECK(qa2.Size() == 7);
    CHECK(qa3.Size() == 7);

    CHECK(qa1.Top() == Complex(4));
    CHECK(qa2.Top() == Complex(4));
    CHECK(qa3.Top() == Complex(4));

    qa1.Pop();
    qa2.Pop();
    qa3.Pop();

    CHECK(qa1.Top() == Complex(3));
    CHECK(qa2.Top() == Complex(3));
    CHECK(qa3.Top() == Complex(3));

    for(int i = 0; i < 10; i++){
        qa1.Pop();
    }
    CHECK(qa1.IsEmpty() == true);
}

Complex a(1, 2);
Complex b(1, 3);

TEST_CASE("Initialization") {
    QueueArr queue;
    CHECK_THROWS(queue.Top());
    CHECK(queue.IsEmpty());
    CHECK_NOTHROW(queue.Pop());
    queue.Push(a);
    CHECK_NOTHROW(queue.Top());
    queue.Push(b);
}

TEST_CASE("Push, Pop, Top, Clear") {
    QueueArr queue;
    CHECK_THROWS(queue.Top());
    CHECK(queue.IsEmpty());
    CHECK_NOTHROW(queue.Pop());

    queue.Push(a);
    CHECK_NOTHROW(queue.Top());
    CHECK_EQ(queue.Top(), a);

    queue.Push(b);
    CHECK_EQ(queue.Top(), a);
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue.Top(), b);
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue.IsEmpty(), true);

    queue.Push(a);
    CHECK_NOTHROW(queue.Top());
    queue.Clear();
    CHECK_EQ(queue.IsEmpty(), true);
}

TEST_CASE("Copy ctor") {
    QueueArr queue;
    queue.Push(a);
    queue.Push(b);

    QueueArr queue2(queue);
    CHECK_EQ(queue2.Top(), queue.Top());
    CHECK_EQ(queue2.Top(), a);
    CHECK_NOTHROW(queue2.Pop());
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue2.Top(), queue.Top());
    CHECK_EQ(queue2.Top(), b);
    CHECK_NOTHROW(queue2.Pop());
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue2.IsEmpty(), queue.IsEmpty());
    CHECK_EQ(queue2.IsEmpty(), true);
}

TEST_CASE("Copy operator") {
    QueueArr queue3;
    CHECK_THROWS(queue3.Top());
    CHECK(queue3.IsEmpty());
    CHECK_NOTHROW(queue3.Pop());
    queue3.Push(a);
    CHECK_NOTHROW(queue3.Top());
    queue3.Push(b);

    QueueArr queue4 = queue3;
    CHECK_EQ(queue4.Top(), queue3.Top());
    CHECK_EQ(queue4.Top(), a);
    CHECK_NOTHROW(queue4.Pop());
    CHECK_NOTHROW(queue3.Pop());
    CHECK_EQ(queue4.Top(), queue3.Top());
    CHECK_EQ(queue4.Top(), b);
    CHECK_NOTHROW(queue4.Pop());
    CHECK_NOTHROW(queue3.Pop());
    CHECK_EQ(queue4.IsEmpty(), queue3.IsEmpty());
    CHECK_EQ(queue4.IsEmpty(), true);
}

TEST_CASE("Cycle") {
    QueueArr queue;
    for(int i_cycle = 0; i_cycle < 100; i_cycle++) {
        queue.Push(a);
        queue.Push(b);
        CHECK_EQ(queue.Top(), a);
        queue.Pop();
        CHECK_EQ(queue.Top(), b);
        queue.Pop();
        CHECK_EQ(queue.IsEmpty(), true);
    }

    queue.Push(a);
    queue.Push(b);

    QueueArr queue2(queue);
    CHECK_EQ(queue2.Top(), queue.Top());
    CHECK_EQ(queue2.Top(), a);
    CHECK_NOTHROW(queue2.Pop());
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue2.Top(), queue.Top());
    CHECK_EQ(queue2.Top(), b);
    CHECK_NOTHROW(queue2.Pop());
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue2.IsEmpty(), queue.IsEmpty());
    CHECK_EQ(queue2.IsEmpty(), true);

    queue.Push(a);
    queue.Push(b);

    QueueArr queue3 = queue;
    CHECK_EQ(queue3.Top(), queue.Top());
    CHECK_EQ(queue3.Top(), a);
    CHECK_NOTHROW(queue3.Pop());
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue3.Top(), queue.Top());
    CHECK_EQ(queue3.Top(), b);
    CHECK_NOTHROW(queue3.Pop());
    CHECK_NOTHROW(queue.Pop());
    CHECK_EQ(queue3.IsEmpty(), queue.IsEmpty());
    CHECK_EQ(queue3.IsEmpty(), true);
}

static const Complex c(2, 3);

TEST_CASE("time test") {
    long long diff = 0;

    QueueArr queue1;
    for (int i = 0; i < 10000; i++) {
        queue1.Push(a);
    }
    auto start = std::chrono::steady_clock::now();
    QueueArr stack2(queue1);
    auto end = std::chrono::steady_clock::now();
    CHECK_EQ(stack2.Top(), a);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    QueueArr stack3(std::move(queue1));
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack3.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);

    QueueArr stack4;
    for (int i = 0; i < 10000; i++) {
        stack4.Push(a);
    }
    QueueArr stack5;
    start = std::chrono::steady_clock::now();
    stack5 = stack4;
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack5.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    QueueArr stack6 = std::move(stack4);
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack6.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);
}