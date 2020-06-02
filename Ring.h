#pragma once
#include "Polynom.h"


class Ring : public Polynom {
private:	
	std::vector<Polynom> polynomials;
public:
	Ring();
	Polynom add(Polynom& p1, Polynom& p2);
	Polynom subtr(Polynom& p1, Polynom& p2);
	Polynom mult(Polynom& p1, Polynom& p2);
	Polynom quot(Polynom& p1, Polynom& p2);
	Polynom rem(Polynom& p1, Polynom& p2);

	Polynom derivate(Polynom& p);
	Polynom monic(Polynom& p);
	int eval(Polynom p, int x);

	Polynom gcd(Polynom& p1, Polynom& p2);

};