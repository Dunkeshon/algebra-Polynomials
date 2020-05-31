#pragma once
#include "Ring.h"


class Field :public Ring {
private:
	int mobius(int n);
	Polynom Q;//Q is reducible
	int p;//p is prime
public:
	Field();
	Field(int p_);
	Field(Polynom &Q, int p_);
	Polynom buildCircularPolynom(int n);
	//!Algorithm for Inversion in field GF(p^m) based on Extended Euclid’s Algorithm
	Polynom& inverse(Polynom& pol);
	// /
	// %
	// gcd
	// inverse
};