#include <iostream> 
#include <windows.h> 
using namespace std;
// √a за рекурентною формулою y(n+1) = 1/2 * (y(n) + a / y(n)), y0 = 1
double sqrtIter(const double* a, int* terms)
{
    double y = 1.0;                        // y0
    double diff;
    int n = 0;
    do
    {
        double yNext = 0.5 * (y + *a / y); // рекурентне співвідношення
        diff = fabs(yNext - y);
        y = yNext;
        n++;
    } while (diff > EPS);                  // до заданої точності
    *terms = n;
    return y;
}

void calcY(const double* x, double* y, double* st, double* err, int* terms, bool* defined)
{
    *defined = true;

    if (*x >= 1 && *x <= 2)                // y = sqrt(15 - x^2)
    {
        double a = 15.0 - (*x) * (*x);
        *y = sqrtIter(&a, terms);
        *st = sqrt(a);
    }
    else if (*x >= -1 && *x < 1 && (*x) + (*x) * (*x) > 0)   // y = 1/sqrt(x + x^2)
    {
        double a = (*x) + pow(x, 2);
        *y = 1.0 / sqrtIter(&a, terms);
        *st = 1.0 / sqrt(a);
    }
    else
    {
        *defined = false;
        return;
    }
    *err = fabs(*st - *y);
}