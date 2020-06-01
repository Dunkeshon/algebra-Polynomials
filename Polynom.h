//
// Created by Taisiia on 07.03.2020.
//
/*!
 * \file
 * \brief Header file containing class Polynom
 * \details This file contains definition of the class Polynom
 */


#ifndef POLINOMS_POLYNOM_H
#define POLINOMS_POLYNOM_H

#include <vector>
#include <string>

 /*!
  * \brief class Polynom contains fields that describe polinom
  * \details Every object of this class describe separate polinom
  *
  * a + bx + cx^2
  * power of this polinom - 2
  * a, b, c - coefficients of polinom (key)
  *
  * Every object of this class have structure "PElement"
  * Every structure "PElement" have objects that contains fields "key" and "next"
  * key - coefficient of term
  * next - pointer to next object of structure "PElement"
  */

class Polynom;
//forward declaration

class Polynom {
private:

    struct PElement {
        //!coefficient of terms of polinom
        int key;
        //!pointer to next term
        PElement* next{ nullptr };
    };
    //!Mod of polynom
    void makeMod();
    //!Pointer to the first term of every object of class "Polynom"
    PElement* head = nullptr;

    void deleteListNode(PElement* node);

    //Clear PElement list
     //!Making term of structure "PElement" (element of polinom) using the value of coefficient
    static PElement* makeItem(int val);
    //!Adding term to the end of the polinom
    static void appendItem(PElement* head, PElement* el);
    //!Set the coefficient coef. on position pos equal to the value key
    void set(int pos, int key);
    std::vector<int> getCoefficientVector(int n);
    static int getRank(std::vector<std::vector<int>>& matrix);
    static void swap(std::vector<std::vector<int>>& matrix, int row1, int row2, int col);
    static std::vector<std::vector<int>> transpose(std::vector<std::vector<int>>& matrix);
    
 friend class UiController;
public:
    void clear();
    int getLastCoefficient();
    int getCoefficient(int pos);
    int modInverse(int x);
    int gcdExtended(int a, int b, int* x, int* y);
    int modDivision(int a, int b);
    int modMultiply(int a, int b);
    //!Find real power after each operation
    int findPower();
    //!Cut last zeroes and update power
    void cutZeroes();
    //!Copy polynom
    void copy(const Polynom& pol);
    

    void addingPolinoms(Polynom& pol1, Polynom& pol2);
    void differencePolinom(Polynom& pol1, Polynom& pol2);
    void multiplicatePolinom(Polynom& pol1, Polynom& pol2);

    //!polynomial degree (maximum degree that a variable can have)
    int power;
    //!polynomial field
    int p;
    //!Structure that shows every term of every object of class "Polynom"
    //!A polynomial whose leading coefficientis 1 is called monic
    bool isMonic();
    //!Compare the polynomial with f(x) = 0
    bool isZero();
    static void handleException(Polynom& p1, Polynom& p2);
    bool isPrime(int number);
    bool isOperator(char token);
    bool isPower(char token);

    //!empty constructor
    Polynom();
    Polynom(int _p);

    //!constructor that take power of polinom and vector of coefficients of this polinom
    explicit Polynom(int _p, int _power, std::vector<int> keys);
    //!constructor to parse input as a string)
    //!the input should be in the increasing order, see sample input in main
    Polynom(int _p, std::string keys);

    /** Copy constructor.
     * The copy constructor added here to make a deep copy
     * when initialize one object using another object.
     */
    Polynom(const Polynom& other);

    ~Polynom();

    void changeField(int new_p);

    //!Getter and Setters (for me they are useless, but still...they are)
    PElement* getHead()const;
    void setHead(PElement* _head);
    int getPower() const;
    void setPower(int _power);

    //!Each coefficient is shifting upwards
    void shift(int n);
    // Valuation of the polynom
    void valuate(int coef);
    //!A polynomial whose leading coefficientis 1 is called monic
    void makeMonic();
    //!Ben-Or Irreducibility Test
    bool isIrreducible();
    int evaluate(int x);

    //Calculates order of Irreducible polynom
    //returns -1 if Polynom is reducible or f(0) = 0
    int irrPolynomOrder();

    //!Calculates the order of the arbitrary polynomial by its decomposition to irreducibles
    int arbitraryPolynomOrder(std::vector<std::pair<Polynom, int>> polDecomposition);

    //!LCM of given vector numbers
    int LCM(std::vector<int> numbers);
    int gcd(int a, int b);
    std::vector<int> findRoots();
    int findRootNumber();
    //!Find the quotient and remainder A = Q * B + R
    void quot_rem(Polynom& A, Polynom& B, Polynom& Q, Polynom& R);

    /** Polynomial greatest common divisor.
     * Calculate and return a polynomial which is the greatest common divisor of two polynomials.
     *
     * This member function assumes that the degree of the polynomial 'a'
     * is greater than or equal to the degree of the polynomial 'b' (a.power >= b.power).
     * Otherwise, the result is undefined.
     *
     * The returned polynomial (gcd) is monic (i.e. the leading coefficient is equal to 1).
     */
    Polynom gcd(Polynom a, Polynom b);

    //!find X = A^(-1) in field B(p^q)
    Polynom gcdExtended(Polynom A, Polynom B, Polynom& X, Polynom& Y, Polynom& Q);

    /** Copy assignment operator.
     * The copy assignment operator added here to make a deep copy
     * when the "=" is used to assign one instance to another.
     */
    Polynom& operator=(Polynom other);

    /** Polynomial greatest common divisor.
     * Calculate and return a polynomial which is the greatest common divisor of two polynomials.
     *
     * This function does not require the degree of the polynomial 'a' to be greater than or equal
     * to the degree of the polynomial 'b' (a.order >= b.order is not required).
     *
     * The returned polynomial (gcd) is monic (i.e. the leading coefficient is equal to 1).
     */
    friend Polynom GCD(Polynom a, Polynom b);

    //returns factors of the polynomials using Berlekamp's algorithm
    friend std::vector<Polynom> getFactors(Polynom p);

    friend Polynom derivative(Polynom& pol1);
    friend Polynom operator *(Polynom p1, Polynom p2);
    friend Polynom operator -(Polynom p1, Polynom p2);
    friend Polynom operator +(Polynom p1, Polynom p2);
    friend Polynom operator /(Polynom p1, Polynom p2);
    friend Polynom operator %(Polynom p1, Polynom p2);

    //!output polynomial
    friend std::ostream& operator <<(std::ostream& stream, Polynom& polynomial);

    //!equality operators
    friend bool operator ==(Polynom p1, Polynom p2);
    friend bool  operator !=(Polynom p1, Polynom p2);
};

#endif //POLINOMS_POLYNOM_H
