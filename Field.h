#pragma once
#include "Ring.h"


class Field :public Ring {
private:
	int mobius(int n);
	Polynom Q;//Q is reducible polynom of degree q
	int p;//p is prime
	int q;//extension
public:
	Field();
	Field(int p_, int q_);
	Field(Polynom &Q);
    static std::vector<Polynom> generateIrrpols(int _p, int _q);
	Polynom buildCircularPolynom(int n);
    //!Algorithm for Inversion in field GF(p^m) based on Extended Euclids Algorithm
	Polynom& inverse(Polynom& pol);

	Polynom add(Polynom& p1, Polynom& p2);
	Polynom subtr(Polynom& p1, Polynom& p2);
	Polynom mult(Polynom& p1, Polynom& p2);
	Polynom quot(Polynom& p1, Polynom& p2);
	Polynom rem(Polynom& p1, Polynom& p2);

	Polynom gcd(Polynom& p1, Polynom& p2);

	Polynom derivate(Polynom& p);
	Polynom monic(Polynom& p);
	int eval(Polynom p,int x);

	std::vector<int> roots(Polynom& p);
	int rootsNumber(Polynom& p);

	bool isIrreduc(Polynom& p);
	int irrPolOrder(Polynom& p);

	std::vector<Polynom> findIrreduciblesOfPower(int n);
};
