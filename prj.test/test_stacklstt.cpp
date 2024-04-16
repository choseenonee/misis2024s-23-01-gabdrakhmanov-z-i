#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <complex/complex.hpp>
#include <stacklstt/stacklstt.hpp>

#include <string>
#include <sstream>

template<class T>
T getFirst() {
    return T{1};
}
template<>
std::string getFirst() {
    std::string a = "hello";
    return a;
}

template<class T>
T getSecond() {
    return T{2};
}
template<>
std::string getSecond() {
    std::string a = "world";
    return a;
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex, std::string) {
    StackLstT<T> stack;

    CHECK(stack.IsEmpty());

    T first_complex = getFirst<T>();

    stack.Push(first_complex);

    CHECK_FALSE(stack.IsEmpty());
    CHECK(stack.Top() == first_complex);

    T second_complex = getSecond<T>();

    stack.Push(second_complex);

    stack.Pop();

    CHECK(stack.Top() == first_complex);
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> stack;

    T first_complex{1};

    stack.Push(first_complex);

    T second_complex{2};

    stack.Push(second_complex);

    stack.Pop();
    stack.Pop();

    CHECK(stack.IsEmpty());
    CHECK_THROWS(stack.Top());
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> my_stack;
    CHECK_THROWS(my_stack.Top());
    CHECK(my_stack.IsEmpty());

    T first_complex{1};
    T second_complex{2};

    my_stack.Push(first_complex);
    my_stack.Push(second_complex);

    CHECK_EQ(my_stack.Top(), second_complex);
    my_stack.Pop();
    CHECK_EQ(my_stack.Top(), first_complex);

    T third_complex{3};

    StackLstT<T> my_stack2;
    my_stack2.Push(third_complex);
    my_stack = my_stack2;
    CHECK_EQ(my_stack.Top(), third_complex);

    StackLstT<T> a(my_stack);
    CHECK_EQ(a.Top(), third_complex);

    T fourth_complex{4};

    T fifth_complex{5};

    my_stack.Push(fourth_complex);
    CHECK_EQ(my_stack.Top(), fourth_complex);
    my_stack.Push(fifth_complex);
    CHECK_EQ(my_stack.Top(), fifth_complex);
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> my_stack;
    CHECK_THROWS(my_stack.Top());
    CHECK(my_stack.IsEmpty());

    T first_complex{1};
    T second_complex{2};

    my_stack.Push(first_complex);
    my_stack.Push(second_complex);

    CHECK_EQ(my_stack.Top(), second_complex);
    my_stack.Pop();
    CHECK_EQ(my_stack.Top(), first_complex);

    T third_complex{3};

    StackLstT<T> my_stack2;
    my_stack2.Push(third_complex);
    my_stack = my_stack2;
    CHECK_EQ(my_stack.Top(), third_complex);

    StackLstT<T> a(my_stack);
    CHECK_EQ(a.Top(), third_complex);

    T fourth_complex{4};

    T fifth_complex{5};

    my_stack.Push(fourth_complex);
    CHECK_EQ(my_stack.Top(), fourth_complex);
    my_stack.Push(fifth_complex);
    CHECK_EQ(my_stack.Top(), fifth_complex);

    StackLstT<T> eq1;
    StackLstT<T> eq2;
    eq1.Push(first_complex);
    eq1.Push(second_complex);
    eq1.Push(third_complex);
    eq2 = eq1;
    CHECK_EQ(eq1.Top(), eq2.Top());
    eq1.Pop();
    eq2.Pop();
    CHECK_EQ(eq1.Top(), eq2.Top());
    eq1.Pop();
    eq2.Pop();
    CHECK_EQ(eq1.Top(), eq2.Top());
    eq1.Pop();
    eq2.Pop();
    CHECK(eq1.IsEmpty());
    CHECK(eq2.IsEmpty());
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> stackFirst;
    StackLstT<T> stackSecond;

    // first not empty, second is empty
    T complexOne{1};
    T complexTwo{2};
    T complexThree{3};
    T complexFour{4};

    stackFirst.Push(complexOne);

    stackFirst = stackSecond;
    CHECK(stackFirst.IsEmpty());

    stackFirst.Clear();
    stackSecond.Clear();
    // both not empty, first > second

    stackFirst.Push(complexOne);
    stackFirst.Push(complexTwo);
    stackFirst.Push(complexFour);

    stackSecond.Push(complexThree);

    stackFirst = stackSecond;
    CHECK_EQ(stackFirst.Top(), stackSecond.Top());

    stackFirst.Clear();
    stackSecond.Clear();
    // both not empty, first < second
    stackSecond.Push(complexOne);
    stackSecond.Push(complexTwo);

    stackFirst.Push(complexThree);

    stackFirst = stackSecond;
    CHECK_EQ(stackFirst.Top(), stackSecond.Top());

    stackFirst.Clear();
    stackSecond.Clear();
    // first empty, second is not
    stackSecond.Push(complexOne);
    stackSecond.Push(complexTwo);

    stackFirst = stackSecond;
    CHECK_EQ(stackFirst.Top(), stackSecond.Top());
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    const T a{1};
    const T b{2};
    const T c{3};
    long long diff = 0;

    StackLstT<T> stack1;
    for (int i = 0; i < 10000; i++) {
        stack1.Push(a);
    }
    auto start = std::chrono::steady_clock::now();
    StackLstT<T> stack2(stack1);
    auto end = std::chrono::steady_clock::now();
    CHECK_EQ(stack2.Top(), a);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    StackLstT<T> stack3(std::move(stack1));
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack3.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);

    StackLstT<T> stack4;
    for (int i = 0; i < 10000; i++) {
        stack4.Push(a);
    }
    StackLstT<T> stack5;
    start = std::chrono::steady_clock::now();
    stack5 = stack4;
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack5.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    StackLstT<T> stack6 = std::move(stack4);
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack6.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);
}


TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> stack;

    CHECK(stack.IsEmpty());

    stack.Push(T{1});

    CHECK_FALSE(stack.IsEmpty());
    CHECK(stack.Top() == T{1});

    stack.Push(T{2});

    stack.Pop();

    CHECK(stack.Top() == T{1});
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> stack;

    stack.Push(T{1});

    stack.Push(T{2});

    stack.Pop();
    stack.Pop();

    CHECK(stack.IsEmpty());
    CHECK_THROWS(stack.Top());
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> my_stack;
    CHECK_THROWS(my_stack.Top());
    CHECK(my_stack.IsEmpty());

    my_stack.Push(T{1});
    my_stack.Push(T{2});

    CHECK_EQ(my_stack.Top(), T{2});
    my_stack.Pop();
    CHECK_EQ(my_stack.Top(), T{1});

    StackLstT<T> my_stack2;
    my_stack2.Push(T{3});
    my_stack = my_stack2;
    CHECK_EQ(my_stack.Top(), T{3});

    StackLstT<T> j(my_stack);
    CHECK_EQ(j.Top(), T{3});


    my_stack.Push(T{4});
    CHECK_EQ(my_stack.Top(), T{4});
    my_stack.Push(T{5});
    CHECK_EQ(my_stack.Top(), T{5});
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> my_stack;
    CHECK_THROWS(my_stack.Top());
    CHECK(my_stack.IsEmpty());

    T first = T{1};
    T second = T{2};
    T third = T{3};
    T fourth = T{4};
    T fifth = T{5};

    my_stack.Push(first);
    my_stack.Push(second);

    CHECK_EQ(my_stack.Top(), second);
    my_stack.Pop();
    CHECK_EQ(my_stack.Top(), first);

    StackLstT<T> my_stack2;
    my_stack2.Push(third);
    my_stack = my_stack2;
    CHECK_EQ(my_stack.Top(), third);

    StackLstT<T> a(my_stack);
    CHECK_EQ(a.Top(), third);


    my_stack.Push(fourth);
    CHECK_EQ(my_stack.Top(), fourth);
    my_stack.Push(fifth);
    CHECK_EQ(my_stack.Top(), fifth);

    StackLstT<T> eq1;
    StackLstT<T> eq2;
    eq1.Push(first);
    eq1.Push(second);
    eq1.Push(third);
    eq2 = eq1;
    CHECK_EQ(eq1.Top(), eq2.Top());
    eq1.Pop();
    eq2.Pop();
    CHECK_EQ(eq1.Top(), eq2.Top());
    eq1.Pop();
    eq2.Pop();
    CHECK_EQ(eq1.Top(), eq2.Top());
    eq1.Pop();
    eq2.Pop();
    CHECK(eq1.IsEmpty());
    CHECK(eq2.IsEmpty());
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    StackLstT<T> stackFirst;
    StackLstT<T> stackSecond;

    T first = T{1};
    T second = T{2};
    T third = T{3};
    T fourth = T{4};
    T fifth = T{5};

    // first not empty, second is empty
    stackFirst.Push(first);

    stackFirst = stackSecond;
    CHECK(stackFirst.IsEmpty());

    stackFirst.Clear();
    stackSecond.Clear();
    // both not empty, first > second

    stackFirst.Push(first);
    stackFirst.Push(second);
    stackFirst.Push(fourth);

    stackSecond.Push(third);

    stackFirst = stackSecond;
    CHECK_EQ(stackFirst.Top(), stackSecond.Top());

    stackFirst.Clear();
    stackSecond.Clear();
    // both not empty, first < second
    stackSecond.Push(first);
    stackSecond.Push(second);

    stackFirst.Push(third);

    stackFirst = stackSecond;
    CHECK_EQ(stackFirst.Top(), stackSecond.Top());

    stackFirst.Clear();
    stackSecond.Clear();
    // first empty, second is not
    stackSecond.Push(first);
    stackSecond.Push(second);

    stackFirst = stackSecond;
    CHECK_EQ(stackFirst.Top(), stackSecond.Top());
}

TEST_CASE_TEMPLATE("signed integers stuff", T, char, short, int, long long int, Complex) {
    long long diff = 0;

    T first = T{1};
    T second = T{2};
    T third = T{3};
    T fourth = T{4};
    T fifth = T{5};

    StackLstT<T> stack1;
    for (int i = 0; i < 10000; i++) {
        stack1.Push(first);
    }
    auto start = std::chrono::steady_clock::now();
    StackLstT<T> stack2(stack1);
    auto end = std::chrono::steady_clock::now();
    CHECK_EQ(stack2.Top(), first);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    StackLstT<T> stack3(std::move(stack1));
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack3.Top(), first);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);

    StackLstT<T> stack4;
    for (int i = 0; i < 10000; i++) {
        stack4.Push(first);
    }
    StackLstT<T> stack5;
    start = std::chrono::steady_clock::now();
    stack5 = stack4;
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack5.Top(), first);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    StackLstT<T> stack6 = std::move(stack4);
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack6.Top(), first);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);
}