#include <utility>
#include <iostream>
#include <list>
#include <cmath>
#include "Field.h"


void Field::handleException(Polynom& p1)
{
    try {
        if (p1.getPower() >= Q.getPower())
            throw std::invalid_argument("Power of the polynom must be less than q\n");
    }
    catch (std::exception & e)
    {
        std::cout << "Caught " << e.what() << std::endl;
        exit(0);
    }
}

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


std::vector<Polynom> Field::genIrrPolynomials(int p, int q){
    std::vector<Polynom> result, temp;
    Polynom circular;

    int num = pow(p, q) - 1;
    for (int m = 1; m <= num; m++) {
        if ((num % m) == 0) {
            circular = buildCircularPolynom(m);
            std::cout << circular;
            if (circular.power >= q) {
                temp = circular.distinctDegreeDecomposition();
                for (auto& ir : temp) {
                    if (ir.power == q) {
                        result.push_back(ir);
                    }
                }
            }
        }
    }
    return result;
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

int Field::phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    if (n > 1)
        result -= result / n;
    return result;
}


Polynom Field::find_Ri(int q, int n, int i, int j) {
    while ((int)pow((double)q, (double)j) % (n / Polynom::gcd(n, i)) == 1) {
        j++;
    }
    int stepin = (int)pow((double)q, (double)j);
    std::string temp = "";
    for (int k = 0; k < stepin; k++) {
        if ((int)pow((double)q, (double)k) * i == k)
            temp += "1";
        else
            temp += "0";
    }
    Polynom result(q, temp);
    return result;
}


std::vector<Polynom> Field::factorise_Ri(int q, int n) {
    if (n <= q) {
        Polynom CyclePol = buildCircularPolynom(n);
        std::vector<Polynom> result;
        result.push_back(CyclePol);
        return result;
    }
    if (Polynom::gcd(n, q) == 1) {

        std::vector<Polynom> result;
        int d = 1;//degree
        while ((int)pow((double)q, (double)d) % n == 1) {
            d++;
        }
        Polynom cyclicPol;

        size_t factorsCount = phi(n) / d;
        size_t factorPower = d;
        if (factorsCount == 1) {
            Polynom CyclePol = buildCircularPolynom(n);
            result.push_back(CyclePol);
            return result;
        }
        size_t i = 1;

        Polynom CyclePol = buildCircularPolynom(n);
        std::list<Polynom> temp_pol;
        temp_pol.push_back(CyclePol);
        while (result.size() < factorsCount) {
            long long j = 1;

            Polynom pol_Ri = find_Ri(q, n, i, j);
            bool factorized = false;
            j = 0;
            while (j < q) {
                Polynom gcdRi = gcd(temp_pol.front(), CyclePol);
                if (j == 0 && gcdRi == temp_pol.front()) {
                    factorized = false;
                    break;
                }

                long long gcdPower = gcdRi.getPower();
                if (gcdPower == d) {
                    factorized = true;
                    gcdRi.makeMonic();
                    result.push_back(gcdRi);
                }
                else if (gcdPower % d == 0) {
                    factorized = true;
                    temp_pol.push_back(gcdRi);
                }

                pol_Ri = pol_Ri + Polynom(q, "1");
                j++;
            }
            if (factorized) {
                temp_pol.pop_front();
            }
            i++;

        }
        return result;
    }
}


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
    Polynom circular = circular1 / circular2;
    return circular;
}

Polynom& Field::inverse(Polynom& pol) {
    handleException(pol);
    Polynom::handleException(pol, Q);
    Polynom X(p), Y(p);
    Polynom* res = new Polynom(p);
    Polynom gcd_ = res->gcdExtended(pol, Q, X, Y, Q);
    return *res;
}

Polynom Field::add(Polynom& p1, Polynom& p2) {
    handleException(p1);
    handleException(p2);
    Polynom res = p1 + p2;
    res = res % Q;
    return res;
}

Polynom Field::subtr(Polynom& p1, Polynom& p2) {
    handleException(p1);
    handleException(p2);
    Polynom res = p1 - p2;
    res = res % Q;
    return res;
}

Polynom Field::mult(Polynom& p1, Polynom& p2) {
    handleException(p1);
    handleException(p2);
    Polynom res = p1 * p2;
    res = res % Q;
    return res;
}


Polynom Field::quot(Polynom& p1, Polynom& p2) {
    handleException(p1);
    handleException(p2);
    Polynom res = p1 / p2;
    res = res % Q;
    return res;
}


Polynom Field::rem(Polynom& p1, Polynom& p2) {
    handleException(p1);
    handleException(p2);
    Polynom res = p1 % p2;
    res = res % Q;
    return res;
}


Polynom Field::gcd(Polynom& p1, Polynom& p2) {
    handleException(p1);
    handleException(p2);
    Polynom res = GCD(p1,p2);
    res = res % Q;
    return res;
}

Polynom Field::derivate(Polynom& _p) {
    handleException(_p);
    Polynom res = derivative(_p);
    res = res % Q;
    return res;
}

Polynom Field::monic(Polynom& _p) {
    handleException(_p);
    Polynom res; _p.makeMonic();
    res = _p;
    res = res % Q;
    return res;
}

int Field::eval(Polynom _p, int x) {
    handleException(_p);
    _p = _p % Q;
    return _p.evaluate(x);
}

std::vector<int> Field::roots(Polynom& _p) {
    handleException(_p);
    return _p.findRoots();
}

int Field::rootsNumber(Polynom& _p) {
    handleException(_p);
    return _p.findRootNumber();
}

