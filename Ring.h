#pragma once
#include "Polynom.h"


class Ring : public Polynom {

private:

protected:
	// a vector of irreducible polynomials
	std::vector<Polynom> polynomials;
	// R(p^n)[x]/Q
	Polynom Q;//could be irreducible
	//p could be prime or not
public:
	Ring();
	//+
	//-
	//*
	//==
	//!=
};