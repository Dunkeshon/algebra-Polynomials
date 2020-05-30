#pragma once
#include "Ring.h"
#include "Polynom.h"


class Field :public Ring {
private:
	int mobius(int n);
	//Q is reducible
	//p is prime
public:
	Field();
	Field(int p);
	Polynom buildCircularPolynom(int n, int p);
	// /
	// %
	// gcd
	// inverse
};