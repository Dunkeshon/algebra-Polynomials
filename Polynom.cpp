//
// Created by Taisiia on 07.03.2020.
//

/*!
 * \file
 * \brief C++ file with implementation of class Polynom
 * \details Functional of polinoms, mathematical actions
 */

#include <iostream>
#include <utility>
#include <stdlib.h>
#include "cmath"
#include "Polynom.h"

using std::cout;
using std::cin;
using std::endl;


int Polynom::getLastCoefficient()
{
    PElement* temp = head;
    while (temp->next != nullptr) temp = temp->next;
    return temp->key;
}

int Polynom::getCoefficient(int pos) {
    PElement* temp = this->head;
    int counter(0);
    while (temp->next) {
        if (counter == pos) break;
        temp = temp->next;
        counter++;
    }
    return temp->key;
}


void Polynom::cutZeroes() {
    int flag = this->findPower();
    auto* temp = this->head;
    PElement* new_head = makeItem(this->head->key);
    for (size_t i(0); i < flag; i++) {
        temp = temp->next;
        appendItem(new_head, makeItem(temp->key));
    }
    clear();
    setHead(new_head);
    this->power = flag;
}


int Polynom::modInverse(int number)
{
    int x, y;
    int g = gcdExtended(number, p, &x, &y);

    if (g != 1)
        return -1;

    return (x % p + p) % p;
}


