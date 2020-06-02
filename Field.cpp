#include <utility>
#include <iostream>
#include "Field.h"


Field::Field() {};

Field::Field(int p_, int q_) {
    this->p = p_;
    this->q = q_;
};

Field::Field(Polynom& _Q) {
    Q = _Q;
    this->p = _Q.p;
    this->q = _Q.power;
}
void Field::setPolynomAsField(Polynom& _Q){
    Q = _Q;
    this->p = _Q.p;
    this->q = _Q.power;
}


////WIP ahead
//std::vector<int> factorizeInt(int x) {//single use but is not relatable to the func it's used in,
//                                      //seen used somewhere else, probably needs to be replaced there 
//    std::vector<int> factors;
//
//    for (int i = 2; i <= sqrt(x); i++) {
//        while (x % i == 0) {
//            factors.push_back(i);
//            x /= i;
//        }
//    }
//
//    if (x != 1) {
//        factors.push_back(x);
//    }
//
//    return factors;
//}
//std::vector<Polynom> Field::findIrreduciblesOfPower(int n) {//n for never gonna give you up(represents requested power)
//    std::vector<Polynom> result;
//    std::vector<int>potentialPolConstructors = factorizeInt(pow(this->p, n) - 1);
//    for (auto& factor : potentialPolConstructors)
//    {
//        bool isSmallestPow = true;	//for black voodoo fuckery, dunno why this part shall be in algo, but i've got multiple proofs it shall
//        for (int i = 1;i < n; i++)
//        {
//            if (factor % (pow(this->p, i) - 1) == 0) {
//                isSmallestPow = false;
//                break;
//            }
//
//        }
//        if (isSmallestPow) {	//could potentially duplicate polynoms in some cases
//            Polynom probablyIrreducible = k.buildCircularPolinom(factor, q ^ n);
//            if (probablyIrreducible.isIrreducible()) {
//                result.push_back(probablyIrreducible);
//            }
//            else {
//                //here shall be the Yaroslav's func call. please replace ??? with it
//                std::vector<Polynom> multipliers = probablyIrreducable. ? ? ? ;		//Whoops, if u r here then it's actually reducable
//                for each (auto multiplier in multipliers)
//                {
//                    if (multiplier.getPower() == n) {
//                        result.push_back(multiplier);
//                    }
//                }
//            }
//        }// that's all, folks!
//    }
//}
//
//
//



int Field::mobius(int n)
{
    if (n == 1)
        return 1;

    int m = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && Polynom::isPrime(i)) {
            if (n % (i * i) == 0)
                return 0;
            else
                m++;
        }
    }
    return (m % 2 != 0) ? -1 : 1;
}

Polynom Field::buildCircularPolynom(int n)
{
    Polynom one(p, 0, { 1 }); //1
    std::vector<int> dividers;
    std::vector<Polynom> polynoms1;
    std::vector<Polynom> polynoms2;
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
            dividers.push_back(i);
    }
    int j = dividers.size() - 1;
    for (int i = 0; i < dividers.size(); i++)
    {
        if (mobius(dividers[i]) == 0)
            polynoms1.push_back(one);
        else if (mobius(dividers[i]) == 1)
        {
            Polynom b;
            Polynom tmp = one;
            tmp.shift(dividers[j]);
            b = tmp - one;

            polynoms1.push_back(b);
            j--;
        }
        else
        {
            Polynom b;
            Polynom tmp = one;
            tmp.shift(dividers[j]);
            b = tmp - one;

            polynoms2.push_back(b);
            j--;
        }
    }
    Polynom circular1 = one;
    Polynom circular2 = one;
     
    for (int k = 0; k < polynoms1.size(); k++)
    {
        circular1 = circular1 * polynoms1[k];
    }
    for (int k = 0; k < polynoms2.size(); k++)
    {
        circular2 = circular2 * polynoms2[k];
    }
    Polynom circular = circular1/circular2;
    return circular;
}

