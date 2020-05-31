#include "pch.h"
#include "gtest/gtest.h"
#include "Polynom.h"

TEST(IrrPolynomOrder, test1) {
	Polynom test1(2, 6, { 1, 0, 0, 1, 0, 0, 1 });
  EXPECT_EQ(test1.irrPolynomOrder(), 9);

}

TEST(IrrPolynomOrder, test2) {
    Polynom test2(2, 6, { 1, 0, 1, 1, 0, 1, 1 });//63
    EXPECT_EQ(test2.irrPolynomOrder(), 63);
   }

TEST(IrrPolynomOrder, test3) {
    Polynom test3(2, 8, { 1, 0, 0, 0, 1, 1, 1, 0, 1 });//255
    EXPECT_EQ(test3.irrPolynomOrder(), 255);
    }

TEST(IrrPolynomOrder, test4) {
    Polynom test4(2, 1, { 1, 1 });//1
    EXPECT_EQ(test4.irrPolynomOrder(), 1);
}

TEST(IrrPolynomOrder, test5) {
   
    Polynom test5(2, 10, { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 });//341
    EXPECT_EQ(test5.irrPolynomOrder(), 341);
}

TEST(IrrPolynomOrder, test6) {
   Polynom test6(3, 5, { 1, 0, 0, 0, 2, 1 });//242
    EXPECT_EQ(test6.irrPolynomOrder(), 242);
}

TEST(IrrPolynomOrder, test7) {
   Polynom test7(5, 1, { 1, 4 });//1
    EXPECT_EQ(test7.irrPolynomOrder(), 1);
}

TEST(IrrPolynomOrder, test8) {
   Polynom test8(7, 3, { 1, 0, 0, 2 });//18
    EXPECT_EQ(test8.irrPolynomOrder(), 18);
  }


TEST(_GCD, test1)
{
    Polynom p1(2,7, { 1, 0, 0, 0, 0, 0, 0, 1 });
    Polynom p2(2,5, { 1, 1, 0, 1, 0, 1 });
    Polynom res(2, 1, { 1,1 });
    EXPECT_TRUE(GCD(p1, p2)== res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}

TEST(_GCD, test2)
{
    Polynom p1(2, 5, { 1, 1, 0, 0, 0, 1 });
    Polynom p2(2, 5, { 1, 0, 0, 1, 1, 1 });
    Polynom res(2, 3, { 1,0 ,1,1});
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}

TEST(_GCD, test3)
{
    Polynom p1(3, 8, { 1, 0, 1, 1, 0, 2, 0, 0, 1 });
    Polynom p2(3, 6, { 2, 0, 2, 2, 0, 1, 2 });
    Polynom res(3, 2, { 2,0,1});
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}

TEST(_GCD, test4)
{
    Polynom p1(5, 0, { 3 });
    Polynom p2(5, 0, { 0 });
    Polynom res(5, 0, { 1 });
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}


TEST(_GCD, test5)
{
    Polynom p1(5, 2, { 1, 2, 1 });
    Polynom p2(5, 0, { 0 });
    Polynom res(5, 2, { 1,2,1 });
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}

TEST(_GCD, test6)
{
    Polynom p1(5, 2, { 4, 0, 7 });
    Polynom p2(5, 2, { 1, 2, 1 });
    Polynom res(5, 0, { 1 });
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}

TEST(_GCD, test7)
{
    Polynom p1(13, 7, { 4, 0, -1, 0, 0, -4, 0, 1 });
    Polynom p2(13, 4, { 4, 0, -1, -4, 1 });
    Polynom res(13, 1, { 12,1 });
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}


TEST(_GCD, test8)
{
    Polynom p1(29, 0, { 5 });
    Polynom p2(29, 0, { 25 });
    Polynom res(29, 0, { 1 });
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}

TEST(_GCD, test9)
{
    Polynom p1(5, 0, { 3 });
    Polynom p2(5, 0, { 3 });
    Polynom res(5, 0, { 1});
    EXPECT_TRUE(GCD(p1, p2) == res);
    EXPECT_TRUE(GCD(p2, p1) == res);
}