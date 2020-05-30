#include <iostream>
#include "Polynom.h"
#include "Field.h"

using std::cout;
using std::cin;
using std::endl;

int main() {

    Polynom f(5, 2, { 1,2,1 });
    Polynom g(5, 2, { 1,3,1 });
    Polynom h(5, 1, { 1,2 });
    Polynom b(5, 1, { 1,1 });
    Polynom zero(5, 0, { 0 });

    cout << "1) f(x) = " << f;
    cout << "f(4) = " << f.evaluate(4) << "\n\n";


    cout << "2) g(x) = " << g;
    cout << "h(4) = " << g.evaluate(4) << "\n\n";


    cout << "3) h(x) = " << h;
    cout << "b(4) = " << h.evaluate(4) << "\n\n";

    cout << "4) b(x) = " << b;
    cout << "b(4) = " << b.evaluate(4) << "\n\n";


    cout << "\n\nMaking polynomial monic\n";
    Polynom e(5, 3, { 1, 3, 5, 5 });
    cout << "e(x) = " << e;
    e.makeMonic();
    cout << "e(x) {monic} = " << e;

    //!before each action, re-declare the variable (for each action - new variable)
    cout << "--------------------------------------------------------------------\n";
    Polynom res = f + g;
    cout << "\nf(x) + g(x) = " << res;


    Polynom d = f * g;
    cout << "f(x) * g(x) = " << d;

    Polynom der1 = derivative(f);
    cout << "f(x)' = " << der1;

    Polynom der2 = derivative(g);
    cout << "g(x)' = " << der2;

    cout << "\nf == h " << bool(f == h) << endl;
    cout << "h(x) = " << h;
    h.shift(5);
    cout << endl;
    cout << "h(x) {shift 5} = " << h;
    cout << "--------------------------------------------------------------------\n";

    cout << "f(x) = " << f;
    cout << "g(x) = " << g;
    Polynom div1 = f / g;
    cout << "f(x) / g(x) = " << div1;

    Polynom div2 = f % g;
    cout << "f(x) % g(x) = " << div2;

    cout << "-------------------------------- GCD ------------------------------\n";

    Polynom p1(2, 7, { 1, 0, 0, 0, 0, 0, 0, 1 });
    Polynom p2(2, 5, { 1, 1, 0, 1, 0, 1 });

    cout << "p1(x) = " << p1;
    cout << "p2(x) = " << p2;
    cout << "gcd(p1, p2) = " << GCD(p1, p2); // 1+x^1

    cout << "---" << endl;

    p1 = Polynom(2, 5, { 1, 1, 0, 0, 0, 1 });
    p2 = Polynom(2, 5, { 1, 0, 0, 1, 1, 1 });

    cout << "p1(x) = " << p1;
    cout << "p2(x) = " << p2;
    cout << "gcd(p1, p2) = " << GCD(p1, p2); // 1+x^2+x^3

    cout << "---" << endl;

    Polynom p3(3, 8, { 1, 0, 1, 1, 0, 2, 0, 0, 1 });
    Polynom p4(3, 6, { 2, 0, 2, 2, 0, 1, 2 });
    cout << "p3(x) = " << p3;
    cout << "p4(x) = " << p4;
    Polynom gcd1 = GCD(p3, p4);
    cout << "gcd(p3, p4) = " << gcd1; // 2+x^2

    cout << "---" << endl;

    cout << "h(x) = " << h;
    cout << "g(x) = " << g;
    Polynom gcd2 = GCD(h, g);
    cout << "gcd(h, g) = " << gcd2; // 1

    cout << "--------------------------------Inverse----------------------------------\n";

    Polynom x(5, 1, { 2,1 }), field(5, 3, { 2,3,0,1 });
    cout << "x = " << x;
    cout << "field = " << field;
    Polynom inv = inverse(x, field);
    cout << "inverse(x, field) = " << inv;

    cout << "--------------------------------------------------------------------\n";

    Polynom pol1(2, 4, { 1,0,0,1,1 });
    cout << "1) pol1(x) = " << pol1;
    cout << "Irreducible : ";
    if (pol1.isIrreducible())
        cout << "Yes\n\n";
    else cout << "No\n\n";

    Polynom pol2(5, 3, { 1,0,1,1 });
    cout << "2) pol2(x) = " << pol2;
    cout << "Irreducible : ";
    if (pol2.isIrreducible())
        cout << "Yes\n\n";
    else cout << "No\n\n";


    Polynom irred(3, 6, { 1, 0, 0, 1, 1, 0, 1 });
    Polynom irred2(3, 2, { 1, 0, 1 });
    Polynom irred3(3, 5, { 1, 0, 1, 1, 1, 3 });
    // Polynom<4> red(2, { 1, 2, 1 });
    // Polynom<4> red2(6, { 1, 1, 3, 0, 3, 0, 1 });

    cout << "\n\n\n";

    cout << "3) irred(x) = " << irred;
    cout << "4) irred2(x) = " << irred2;
    cout << "5) irred3(x) = " << irred3;
    // cout << "6) red(x) = " << red;
    cout << "pol1 Order: " << pol1.irrPolynomOrder() << "\n";
    cout << "pol2 Order: " << pol2.irrPolynomOrder() << "\n";
    cout << "irred Order: " << irred.irrPolynomOrder() << "\n";
    cout << "irred2 Order: " << irred2.irrPolynomOrder() << "\n";
    cout << "irred3 Order: " << irred3.irrPolynomOrder() << "\n";
    // cout << "red Order: " << red.irrPolynomOrder() << "\n";

   

    cout << "--------------------------------Changing field(p)--------------------\n";
    Polynom first(7, 2, {0,1,4}), second(7, 3, { 0,1,4,1});

    cout << first<< second;

    cout << "mod 7\n";
    cout << first + second; cout << endl;

    first.changeField(2); second.changeField(2);

    cout << "mod 2\n";
    cout << first << second;
    cout << first + second;
    cout << "------------------------------------FindRoots----------------------------\n";

    Polynom root1(5, 2, {1,2,1});
    cout << root1;
    cout << "roots: ";
    std::vector<int> rootvec1 = root1.findRoots();
    if (rootvec1.size() == 0) cout << "No roots\n";
    else {
        for (int i(0); i < rootvec1.size(); i++) {
            cout << rootvec1[i] << " ";
        }
        cout << endl;
        cout << root1.findRootNumber() << endl;
    }

    Polynom root2(5, 2, { 1,3,1 });
    cout << root2;
    cout << "roots: ";
    std::vector<int> rootvec2 = root2.findRoots();
    if (rootvec2.size() == 0) cout << "No roots\n";
    else {
        for (int i(0); i < rootvec2.size(); i++) {
            cout << rootvec2[i] << " ";
        }
        cout << endl;
        cout << root2.findRootNumber() << endl;
    }

    Polynom root3(5, 4, { 1,0,0,0,2});
    cout << root3;
    cout << "roots: ";
    std::vector<int> rootvec3 = root3.findRoots();
    if (rootvec3.size() == 0) cout << "No roots\n";
    else {
        for (int i(0); i < rootvec3.size(); i++) {
            cout << rootvec3[i] << " ";
        }
        cout << endl;
        cout << root3.findRootNumber() << endl;
    }

    Polynom root4(5, 3, { 0,2,3,1 });
    cout << root4;
    cout << "roots: ";
    std::vector<int> rootvec4 = root4.findRoots();
    if (rootvec4.size() == 0) cout << "No roots\n";
    else {
        for (int i(0); i < rootvec4.size(); i++) {
            cout << rootvec4[i] << " ";
        }
        cout << endl;
        cout << root4.findRootNumber() << endl;
    }

    Polynom root5(5, 3, { 2,3,3,1 });
    cout << root5;
    cout << "roots: ";
    std::vector<int> rootvec5 = root5.findRoots();
    if (rootvec5.size() == 0) cout << "No roots\n";
    else {
        for (int i(0); i < rootvec5.size(); i++) {
            cout << rootvec5[i] << " ";
        }
        cout << endl;
        cout << root5.findRootNumber() << endl;
    }


    cout << "----------------------------Circular polynom----------------------------\n";


    Field fi(5);
    cout << "n = 6: ";
    cout << fi.buildCircularPolynom(6, 5) << endl;
    cout << "n = 12: ";
    cout << fi.buildCircularPolynom(12, 5) << endl;
    cout << "n = 29: ";
    cout << fi.buildCircularPolynom(29, 5) << endl;
   

    return 0;
}