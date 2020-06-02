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
#include <algorithm>
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


Polynom::Polynom(int _p, std::string keys)
{
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
    int coefficient = 0;
    bool isCoefficient = true;
    bool wasPower = false;
    int currentPower = 0;
    int currentOutputPower = 0;
    keys += "+";

    for (int i = 0; i < keys.length(); i++) {
        char current = keys[i];
        if (isOperator(current)) {
            if (coefficient == 0) coefficient = 1;
            if (wasPower && currentPower != currentOutputPower)
                while (currentOutputPower != currentPower) {
                    if (currentOutputPower == 0) head = makeItem(0);
                    else appendItem(head, makeItem(0));
                    currentOutputPower++;
                }
            if (currentOutputPower == 0) head = makeItem(coefficient);
            else appendItem(head, makeItem(coefficient));
            currentPower = 0;
            coefficient = 0;
            currentOutputPower++;
            wasPower = false;
            isCoefficient = true;
        }
        else if (isPower(current)) {
            isCoefficient = false;
        } else if (!isalpha(current)) { //number
            if (isCoefficient) coefficient = coefficient * 10 + (current - '0');
            else {
                currentPower = currentPower * 10 + (current - '0');
                wasPower = true;
            }
        } 
    }
    this->power = currentOutputPower - 1;
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

void Polynom::deleteListNode(PElement* node)
{
    if (!node) {
        return;
    }

    deleteListNode(node->next);
    delete node;
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
    if (n == 0) 
        return;
    PElement* new_head = makeItem(0);
    for (int i=1; i < n; i++) 
        appendItem(new_head, makeItem(0));
    appendItem(new_head, this->head);
    setHead(new_head);
    this->power += n;
}


void Polynom::clear() {
    deleteListNode(this->head);
    this->head = nullptr;
    this->power = 0;
}


void Polynom::set(int pos, int key_) {
    auto* tmp = this->head;
    if (pos <= this->power) {
        int counter = 0;
        while (tmp) {
            if (counter == pos) break;
            tmp = tmp->next;
            counter++;
        }
        if (this->power == 0)
            this->head = makeItem(key_);
        else if (tmp) tmp->key = key_;
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
        appendItem(this->head, makeItem(key_));
        this->power = pos;
    }
    makeMod();
}

std::vector<int> Polynom::getCoefficientVector(int n)
{
    std::vector<int> vec;
    vec.resize(n);
    int i = 0;
    while (head) {
        vec[i] = head->key;
        head = head->next;
        i++;
    }
    return vec;
}

int Polynom::getRank(std::vector<std::vector<int>>& matrix)
{
    int rank = matrix.size();

    for (int row = 0; row < rank; row++)
    {
        if (matrix[row][row])
        {
            for (int col = 0; col < matrix.size(); col++)
            {
                if (col != row)
                {
                    int mult = matrix[col][row] / matrix[row][row];
                    for (int i = 0; i < rank; i++)
                        matrix[col][i] -= mult * matrix[row][i];
                }
            }
        }
        else
        {
            bool reduce = true;
            for (int i = row + 1; i < matrix.size(); i++)
            {
                if (matrix[i][row])
                {
                    swap(matrix, row, i, rank);
                    reduce = false;
                    break;
                }
            }
            if (reduce)
            {
                rank--;
                for (int i = 0; i < matrix.size(); i++)
                    matrix[i][row] = matrix[i][rank];
            }

            row--;
        }
    }
    return rank;
}

void Polynom::swap(std::vector<std::vector<int>>& matrix, int row1, int row2, int col)
{

    for (int i = 0; i < col; i++)
    {
        int temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

std::vector<std::vector<int>> Polynom::transpose(std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<int>> transposed;
    transposed.resize(matrix.size());
    for (int i = 0; i < matrix.size(); i++) transposed[i].resize(matrix.size());
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix.size(); j++) transposed[i][j] = matrix[j][i];
    return transposed;
}

void Polynom::copy(const Polynom& pol) {
    
    this->p = pol.p;
    clear();
    auto* tmp = pol.head;
    if (tmp) {
        this->head = makeItem(tmp->key);
        tmp = tmp->next;
    }
    else this->head = NULL;
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

bool Polynom::isOperator(char token)
{
    return token == '+' || token == '-' || token == '*' || token == '/';
}

bool Polynom::isPower(char token)
{
    return token == '^';
}


Polynom::~Polynom() {
    deleteListNode(this->head);
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
        if (gcd_.power!=0) return false;
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
            if(i)
            res.push_back(this->p-i);
            else res.push_back(i);
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


int Polynom::arbitraryPolynomOrder(std::vector<std::pair<Polynom, int>> polDecomposition) {
    if (this->evaluate(0) == 0)
        return -1;

    if (this->isIrreducible())
        return this->irrPolynomOrder();

    int max = 0;
    // Yaroslav should to do function (getFactors)
    //std::vector<std::pair<Polynom, int>> polDecomposition = getFactors(Polynom(*this));
    std::vector<int> ords;
    for (auto irrPol : polDecomposition) {
        ords.push_back((irrPol.first).irrPolynomOrder());
        if (irrPol.second > max) max = irrPol.second;
    }

    int t = 0;
    for (; std::pow(this->p, t) < max; t++);

    int koef = std::pow(this->p, t);

    return koef * LCM(ords);
}


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
    this->power = (pol1.power > pol2.power) ? pol1.power : pol2.power;
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
        *this = Polynom(p, 0, { 0 });
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
    Polynom A_copy(p);
    A_copy = A;
    Q = Polynom(p, 0, { 0 });
    R = Polynom(p, 0, { 0 });
    while (A_copy.power >= B.power) 
    {
        int k = A_copy.power - B.power;
        Polynom B_copy(p); 
        B_copy = B;
        if (k)
            B_copy.shift(k);
        int a_lead = A_copy.getLastCoefficient();
        int b_lead = B_copy.getLastCoefficient();

        for (int j=0; j <= B_copy.power; j++) 
        {
            int set_value = modMultiply(B_copy.getCoefficient(j), modDivision(a_lead, b_lead));
            B_copy.set(j, set_value);
        }
        Polynom temp = A_copy - B_copy;
        A_copy = temp;
        Q.set(k, modDivision(a_lead, b_lead));
    }
    Polynom temp = Q * B;
    R = A - temp;
}


Polynom Polynom::gcd(Polynom a, Polynom b) {
    if (b.isZero()) {
        a.makeMonic();
        return a;
    }
    return gcd(b, a % b);
}


Polynom Polynom::gcdExtended(Polynom A, Polynom B, Polynom& X, Polynom& Y,Polynom& Q) {
    if (A.isZero()) {
        X = Polynom(p, 0, {0});
        Y = Polynom(p, 0, {1});
        return B;
   }
    Polynom X1(p), Y1(p);
    Polynom Gcd_ = gcdExtended(B%A,A,X1,Y1,Q);
    X = Y1 - ((B / A) * X1)%Q;
    Y = X1;
    *this = X;
    return Gcd_;
}


Polynom& Polynom::operator=(Polynom other)
{
    if (this != &other) {
        this->copy(other);
    }
    return *this;
}


Polynom GCD(Polynom a, Polynom b) {
    Polynom::handleException(a, b);

    if (a.power < b.power) {
        std::swap(a, b);
    }
    return a.gcd(a, b);
}

int mod(int x, int y) {
    if (x >= 0) return x % y;
    else if (x < 0) {
        while (x < (-y)) {
            x = x + y;
        }
        return (y - (-x));
    }
}


bool Polynom::isZeroRow(std::vector<int>& row,int i) {

    for (int i(0); i < row.size(); i++) {
        if (row[i] != 0)
            return false;
    } 
    return true;
 }

std::vector<int> Polynom::getCoefs() {
    std::vector<int> res;
    PElement* temp = this->head;
    while (temp) {
        res.push_back(temp->key);
        temp = temp->next;
    }
    return res;
}

void Polynom::deleteDuplicates(std::vector<Polynom>& vec, Polynom p) {
    for (int i(0); i < vec.size();i++) {//remove p in vec
        if (vec[i] == p) {
            vec.erase(vec.begin() + i);
            i--;
        }
    }
    for (int i(0); i < vec.size(); i++) {//remove duplicates
        for(int j(0);j<vec.size();j++)
            if (vec[i] == vec[j] && i!=j) {
                vec.erase(vec.begin() + j);
                j--;
            }
    }
   
}

std::vector<Polynom> getFactors(Polynom p)
{
    std::vector<Polynom> result;

    if (GCD(p, derivative(p)) == Polynom(p.p, "1")) {
        int maxPower = p.getPower();
        std::vector<std::vector<int>> coefficientMatrix;
        coefficientMatrix.resize(maxPower);

        int iq = 0;
        for (int i = 0; i < maxPower; i++) {
            iq = i * p.p;
            std::string m = "x^" + std::to_string(iq);
            Polynom mon(p.p, m);
            Polynom res = mon % p;
            coefficientMatrix[i] = res.getCoefficientVector(maxPower);
        }
        for (int i = 0; i < maxPower; i++) {
            coefficientMatrix[i][i] = mod(coefficientMatrix[i][i] - 1, p.p);
        }

       // p.displayMatrix(coefficientMatrix);
        //we transpose matrix to do all actions with columns rather than rows
        std::vector<std::vector<int>> transposed = Polynom::transpose(coefficientMatrix);
        int rank = Polynom::getRank(transposed);
        int k = transposed.size() - rank;

        if (k == 1) { //polynomial is irreducible
            result.push_back(p);
            return result;
        }
        coefficientMatrix = Polynom::transpose(transposed);

        //cout << "rank  = " << rank << endl;
        std::vector<std::vector<int>> basis;
        for (int i = 0; i < coefficientMatrix.size(); i++) {
            for (int j = 0; j < coefficientMatrix.size(); j++)
                if (coefficientMatrix[i][j] != 0) {
                    basis.push_back(coefficientMatrix[i]);
                    break;
                }
        }
       // p.displayMatrix(coefficientMatrix);

        for (auto b : basis) {
            for (int i = 0; i < p.p; i++) {
                Polynom res = GCD(p, Polynom(p.p, b.size() - 1, b) - Polynom(p.p, std::to_string(i)));
                if (res != Polynom(p.p, "1")) result.push_back(res);
            }
        }

        Polynom::deleteDuplicates(result,p);

    }
    else {
        cout << "GCD != 1" << endl;
        //TODO
    }

    return result;
}


void Polynom::displayMatrix(std::vector<std::vector<int>>& matrix) {
    for (int i(0); i < matrix.size(); i++) {
        for (int j(0); j < matrix.size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}


Polynom derivative(Polynom& pol1)
{
    Polynom result(pol1.p);
    auto temp = pol1.head;
    result.power = pol1.power - 1;

    int power = 0;

    while (temp) {
        if (power != 0) {
            if (result.head != nullptr) Polynom::appendItem(result.head, Polynom::makeItem(temp->key * power));
            else result.head = Polynom::makeItem(temp->key * power);
        }
        temp = temp->next;
        power++;
    }
    result.Polynom::makeMod();
    result.Polynom::cutZeroes();
    return result;
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


Polynom operator*(Polynom p1, Polynom p2) {
    Polynom::handleException(p1, p2);

    Polynom result(p1.p);
    result.Polynom::multiplicatePolinom(p1, p2);
    result.Polynom::cutZeroes();
    result.Polynom::makeMod();
    result.p = p1.p;
    return result;
}


Polynom operator+(Polynom p1, Polynom p2) {
    Polynom::handleException(p1, p2);

    Polynom result(p1.p);
    result.Polynom::addingPolinoms(p1, p2);
    result.Polynom::cutZeroes();
    result.Polynom::makeMod();
    result.p = p1.p;
    return result;
}


Polynom operator-(Polynom p1, Polynom p2) {
    Polynom::handleException(p1, p2);
    Polynom result(p1.p);
    result.Polynom::differencePolinom(p1, p2);
    result.Polynom::cutZeroes();
    result.Polynom::makeMod();
    result.p = p1.p;
    return result;
}


Polynom operator/(Polynom p1, Polynom p2) {
    Polynom::handleException(p1, p2);

    int field = p1.p;
    if (p1.power < p2.power) { cout << "Can`t divide! The degree of dividend is always greater than divisor!\n\n"; return Polynom(field); }
    if (p2.isZero()) { cout << "Can't divide by 0!\n"; return Polynom(field); }
    Polynom* Q = new Polynom(field), *R = new Polynom(field);
    if (p2.power == 0) {
        Q->copy(p1);
    }
    else
        p1.Polynom::quot_rem(p1, p2, *Q, *R);
    return *Q;
}

Polynom operator%(Polynom p1, Polynom p2) {//using for mod
    Polynom::handleException(p1, p2);

    int field = p1.p;
    if (p1.power < p2.power) {return p1; }
    if (p2.isZero()) { cout << "Can't divide by 0!\n"; return Polynom(field); }
    Polynom* Q = new Polynom(field), * R = new Polynom(field);
    if (p2.power == 0) {
        Q->copy(p1);
    }
    else
        p1.Polynom::quot_rem(p1, p2, *Q, *R);
    return *R;
}


bool operator==(Polynom p1, Polynom p2) {
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


bool operator!=(Polynom p1, Polynom p2) {
    Polynom::handleException(p1, p2);

    return !(p1 == p2);
}