Polynom& Field::inverse(Polynom& pol) {
    Polynom::handleException(pol, Q);
    Polynom X(p), Y(p);
    Polynom* res = new Polynom(p);
    Polynom gcd_ = res->gcdExtended(pol, Q, X, Y, Q);
    return *res;
}

Polynom Field::add(Polynom& p1, Polynom& p2) {
    Polynom res = p1 + p2;
    res = res % Q;
    return res;
}

Polynom Field::subtr(Polynom& p1, Polynom& p2) {
    Polynom res = p1 - p2;
    res = res % Q;
    return res;
}

Polynom Field::mult(Polynom& p1, Polynom& p2) {
    Polynom res = p1 * p2;
    res = res % Q;
    return res;
}


Polynom Field::quot(Polynom& p1, Polynom& p2) {
    Polynom res = p1 / p2;
    res = res % Q;
    return res;
}


Polynom Field::rem(Polynom& p1, Polynom& p2) {
    Polynom res = p1 % p2;
    res = res % Q;
    return res;
}


Polynom Field::gcd(Polynom& p1, Polynom& p2) {
    Polynom res = GCD(p1,p2);
    res = res % Q;
    return res;
}

Polynom Field::derivate(Polynom& p) {
    Polynom res = derivative(p);
    res = res % Q;
    return res;
}

Polynom Field::monic(Polynom& p) {
    Polynom res; p.makeMonic();
    res = p;
    res = res % Q;
    return res;
}

int Field::eval(Polynom p, int x) {

    return p.evaluate(x);
}

std::vector<int> Field::roots(Polynom& p) {
    return p.findRoots();
}

int Field::rootsNumber(Polynom& p) {

    return p.findRootNumber();
}

bool Field::isIrreduc(Polynom& p) {
    return p.isIrreducible();
}

int Field::irrPolOrder(Polynom& p) {
    return p.irrPolynomOrder();
}

std::vector<Polynom> Field::generateIrrpols(int _p, int _q) {
    if (_p == 2) {
        switch (_q) {
        case 1:
            return std::vector<Polynom> { Polynom(2, 1, { 0,1 }), Polynom(2, 1, { 1,1 }) };

        case 2:
            return std::vector<Polynom>{Polynom(2, 2, { 1,1,1 })};
        case 3: 
            return std::vector<Polynom>{Polynom(2, 3, { 1,1,0,1 }), Polynom(2, 3, { 1,0,1,1 })};
        case 4: 
            return std::vector<Polynom>{Polynom(2, 4, { 1,1,0,0,1 }), Polynom(2, 4, { 1,0,0,1,1 }),
                Polynom(2, 4, { 1,1,1,1,1 })};
        case 5:
            return std::vector<Polynom>{Polynom(2, 5, { 1,0,1,0,0,1 }), Polynom(2, 5, { 1,0,0,1,0,1 }),
                Polynom(2, 5, { 1,1,1,1,0,1 }), Polynom(2, 5, { 1,1,1,0,1,1 }), Polynom(2, 5, { 1,1,0,1,1,1 }),
                Polynom(2, 5, { 1,0,1,1,1,1 })};
        case 6:
            return std::vector<Polynom>{ Polynom(2, 6, { 1,1,0,0,0,0,1 }), Polynom(2, 6, { 1,0,0,1,0,0,1 }),
                Polynom(2, 6, { 1,1,1,0,1,0,1 }), Polynom(2, 6, { 1,1,0,1,1,0,1 }), Polynom(2, 6, { 1,0,0,0,0,1,1 }),
                Polynom(2, 6, { 1,1,1,0,0,1,1 }), Polynom(2, 6, { 1,0,1,1,0,1,1 }), Polynom(2, 6, { 1,1,0,0,1,1,1 }),
                Polynom(2, 6, { 1,0,1,0,1,1,1 })};
        case 7:
            return std::vector<Polynom>{Polynom(2, 7, { 1,1,0,0,0,0,0,1 }), Polynom(2, 7, { 1,0,0,1,0,0,0,1 })  };
        default:
            return std::vector<Polynom> {Polynom(7, 0, {1})};

        }

        
    }
}
