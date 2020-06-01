#include "Ring.h"

Ring::Ring() {};


Polynom Ring::add(Polynom& p1, Polynom& p2) {
    Polynom res = p1 + p2;
    return res;
}

Polynom Ring::subtr(Polynom& p1, Polynom& p2) {
    Polynom res = p1 - p2;
    return res;
}

Polynom Ring::mult(Polynom& p1, Polynom& p2) {
    Polynom res = p1 * p2;
    return res;
}


Polynom Ring::quot(Polynom& p1, Polynom& p2) {
    Polynom res = p1 / p2;
    return res;
}


Polynom Ring::rem(Polynom& p1, Polynom& p2) {
    Polynom res = p1 % p2;
    return res;
}

Polynom Ring::derivate(Polynom& p) {
    Polynom res = derivative(p);
    return res;
}

Polynom Ring::monic(Polynom& p) {
    p.makeMonic();
    return p;
}

int Ring::eval(Polynom p, int x) {

    return p.evaluate(x);
}


Polynom Ring::gcd(Polynom& p1, Polynom& p2) {
    Polynom res = GCD(p1, p2);
    return res;
}