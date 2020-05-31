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
	Field(Polynom &Q, int p_,int q_);
	Polynom buildCircularPolynom(int n);
	//!Algorithm for Inversion in field GF(p^m) based on Extended Euclid’s Algorithm
	Polynom& inverse(Polynom& pol);
	// /
	// %
	// gcd
};