int Polynom::gcdExtended(int a, int b, int* x, int* y)
{
    if (a == 0)
    {
        *x = 0, * y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}


int Polynom::modDivision(int a, int b)
{
    a = a % p;
    int inv = modInverse(b);
    if (inv == -1)
        cout << "Division not defined";
    else return (inv * a) % p;
}


int Polynom::modMultiply(int a, int b) {
    return (a * b) % p;
}

Polynom::Polynom(){}

Polynom::Polynom(int _p) {
    head = nullptr;
    power = 0;
    p = _p;
}

void Polynom::changeField(int new_p) {
    this->p = new_p;
    this->makeMod();
    this->cutZeroes();
}

Polynom::Polynom(int _p, int _power, std::vector<int> keys) {

    try {
        if (_p < 0 || !isPrime(_p))
            throw std::invalid_argument("Module p should be prime and more than zero\n");
    }
    catch (std::exception & e)
    {
        std::cout << "Caught " << e.what() << endl;
        exit(0);
    }
    p = _p;
    power = _power;
    head = makeItem(keys[0]);

    for (int i = 1; i < keys.size(); i++) {
        appendItem(head, makeItem(keys[i]));
    }
    makeMod();
    cutZeroes();
}

Polynom::Polynom(const Polynom& other)
{
    this->copy(other);
}


void Polynom::makeMod() {
    PElement* tmp = head;
    while (tmp != nullptr) {
        if (tmp->key >= p)
            tmp->key = tmp->key % p;
        else while (tmp->key < 0) {
            tmp->key = tmp->key + p;
        }
        tmp = tmp->next;
    }
}


int Polynom::findPower() {
    int flag = 0, counter = 0;
    auto* tmp = this->head;
    while (tmp) {
        if (tmp->key) {
            flag = counter;
            counter++;
        }
        else
            counter++;
        tmp = tmp->next;
    }
    return flag;
}


typename Polynom::PElement* Polynom::makeItem(int value) {
    auto* el = new PElement;
    el->key = value;
    el->next = nullptr;
    return el;
}


void Polynom::appendItem(Polynom::PElement* head, Polynom::PElement* el) {
    PElement* tmp = head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = el;
}


void Polynom::shift(int n) {
    if (n == 0) return;
    PElement* new_head = makeItem(0);
    for (int i(1); i < n; i++) {
        appendItem(new_head, makeItem(0));
    }
    appendItem(new_head, this->head);
    setHead(new_head);
    this->power += n;
}


void Polynom::clear() {
    auto* current = this->head;
    while (current) {
        this->head = this->head->next;
        free(current);
        current = this->head;
    }
    this->power = 0;
}


void Polynom::set(int pos, int key) {
    auto* tmp = this->head;
    if (pos <= this->power) {
        int counter = 0;
        while (tmp) {
            if (counter == pos) break;
            tmp = tmp->next;
            counter++;
        }
        if (this->power == 0)
            this->head = makeItem(key);
        else
            tmp->key = key;
    }
    else {
        int counter = 0;
        if (tmp)
            while (tmp) {
                tmp = tmp->next;
                counter++;
            }
        int j = counter;
        if (counter == 0) { this->head = makeItem(0); counter++; }
        for (int j(counter); j < pos; j++) {
            appendItem(this->head, makeItem(0));
        }
        appendItem(this->head, makeItem(key));
        this->power = pos;
    }
    makeMod();
}


void Polynom::copy(const Polynom& pol) {
    this->p = pol.p;
    clear();
    auto* tmp = pol.head;
    this->head = makeItem(tmp->key);
    tmp = tmp->next;
    while (tmp) {
        appendItem(this->head, makeItem(tmp->key));
        tmp = tmp->next;
    }
    this->power = pol.power;
}


bool Polynom::isPrime(int number)
{
    if (number < 2) return false;
    int root = sqrt(number);
    for (int i = 2; i <= root; i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}


Polynom::~Polynom() {

}


typename Polynom::PElement* Polynom::getHead() const {
    return head;
}


void Polynom::setHead(Polynom::PElement* _head) {
    head = _head;
}


int Polynom::getPower() const {
    return power;
}


void Polynom::setPower(int _power) {
    power = _power;
}


void Polynom::valuate(int coef)
{
    if (coef != 0) {
        PElement* temp = head;
        while (temp) {
            temp->key = modDivision(temp->key, coef);
            temp = temp->next;
        }
    }
}


void Polynom::makeMonic() {
    int coef = getLastCoefficient();
    valuate(coef);
}


bool Polynom::isMonic() {
    int coef = getLastCoefficient();
    return(coef == 1);
}


bool Polynom::isZero() {
    Polynom zero(this->p, 0, { 0 });
    return ((*this) == zero);

}

void Polynom::handleException(Polynom& p1, Polynom& p2)
{
    try {
        if (p1.p != p2.p)
            throw std::invalid_argument("Modules of the polynoms should be the same\n");
    }
    catch (std::exception & e)
    {
        std::cout << "Caught " << e.what() << endl;
        exit(0);
    }
}


bool Polynom::isIrreducible() {
    Polynom tmp(p), odd(p, 1, { 0, 1 }), gcd_(p);
    Polynom one(this->p, 0, { 1 });
    makeMonic();
    int power_;
    for (size_t i(1); i <= this->power / 2; i++) {
        tmp = one;
        power_ = pow(p, i);
        tmp.shift(power_);
        if ((tmp - odd).power >= this->power)
            gcd_ = gcd((*this), (tmp - odd) % (*this));
        else {
            gcd_ = gcd((*this), tmp - odd);
        }
        if (gcd_ != one) return false;
        tmp.clear();

    }
    return true;
}


int Polynom::evaluate(int x)
{
    PElement* temp = head;
    int result = 0;
    int pp = 0;
    while (temp != nullptr) {
        result = result + temp->key * pow(x, pp);
        pp++;
        temp = temp->next;
    }
    return result;
}


std::vector<int> Polynom::findRoots() {

    std::vector<int> res;
    Polynom temp = *this, divider(this->p, 1, { 0,1 }), root(this->p, 0, { 0 });
    for (size_t i(0); i < this->p; i++) {
        root.head->key = i;
        while ((temp % (divider + root)).isZero()) {
            res.push_back(this->p-i);
            temp = temp / (divider + root);
            if (res.size() == this->power) break;
        }
        if (res.size() == this->power) break;
    }

    return res;
}

int Polynom::findRootNumber() {
    std::vector<int> res = findRoots();
    return res.size();
}

int Polynom::irrPolynomOrder()
{
    if (this->evaluate(0) == 0)
        return -1;

    if (!this->isIrreducible())
        return -1;

    //Creates vector for Polynom of this form (x^e - 1)
    //-1 transforms by laws of the field.
    //vector have (power - 1) and this fixes in first iteration of while loop.
    std::vector<int> vec{ -1 };
    if (this->power > 1) {
        for (auto i = 0; i < this->power - 2; ++i)
            vec.push_back(0);
        vec.push_back(1);
    }

    while (true) {

        if (vec[vec.size() - 1] == 1) { //if last element is 1 then delete it and add 0.
            vec.pop_back();
            vec.push_back(0);
        }
        vec.push_back(1);

        // if pol % this == 0
        if ((Polynom(p, vec.size() - 1, vec) % *this).isZero())
            return vec.size() - 1; //order
    }
}


//int Polynom::derivativePolynomOrder() {    
//    if (this->evaluate(0) == 0)
//        return -1;
//
//    // Yaroslav should to do function (derivativeToIrrPolynoms)
//    std::vector<Polynom> irrPolymons = derivativeToIrrPolynoms(this);
//    std::vector<int> ords(irrPolymons.size());
//    for (auto irrPol : irrPolymons) {
//        ords.push_back(irrPol.irrPolynomOrder());
//    }
//    return LCM(ords);
//}


int Polynom::LCM(std::vector<int> ords) {
    int ans = ords[0];

    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < ords.size(); i++)
        ans = (((ords[i] * ans)) /
            (gcd(ords[i], ans)));

    return ans;
}


int Polynom::gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}


