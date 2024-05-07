#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <queuelst/queuelst.hpp>

static const Complex a(1,1 );
static const Complex b(3, 3);
static const Complex c(2, 3);
static const Complex d(4, 4);

TEST_CASE("copy operator") {
    QueueLst lhs;
    QueueLst rhs;
    // size equals
    lhs.Push(a);
    lhs.Push(b);

    rhs.Push(c);
    rhs.Push(d);

    lhs = rhs;

    CHECK_EQ(lhs.Size(), rhs.Size());

    CHECK_EQ(lhs.Top(), rhs.Top());

    CHECK_NOTHROW(lhs.Pop());
    CHECK_NOTHROW(rhs.Pop());

    CHECK_EQ(lhs.Top(), rhs.Top());

    lhs.Clear();
    rhs.Clear();

    //lhs size < rhs size

    lhs.Push(a);
    lhs.Push(d);

    rhs.Push(a);
    rhs.Push(b);
    rhs.Push(c);
    rhs.Push(d);

    lhs = rhs;

    CHECK_EQ(lhs.Size(), rhs.Size());

    CHECK_EQ(lhs.Top(), rhs.Top());

    CHECK_NOTHROW(lhs.Pop());
    CHECK_NOTHROW(rhs.Pop());

    CHECK_EQ(lhs.Top(), rhs.Top());

    CHECK_NOTHROW(lhs.Pop());
    CHECK_NOTHROW(rhs.Pop());

    CHECK_EQ(lhs.Top(), rhs.Top());

    CHECK_NOTHROW(lhs.Pop());
    CHECK_NOTHROW(rhs.Pop());

    CHECK_EQ(lhs.Top(), rhs.Top());

    lhs.Clear();
    rhs.Clear();

    //lhs size > rhs size

    lhs.Push(a);
    lhs.Push(d);
    lhs.Push(c);
    lhs.Push(b);

    rhs.Push(a);
    rhs.Push(c);

    lhs = rhs;

    CHECK_EQ(lhs.Size(), rhs.Size());

    CHECK_EQ(lhs.Top(), rhs.Top());

    CHECK_NOTHROW(lhs.Pop());
    CHECK_NOTHROW(rhs.Pop());

    CHECK_EQ(lhs.Top(), rhs.Top());

    lhs.Clear();
    rhs.Clear();

    // lhs empty, rhs is not
    rhs.Push(a);
    rhs.Push(b);

    lhs = rhs;

    CHECK_EQ(lhs.Size(), rhs.Size());

    CHECK_EQ(lhs.Top(), rhs.Top());

    CHECK_NOTHROW(lhs.Pop());
    CHECK_NOTHROW(rhs.Pop());

    CHECK_EQ(lhs.Top(), rhs.Top());

    //rhs is empty, rhs is not

    lhs.Clear();
    rhs.Clear();

    lhs.Push(a);
    lhs.Push(b);

    lhs = rhs;

    CHECK_EQ(lhs.Size(), rhs.Size());
    CHECK(lhs.IsEmpty());
}

TEST_CASE("StackList ctor") {
    QueueLst stack;

    CHECK(stack.IsEmpty());

    Complex first_complex(1, 1);

    stack.Push(first_complex);

    stack.Pop();

    CHECK(stack.IsEmpty());

    CHECK_THROWS(stack.Top());

    stack.Push(first_complex);

    CHECK_FALSE(stack.IsEmpty());
    CHECK(stack.Top() == first_complex);

    Complex second_complex(2, 2);

    stack.Push(second_complex);

    CHECK(stack.Top() == first_complex);

    stack.Pop();
}

TEST_CASE("time test") {
    long long diff = 0;

    QueueLst queue1;
    for (int i = 0; i < 10000; i++) {
        queue1.Push(a);
    }
    auto start = std::chrono::steady_clock::now();
    QueueLst stack2(queue1);
    auto end = std::chrono::steady_clock::now();
    CHECK_EQ(stack2.Top(), a);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    QueueLst stack3(std::move(queue1));
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack3.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);

    QueueLst stack4;
    for (int i = 0; i < 10000; i++) {
        stack4.Push(a);
    }
    QueueLst stack5;
    start = std::chrono::steady_clock::now();
    stack5 = stack4;
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack5.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    QueueLst stack6 = std::move(stack4);
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack6.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);
}