#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <queuelst/queuelst.hpp>

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