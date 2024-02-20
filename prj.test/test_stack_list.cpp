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