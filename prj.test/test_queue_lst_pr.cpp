#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <queuelstpr/queuelstpr.hpp>

TEST_CASE("push, pop, top sorted") {
    QueueLstPr qu;

    float one = 1.1;
    float two = 2.2;
    float three = 3.3;
    float four = 4.4;

    CHECK(qu.IsEmpty());

    CHECK_THROWS(qu.Top());
    CHECK_THROWS(qu.Pop());

    CHECK_NOTHROW(qu.Push(two));

    CHECK_EQ(qu.Top(), two);

    CHECK_NOTHROW(qu.Pop());

    CHECK(qu.IsEmpty());

    CHECK_NOTHROW(qu.Push(four));
    CHECK_NOTHROW(qu.Push(two));

    CHECK_EQ(qu.Top(), two);

    CHECK_NOTHROW(qu.Push(three));

    CHECK_EQ(qu.Top(), two);

    CHECK_NOTHROW(qu.Pop());

    CHECK_EQ(qu.Top(), three);

    CHECK_NOTHROW(qu.Push(one));

    CHECK_EQ(qu.Top(), one);
}

TEST_CASE("copy and ctor") {
    QueueLstPr qu;

    float one = 1.1;
    float two = 2.2;
    float three = 3.3;
    float four = 4.4;

    CHECK_NOTHROW(qu.Push(four));
    CHECK_NOTHROW(qu.Push(two));
    CHECK_NOTHROW(qu.Push(one));
    CHECK_NOTHROW(qu.Push(three));

    QueueLstPr nqu(qu);

    CHECK_EQ(nqu.Top(), one);
    CHECK_NOTHROW(nqu.Pop());
    CHECK_EQ(nqu.Top(), two);
    CHECK_NOTHROW(nqu.Pop());
    CHECK_EQ(nqu.Top(), three);
    CHECK_NOTHROW(nqu.Pop());
    CHECK_EQ(nqu.Top(), four);

    CHECK_EQ(qu.Top(), one);
    CHECK_NOTHROW(qu.Pop());
    CHECK_EQ(qu.Top(), two);
    CHECK_NOTHROW(qu.Pop());
    CHECK_EQ(qu.Top(), three);
    CHECK_NOTHROW(qu.Pop());
    CHECK_EQ(qu.Top(), four);
    CHECK_NOTHROW(qu.Pop());

    CHECK_NOTHROW(qu.Push(four));
    CHECK_NOTHROW(qu.Push(two));
    CHECK_NOTHROW(qu.Push(one));
    CHECK_NOTHROW(qu.Push(three));

    nqu = qu;

    CHECK_EQ(nqu.Top(), one);
    CHECK_NOTHROW(nqu.Pop());
    CHECK_EQ(nqu.Top(), two);
    CHECK_NOTHROW(nqu.Pop());
    CHECK_EQ(nqu.Top(), three);
    CHECK_NOTHROW(nqu.Pop());
    CHECK_EQ(nqu.Top(), four);

    CHECK_EQ(qu.Top(), one);
    CHECK_NOTHROW(qu.Pop());
    CHECK_EQ(qu.Top(), two);
    CHECK_NOTHROW(qu.Pop());
    CHECK_EQ(qu.Top(), three);
    CHECK_NOTHROW(qu.Pop());
    CHECK_EQ(qu.Top(), four);
    CHECK_NOTHROW(qu.Pop());
}