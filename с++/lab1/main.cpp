#include "gtest.h"
#include "tritSet.h"
#include "trit.h"

TEST(MemoryTests, AllocationTest){
    tritSet set(1000);
    size_t allocLength = set.capacity();
    EXPECT_GE(allocLength, 1000 * 2 / 8 / sizeof(uint));
}

TEST(MemoryTests, NotAllocationMemory){
    tritSet set(1000);
    size_t allocLength = set.capacity();
    set[100000] = trit::Unknown;
    EXPECT_GE(allocLength, set.capacity());
}

TEST(MemoryTests, AllocationMemory){
    tritSet set(10);
    size_t allocLength = set.capacity();
    set[30] = trit::True;
    EXPECT_TRUE(allocLength < set.capacity());

    allocLength = set.capacity();
    set[15] = trit::Unknown;
    set[11] = trit::False;
    EXPECT_TRUE(allocLength == set.capacity());
}

TEST(MemoryTests, ShrinkChecks){
    tritSet set(1000);
    set[100000] = trit::True;
    size_t allocLength = set.capacity();
    set.shrink();
    EXPECT_TRUE(allocLength > set.capacity());
}

TEST(MemoryTests, CompareTrits){
    tritSet setFirst(1000);
    size_t allocLength = setFirst.capacity();
    EXPECT_TRUE(setFirst[1000000] != trit::True);

    tritSet set(6);
    set[0] = trit::True;
    set[1] = trit::False;
    set[2] = trit::True;
    set[3] = trit::True;
    set[4] = trit::Unknown;
    set[5] = trit::False;

    EXPECT_TRUE(set[0] == trit::True);
    EXPECT_TRUE(set[1] == trit::False);
    EXPECT_TRUE(set[2] == trit::True);
    EXPECT_TRUE(set[3] == trit::True);
    EXPECT_TRUE(set[4] == trit::Unknown);
    EXPECT_TRUE(set[5] == trit::False);
}

TEST(MemoryTests, tritSetAllocation){
    tritSet setA(1000);
    tritSet setB(2000);
    tritSet setC = setA | setB;
    EXPECT_EQ(setB.capacity(), setC.capacity());
}

TEST(tritOperationTests, OrTest){
    tritSet setA(3);
    tritSet setB(3);

    setB[0] = trit::True;
    setB[1] = trit::Unknown;
    setB[2] = trit::False;

    setA[0] = trit::Unknown;
    setA[1] = trit::Unknown;
    setA[2] = trit::Unknown;
    tritSet setC = setA | setB;

    EXPECT_TRUE(setC[0] == trit::True);
    EXPECT_TRUE(setC[1] == trit::Unknown);
    EXPECT_TRUE(setC[2] == trit::Unknown);

    setA[0] = trit::False;
    setA[1] = trit::False;
    setA[2] = trit::False;
    setC = setA | setB;

    EXPECT_TRUE(setC[0] == trit::True);
    EXPECT_TRUE(setC[1] == trit::Unknown);
    EXPECT_TRUE(setC[2] == trit::False);

    setA[0] = trit::True;
    setA[1] = trit::True;
    setA[2] = trit::True;
    setC = setA | setB;

    EXPECT_TRUE(setC[0] == trit::True);
    EXPECT_TRUE(setC[1] == trit::True);
    EXPECT_TRUE(setC[2] == trit::True);

}

TEST(tritOperationTests, AndTest){
    tritSet setA(3);
    tritSet setB(3);

    setB[0] = trit::True;
    setB[1] = trit::Unknown;
    setB[2] = trit::False;

    setA[0] = trit::Unknown;
    setA[1] = trit::Unknown;
    setA[2] = trit::Unknown;
    tritSet setC = setA & setB;

    EXPECT_TRUE(setC[0] == trit::Unknown);
    EXPECT_TRUE(setC[1] == trit::Unknown);
    EXPECT_TRUE(setC[2] == trit::False);

    setA[0] = trit::False;
    setA[1] = trit::False;
    setA[2] = trit::False;
    setC = setA & setB;

    EXPECT_TRUE(setC[0] == trit::False);
    EXPECT_TRUE(setC[1] == trit::False);
    EXPECT_TRUE(setC[2] == trit::False);

    setA[0] = trit::True;
    setA[1] = trit::True;
    setA[2] = trit::True;
    setC = setA & setB;

    EXPECT_TRUE(setC[0] == trit::True);
    EXPECT_TRUE(setC[1] == trit::Unknown);
    EXPECT_TRUE(setC[2] == trit::False);
}

TEST(tritOperationTests, NotTest){
    tritSet setA(3);

    setA[0] = trit::True;
    setA[1] = trit::False;
    setA[2] = trit::Unknown;

    tritSet setC = !setA;

    EXPECT_TRUE(setC[0] == trit::False);
    EXPECT_TRUE(setC[1] == trit::True);
    EXPECT_TRUE(setC[2] == trit::Unknown);
}

TEST(OtherFunctionsTests, CardinalityTest){
    tritSet set(3);

    set[0] = trit::True;
    set[1] = trit::Unknown;
    set[2] = trit::False;
    set[5] = trit::True;

    EXPECT_EQ(set.cardinality(trit::False), 1);
    EXPECT_EQ(set.cardinality(trit::True), 2);
    EXPECT_EQ(set.cardinality(trit::Unknown), 3);
}

TEST(OtherFunctionsTests, CardinalityMapTest){
    tritSet set(32);

    set[0] = trit::True;
    set[1] = trit::Unknown;
    set[2] = trit::False;
    set[3] = trit::False;
    set[4] = trit::Unknown;
    set[5] = trit::False;
    set[31] = trit::True;

    unordered_map<trit, int> mapTrits = set.cardinality();
    EXPECT_EQ(mapTrits[trit::True], 2);
    EXPECT_EQ(mapTrits[trit::False], 3);
    EXPECT_EQ(mapTrits[trit::Unknown], 27);
}

TEST(OtherFunctionsTests, TrimTest)
{
    tritSet set(7);

    set[0] = trit::True;
    set[1] = trit::Unknown;
    set[2] = trit::False;
    set[3] = trit::False;
    set[4] = trit::Unknown;
    set[5] = trit::True;
    set[6] = trit::Unknown;

    set.trim(5);
    EXPECT_TRUE(set.lengthLogical()==4);
}

TEST(OtherFunctionsTests, LenTest)
{
    tritSet set(4);

    set[0] = trit::True;
    set[1] = trit::Unknown;
    set[2] = trit::False;
    set[3] = trit::Unknown;

    EXPECT_EQ(set.lengthLogical(), 3);
}