bool Field::isIrreduc(Polynom& _p) {
    handleException(_p);
    return _p.isIrreducible();
}

int Field::irrPolOrder(Polynom& _p) {
    handleException(_p);
    return _p.irrPolynomOrder();
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
            return std::vector<Polynom>{Polynom(2, 7, { 1,1,0,0,0,0,0,1 }), Polynom(2, 7, { 1,0,0,1,0,0,0,1 }),
                Polynom(2, 7, { 1,1,1,1,0,0,0,1 }), Polynom(2, 7, { 1,0,0,0,1,0,0,1 }), Polynom(2, 7, { 1,0,1,1,1,0,0,1 })};
        case 8: 
            return std::vector<Polynom>{Polynom(2, 8, {1,1,0,1,1,0,0,0,1}), Polynom(2, 8, {1,0,1,1,1,0,0,0,1}),
                Polynom(2, 8, { 1,1,0,1,0,1,0,0,1 }), Polynom(2, 8, { 1,1,0,1,1,1,1,0,1}) };
        case 9:
            return std::vector<Polynom> {Polynom(2, 9, {1,1,0,0,0,0,0,0,0,1}), Polynom(2, 9, { 1,0,0,0,1,0,0,0,0,1}),
                Polynom(2, 9, {1,1,1,0,1,0,0,0,0,1}), Polynom(2, 9, {1,1,0,1,1,0,0,0,0,1})};
        default:
            return std::vector<Polynom> {Polynom(2, 0, {1})};

        }  
    }
    else if (_p == 3) {
        switch (_q) {
        case 1: 
            return std::vector<Polynom> { Polynom(3, 1, { 0,1 }), Polynom(3, 1, { 1,1 }), Polynom(3, 1, { 2,1 }) };
        case 2:
            return std::vector<Polynom> {Polynom(3, 2, {1,0,1 }), Polynom(3, 2, { 2,1,1 }), Polynom(3, 2, { 2,2,1 })};
        case 3:
            return std::vector<Polynom> {Polynom(3, 3, { 1,2,0,1 }), Polynom(3, 3, { 2,2,0,1 }), Polynom(3, 3, { 2,0,1,1 })};
        case 4:
            return std::vector<Polynom> {Polynom(3, 4, { 2,1,0,0,1 }), Polynom(3, 4, { 2,2,0,0,1 }), Polynom(3, 4, { 2,0,1,0,1 })};
        case 5:
            return std::vector<Polynom> {Polynom(3, 5, {1,2,0,0,0,1 }), Polynom(3, 5, { 2,2,0,0,0,1 }), Polynom(3, 5, { 2,1,1,0,0,1 })};
        case 6:
            return std::vector<Polynom> {Polynom(3, 6, { 2,1,0,0,0,0,1 }), Polynom(3, 6, { 2,2,0,0,0,0,1 }),
                Polynom(3, 6, { 1,1,1,0,0,0,1 })};
        case 7:
            return std::vector<Polynom> {Polynom(3, 7, { 2,0,1,0,0,0,0,1 }), Polynom(3, 7, { 1,2,1,0,0,0,0,1 }), 
                Polynom(3, 7, { 1,0,2,0,0,0,0,1 })};
        default:
            return std::vector<Polynom> {Polynom(3, 0, { 1 })};
           
        }
    }
    else if (_p == 5) {
        switch (_q) {
        case 1:
            return std::vector<Polynom> {Polynom(5, 1, { 0,1 }), Polynom(5, 1, { 1,1 }), Polynom(5, 1, { 2,1 }) };
        case 2:
            return std::vector<Polynom> {Polynom(5, 2, { 2,0,1 }), Polynom(5, 2, { 3,0,1 }), Polynom(5, 2, { 1,1,1 })};
        case 3:
            return std::vector<Polynom> {Polynom(5, 3, { 1,1,0,1 }), Polynom(5, 3, { 4,1,0,1 }), Polynom(5, 3, { 1,2,0,1 })};
        case 4:
            return std::vector<Polynom> {Polynom(5, 4, { 2,0,0,0,1 }), Polynom(5, 4, { 3,0,0,0,1 }), Polynom(5, 4, { 4,1,0,0,1 })};
        case 5:
            return std::vector<Polynom> {Polynom(5, 5, { 1,4,0,0,0,1 }), Polynom(5, 5, { 2,4,0,0,0,1 }), Polynom(5, 5, { 3,4,0,0,0,1 })};
  
        default:
            return std::vector<Polynom> {Polynom(5, 0, { 1 })};

        }
     }
    else if (_p == 7) {
        switch (_q) {
        case 1:
            return std::vector<Polynom> {Polynom(7, 1, { 0,1 }), Polynom(7, 1, { 1,1 }), Polynom(7, 1, { 2,1 }) };
        case 2:
            return std::vector<Polynom> {Polynom(7, 2, { 2,0,1 }), Polynom(7, 2, { 1,0,1 }), Polynom(7, 2, { 4,1,1 })};
        case 3:
            return std::vector<Polynom> {Polynom(7, 3, { 2,0,0,1 }), Polynom(7, 3, { 3,0,0,1 }), Polynom(7, 3, { 4,0,0,1 })};
        case 4:
            return std::vector<Polynom> {Polynom(7, 4, { 1,1,0,0,1 }), Polynom(7, 4, { 2,1,0,0,1 }), Polynom(7, 4, { 4,1,0,0,1 })};

        default:
            return std::vector<Polynom> {Polynom(7, 0, { 1 })};

        }
    }
  }