void Polynom::addingPolinoms(Polynom& pol1, Polynom& pol2) {
    power = (pol1.power > pol2.power) ? pol1.power : pol2.power;
    p = pol1.p;
    head = makeItem(pol1.head->key + pol2.head->key);

    PElement* tmp1 = pol1.head->next;
    PElement* tmp2 = pol2.head->next;

    while ((tmp1) && (tmp2)) {
        appendItem(head, makeItem(tmp1->key + tmp2->key));
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    while (tmp1) {
        appendItem(head, makeItem(tmp1->key));
        tmp1 = tmp1->next;
    }
    while (tmp2) {
        appendItem(head, makeItem(tmp2->key));
        tmp2 = tmp2->next;
    }
}


void Polynom::differencePolinom(Polynom& pol1, Polynom& pol2) {
    this->power = (pol1.power > pol2.power) ? pol1.power : pol2.power;
    p = pol1.p;
    head = makeItem(pol1.head->key - pol2.head->key);

    PElement* tmp1 = pol1.head->next;
    PElement* tmp2 = pol2.head->next;

    while ((tmp1) && (tmp2)) {
        appendItem(head, makeItem(tmp1->key - tmp2->key));
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    while (tmp1) {
        appendItem(head, makeItem(tmp1->key));
        tmp1 = tmp1->next;
    }
    while (tmp2) {
        appendItem(head, makeItem(tmp2->key * (-1)));
        tmp2 = tmp2->next;
    }
}


void Polynom::multiplicatePolinom(Polynom& pol1, Polynom& pol2) {
    if (pol1.isZero() || pol2.isZero()) {
        this->power = 0;
        this->head = makeItem(0);
        return;
    }
    p = pol1.p;
    int pow = pol1.power + pol2.power;
    for (size_t k(0); k <= pow; k++) {
        int c(0);
        for (size_t j(0); j <= k; j++) {
            if ((j <= pol1.power) && (k - j <= pol2.power))
                c += modMultiply(pol1.getCoefficient(j), pol2.getCoefficient(k - j));
        }
        this->set(k, c);
    }
}


void Polynom::quot_rem(Polynom& A, Polynom& B, Polynom& Q, Polynom& R) {
    Polynom A_copy(p); A_copy = A;
    Q.clear(); R.clear();
    while (A_copy.power >= B.power) {
        int k = A_copy.power - B.power;
        Polynom B_copy(p); B_copy = B;
        if (k)
            B_copy.shift(k);
        int a_lead = A_copy.getLastCoefficient();
        int b_lead = B_copy.getLastCoefficient();

        for (size_t j(0); j <= B_copy.power; j++) {
            int set_value = modMultiply(B_copy.getCoefficient(j), modDivision(a_lead, b_lead));
            B_copy.set(j, set_value);
        }
        Polynom temp = A_copy - B_copy;
        A_copy = temp;
        A_copy.cutZeroes();
        Q.set(k, modDivision(a_lead, b_lead));
    }
    Polynom temp = Q * B;
    temp.cutZeroes();
    R = A - temp;
}


Polynom& Polynom::gcd(Polynom& a, Polynom& b) {
    if (b.isZero()) {
        a.makeMonic();
        return a;
    }
    return gcd(b, a % b);
}


void Polynom::gcdExtended(Polynom& A, Polynom& B) {
    Polynom S(p), R(p), V(p, 0, { 0 }), U(p, 0, { 1 });//U is inverse of A mod B(p^m)
    Polynom Rshift(p), Ushift(p), temp(p);

    S = B; R = A;

    while (R.power) {
        int s = S.power - R.power;
        if (s < 0) {
            temp = S; S = R; R = temp;
            temp = V; V = U; U = temp;
            s *= -1;
        }
        Rshift = R; Ushift = U;
        Rshift.shift(s); Ushift.shift(s);
        S = S - Rshift;
        V = V - Ushift;
    }
    U.cutZeroes();
    U.makeMonic();
    (*this) = U;
}


Polynom& Polynom::operator=(Polynom& other)
{
    if (this != &other) {
        this->copy(other);
    }
    return *this;
}


Polynom& GCD(Polynom a, Polynom b) {
    Polynom::handleException(a, b);

    if (a.power < b.power) {
        std::swap(a, b);
    }
    return a.gcd(a, b);
}


Polynom& derivative(Polynom& pol1)
{
    auto* result = new Polynom(pol1.p);
    auto temp = pol1.head;
    result->power = pol1.power - 1;

    int power = 0;

    while (temp) {
        if (power != 0) {
            if (result->head != nullptr) Polynom::appendItem(result->head, Polynom::makeItem(temp->key * power));
            else result->head = Polynom::makeItem(temp->key * power);
        }
        temp = temp->next;
        power++;
    }
    result->Polynom::makeMod();
    return *result;
}


std::ostream& operator<<(std::ostream& stream, Polynom& polynomial)
{
    if (polynomial.Polynom::isZero()) {
        stream << "0\n";
        return stream;
    }
    Polynom::PElement* tmp = polynomial.Polynom::head;
    int i = 0;
    bool isFirst = true;
    while (tmp != nullptr) {
        if (tmp->key == 0) {
            tmp = tmp->next;
            i++;
            continue;
        }
        if (!isFirst) cout << "+";
        else isFirst = false;
        if (tmp->key != 1 || i == 0)
            stream << tmp->key;
        if (i != 0) stream << "x^" << i;
        tmp = tmp->next;
        i++;
    }
    stream << "\n";

    return stream;
}


Polynom& operator*(Polynom& p1, Polynom& p2) {
    Polynom::handleException(p1, p2);

    auto* result = new Polynom(p1.p);
    result->Polynom::multiplicatePolinom(p1, p2);
    result->Polynom::cutZeroes();
    result->Polynom::makeMod();
    return *result;
}


Polynom& operator+(Polynom& p1, Polynom& p2) {
    Polynom::handleException(p1, p2);

    auto* result = new Polynom(p1.p);
    result->Polynom::addingPolinoms(p1, p2);
    result->Polynom::cutZeroes();
    result->Polynom::makeMod();
    return *result;
}


Polynom& operator-(Polynom& p1, Polynom& p2) {
    Polynom::handleException(p1, p2);

    Polynom* result = new Polynom(p1.p);
    result->Polynom::differencePolinom(p1, p2);
    result->Polynom::cutZeroes();
    result->Polynom::makeMod();
    return *result;
}


Polynom& operator/(Polynom& p1, Polynom& p2) {
    Polynom::handleException(p1, p2);

    int field = p1.p;
    if (p1.power < p2.power) { cout << "Can`t divide! The degree of dividend is always greater than divisor!\n\n"; return Polynom(field); }
    if (p2.isZero()) { cout << "Can't divide by 0!\n"; return Polynom(field); }
    Polynom* Q = new Polynom(field), * R = new Polynom(field);
    if (p2.power == 0) {
        p1.valuate(p2.head->key);
        Q->copy(p1);
    }
    else
        p1.Polynom::quot_rem(p1, p2, *Q, *R);
    return *Q;
}

Polynom& operator%(Polynom& p1, Polynom& p2) {
    Polynom::handleException(p1, p2);

    int field = p1.p;
    if (p1.power < p2.power) { cout << "Can`t divide! The degree of dividend is always greater than divisor!\n\n"; return Polynom(field); }
    if (p2.isZero()) { cout << "Can't divide by 0!\n"; return Polynom(field); }
    Polynom* Q = new Polynom(field), * R = new Polynom(field);
    if (p2.power == 0) {
        p1.valuate(p2.head->key);
        Q->copy(p1);
    }
    else
        p1.Polynom::quot_rem(p1, p2, *Q, *R);
    return *R;
}


bool operator==(Polynom& p1, Polynom& p2) {
    Polynom::handleException(p1, p2);

    if (p1.power != p2.power || p1.p != p2.p) return false;
    auto temp1 = p1.head, temp2 = p2.head;
    while (temp1) {
        if (temp1->key != temp2->key) return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}


bool operator!=(Polynom& p1, Polynom& p2) {
    Polynom::handleException(p1, p2);

    return !(p1 == p2);
}


Polynom& inverse(Polynom& pol, Polynom& field) {
    Polynom::handleException(pol, field);

    Polynom* result = new Polynom(pol.p);
    result->Polynom::gcdExtended(pol, field);
    result->p = pol.p;
    return *result;
}

