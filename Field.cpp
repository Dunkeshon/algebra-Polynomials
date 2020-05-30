#include "Field.h"

Field::Field() {};
Field::Field(int p) {};

int Field::mobius(int n)
{
    if (n == 1)
        return 1;

    int m = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && isPrime(i)) {
            if (n % (i * i) == 0)
                return 0;
            else
                m++;
        }
    }
    return (m % 2 != 0) ? -1 : 1;
}

Polynom Field::buildCircularPolynom(int n, int p)
{
    Polynom one(p, 0, { 1 }); //1
    std::vector<int> dividers; //��������
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

