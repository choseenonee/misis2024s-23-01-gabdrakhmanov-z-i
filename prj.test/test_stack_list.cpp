#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <stacklst/stacklst.hpp>

TEST_CASE("StackList ctor") {
    StackLst stack;

    CHECK(stack.IsEmpty());

    Complex first_complex(1, 1);

    stack.Push(first_complex);

    CHECK_FALSE(stack.IsEmpty());
    CHECK(stack.Top() == first_complex);

    Complex second_complex(2, 2);

    stack.Push(second_complex);

    stack.Pop();

    CHECK(stack.Top() == first_complex);
}

TEST_CASE("StackLst pop exception") {
    StackLst stack;

    Complex first_complex(1, 1);

    stack.Push(first_complex);

    Complex second_complex(2, 2);

    stack.Push(second_complex);

    stack.Pop();
    stack.Pop();

    CHECK(stack.IsEmpty());
    CHECK_THROWS(stack.Top());
}

TEST_CASE("StackLst test") {
    StackLst my_stack;
    CHECK_THROWS(my_stack.Top());
    CHECK(my_stack.IsEmpty());

    Complex first_complex(3, 5);
    Complex second_complex(2, 7);

    my_stack.Push(first_complex);
    my_stack.Push(second_complex);

    CHECK_EQ(my_stack.Top(), second_complex);
    my_stack.Pop();
    CHECK_EQ(my_stack.Top(), first_complex);

    Complex third_complex(1, 1);

    StackLst my_stack2;
    my_stack2.Push(third_complex);
    my_stack = my_stack2;
    CHECK_EQ(my_stack.Top(), third_complex);

    StackLst a(my_stack);
    CHECK_EQ(a.Top(), third_complex);

    Complex fourth_complex(2.3, 7.3);

    Complex fifth_complex(2.003, 0);

    my_stack.Push(fourth_complex);
    CHECK_EQ(my_stack.Top(), fourth_complex);
    my_stack.Push(fifth_complex);
    CHECK_EQ(my_stack.Top(), fifth_complex);
}

TEST_CASE("StackLst test") {
    StackLst my_stack;
    CHECK_THROWS(my_stack.Top());
    CHECK(my_stack.IsEmpty());

    Complex first_complex(3, 5);
    Complex second_complex(2, 7);

    my_stack.Push(first_complex);
    my_stack.Push(second_complex);

    CHECK_EQ(my_stack.Top(), second_complex);
    my_stack.Pop();
    CHECK_EQ(my_stack.Top(), first_complex);

    Complex third_complex(1, 1);

    StackLst my_stack2;
    my_stack2.Push(third_complex);
    my_stack = my_stack2;
    CHECK_EQ(my_stack.Top(), third_complex);

    StackLst a(my_stack);
    CHECK_EQ(a.Top(), third_complex);

    Complex fourth_complex(2.3, 7.3);

    Complex fifth_complex(2.003, 0);

    my_stack.Push(fourth_complex);
    CHECK_EQ(my_stack.Top(), fourth_complex);
    my_stack.Push(fifth_complex);
    CHECK_EQ(my_stack.Top(), fifth_complex);

    StackLst eq1;
    StackLst eq2;
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

TEST_CASE("stack list new copy func realisation") {
    StackLst stackFirst;
    StackLst stackSecond;

    // first not empty, second is empty
    Complex complexOne(1, 1);
    Complex complexTwo(2, 2);
    Complex complexThree(3, 3);
    Complex complexFour(4, 4);

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

static const Complex a(1, 2);
static const Complex b(1, 3);
static const Complex c(2, 3);

TEST_CASE("time test") {
    long long diff = 0;

    StackLst stack1;
    for (int i = 0; i < 10000; i++) {
        stack1.Push(a);
    }
    auto start = std::chrono::steady_clock::now();
    StackLst stack2(stack1);
    auto end = std::chrono::steady_clock::now();
    CHECK_EQ(stack2.Top(), a);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    StackLst stack3(std::move(stack1));
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack3.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);

    StackLst stack4;
    for (int i = 0; i < 10000; i++) {
        stack4.Push(a);
    }
    StackLst stack5;
    start = std::chrono::steady_clock::now();
    stack5 = stack4;
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack5.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff = duration.count();

    start = std::chrono::steady_clock::now();
    StackLst stack6 = std::move(stack4);
    end = std::chrono::steady_clock::now();
    CHECK_EQ(stack6.Top(), a);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    diff -= duration.count();

    CHECK(diff > duration.count() * 10);
}