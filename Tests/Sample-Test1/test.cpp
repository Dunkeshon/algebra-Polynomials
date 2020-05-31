#include "pch.h"
#include "gtest/gtest.h"
#include "Polynom.h"
#include "Field.h"

//TEST(IrrPolynomOrder, test1) {
//	Polynom test1(2, 6, { 1, 0, 0, 1, 0, 0, 1 });
//  EXPECT_EQ(test1.irrPolynomOrder(), 9);
//
//}
//
//TEST(IrrPolynomOrder, test2) {
//    Polynom test2(2, 6, { 1, 0, 1, 1, 0, 1, 1 });
//    EXPECT_EQ(test2.irrPolynomOrder(), 63);
//   }
//
//TEST(IrrPolynomOrder, test3) {
//    Polynom test3(2, 8, { 1, 0, 0, 0, 1, 1, 1, 0, 1 });
//    EXPECT_EQ(test3.irrPolynomOrder(), 255);
//    }
//
//TEST(IrrPolynomOrder, test4) {
//    Polynom test4(2, 1, { 1, 1 });//1
//    EXPECT_EQ(test4.irrPolynomOrder(), 1);
//}
//
//TEST(IrrPolynomOrder, test5) {
//   
//    Polynom test5(2, 10, { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 });
//    EXPECT_EQ(test5.irrPolynomOrder(), 341);
//}
//
//TEST(IrrPolynomOrder, test6) {
//   Polynom test6(3, 5, { 1, 0, 0, 0, 2, 1 });
//    EXPECT_EQ(test6.irrPolynomOrder(), 242);
//}
//
//TEST(IrrPolynomOrder, test7) {
//   Polynom test7(5, 1, { 1, 4 });
//    EXPECT_EQ(test7.irrPolynomOrder(), 1);
//}
//
//TEST(IrrPolynomOrder, test8) {
//   Polynom test8(7, 3, { 1, 0, 0, 2 });
//    EXPECT_EQ(test8.irrPolynomOrder(), 18);
//  }
//
//
//TEST(_GCD, test1)
//{
//    Polynom p1(2,7, { 1, 0, 0, 0, 0, 0, 0, 1 });
//    Polynom p2(2,5, { 1, 1, 0, 1, 0, 1 });
//    Polynom res(2, 1, { 1,1 });
//    EXPECT_TRUE(GCD(p1, p2)== res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//TEST(_GCD, test2)
//{
//    Polynom p1(2, 5, { 1, 1, 0, 0, 0, 1 });
//    Polynom p2(2, 5, { 1, 0, 0, 1, 1, 1 });
//    Polynom res(2, 3, { 1,0 ,1,1});
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//TEST(_GCD, test3)
//{
//    Polynom p1(3, 8, { 1, 0, 1, 1, 0, 2, 0, 0, 1 });
//    Polynom p2(3, 6, { 2, 0, 2, 2, 0, 1, 2 });
//    Polynom res(3, 2, { 2,0,1});
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//TEST(_GCD, test4)
//{
//    Polynom p1(5, 0, { 3 });
//    Polynom p2(5, 0, { 0 });
//    Polynom res(5, 0, { 1 });
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//
//TEST(_GCD, test5)
//{
//    Polynom p1(5, 2, { 1, 2, 1 });
//    Polynom p2(5, 0, { 0 });
//    Polynom res(5, 2, { 1,2,1 });
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//TEST(_GCD, test6)
//{
//    Polynom p1(5, 2, { 4, 0, 7 });
//    Polynom p2(5, 2, { 1, 2, 1 });
//    Polynom res(5, 0, { 1 });
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//TEST(_GCD, test7)
//{
//    Polynom p1(13, 7, { 4, 0, -1, 0, 0, -4, 0, 1 });
//    Polynom p2(13, 4, { 4, 0, -1, -4, 1 });
//    Polynom res(13, 1, { 12,1 });
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//
//TEST(_GCD, test8)
//{
//    Polynom p1(29, 0, { 5 });
//    Polynom p2(29, 0, { 25 });
//    Polynom res(29, 0, { 1 });
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//TEST(_GCD, test9)
//{
//    Polynom p1(5, 0, { 3 });
//    Polynom p2(5, 0, { 3 });
//    Polynom res(5, 0, { 1});
//    EXPECT_TRUE(GCD(p1, p2) == res);
//    EXPECT_TRUE(GCD(p2, p1) == res);
//}
//
//TEST(Evaluate, test1)
//{
//	Polynom f(5, 2, { 1,2,1 });
//	EXPECT_EQ(f.evaluate(4), 25);
//}
//
//TEST(Evaluate, test2)
//{
//	Polynom g(5, 2, { 1,3,1 });
//	EXPECT_EQ(g.evaluate(4), 29);
//}
//
//TEST(Evaluate, test3)
//{
//	Polynom h(5, 1, { 1,2 });
//	EXPECT_EQ(h.evaluate(4), 9);
//}
//
//TEST(Evaluate, test4)
//{
//	Polynom b(5, 1, { 1,1 });
//	EXPECT_EQ(b.evaluate(4), 5);
//}
//
//TEST(Evaluate, test5)
//{
//	Polynom zero(5, 0, { 0 });
//	EXPECT_EQ(zero.evaluate(4), 0);
//}
//
//TEST(Evaluate, test6)
//{
//	Polynom h(5, 15, { 23,0,5,0,6,0,0,0,0,0,0,0,12,0,0,5 });
//	EXPECT_EQ(h.evaluate(5), 488281878);
//}
//
//TEST(Derivative, test1)
//{
//	Polynom f(5, 2, { 1,2,1 });
//	EXPECT_TRUE(derivative(f) == Polynom(5, 1, { 2,2 }));
//}
//
//TEST(Derivative, test2)
//{
//	Polynom g(5, 2, { 1,3,1 });
//	EXPECT_TRUE(derivative(g) == Polynom(5, 1, { 3,2 }));
//}
//
//TEST(Derivative, test3)
//{
//	Polynom k(5, 5, { 3,0,2,0,0,3 });
//	EXPECT_TRUE(derivative(k) == Polynom(5, 1, { 0,4 }));
//}
//
//
//TEST(MakeMonike, test1)
//{
//	Polynom e(5, 5, { 1, 3, 5, 5, 10, 5 });
//	e.makeMonic();
//	EXPECT_TRUE(e == Polynom(5, 1, { 2,1 }));
//}
//
//TEST(MakeMonike, test2)
//{
//	Polynom e(5, 2, { 1, 3, 5 });
//	e.makeMonic();
//	EXPECT_TRUE(e == Polynom(5, 1, { 2,1 }));
//}
//
//TEST(MakeMonike, test3)
//{
//	Polynom e(3, 6, { 1, 3, 5, 6, 0, 5, 8 });
//	e.makeMonic();
//	EXPECT_TRUE(e == Polynom(3, 6, { 2,0,1,0,0,1,1 }));
//}
//
//TEST(Inverse, test1)
//{
//	Polynom field2(5, 4, { 4,4,4,4,1 });
//	Field fi3(field2);
//	Polynom x2(5, 3, { 0,2,2,1 });
//	EXPECT_TRUE(fi3.inverse(x2) == Polynom(5, 3, { 1,2,3,1 }));
//}
//
//TEST(Inverse, test2)
//{
//	Polynom field1(3, 3, { 1,2,0,1 });
//	Field fi2(field1);
//	Polynom x1(3, 2, { 2,2,1 });
//	EXPECT_TRUE(fi2.inverse(x1) == Polynom(3, 2, { 1,1,1 }));
//}
//
//TEST(FindRoots, test1)
//{
//	Polynom root1(5, 2, { 1,2,1 });
//	std::vector<int> rootvec1 = root1.findRoots();
//	std::vector<int> roots{ 4,4 };
//	for (int i = 0; i < rootvec1.size(); i++)
//		EXPECT_EQ(rootvec1[i], roots[i]);
//}
//
//TEST(FindRoots, test2)
//{
//	Polynom root1(5, 2, { 1,3,1 });
//	std::vector<int> rootvec1 = root1.findRoots();
//	std::vector<int> roots{ 1,1 };
//	for (int i = 0; i < rootvec1.size(); i++)
//		EXPECT_EQ(rootvec1[i], roots[i]);
//}
//
//TEST(FindRoots, test3)
//{
//	Polynom root1(5, 4, { 1,0,0,0,2 });
//	std::vector<int> rootvec1 = root1.findRoots();
//	EXPECT_EQ(rootvec1.size(), 0);
//
//}
//
//TEST(FindRoots, test4)
//{
//	Polynom root1(5, 3, { 0,2,3,1 });
//	std::vector<int> rootvec1 = root1.findRoots();
//	std::vector<int> roots{ 0,4,3 };
//	for (int i = 0; i < rootvec1.size(); i++)
//		EXPECT_EQ(rootvec1[i], roots[i]);
//}
//
//TEST(FindRoots, test5)
//{
//	Polynom root1(5, 3, { 2,3,3,1 });
//	std::vector<int> rootvec1 = root1.findRoots();
//	std::vector<int> roots{ 3 };
//	for (int i = 0; i < rootvec1.size(); i++)
//		EXPECT_EQ(rootvec1[i], roots[i]);
//}
//
//TEST(FindRoots, test6)
//{
//	Polynom root1(5, 3, { 2,3,4,1 });
//	std::vector<int> rootvec1 = root1.findRoots();
//	std::vector<int> roots{ 1 };
//	for (int i = 0; i < rootvec1.size(); i++)
//		EXPECT_EQ(rootvec1[i], roots[i]);
//}