#include <iostream>
#include <cmath>




//Find the square root of 'num' by starting the iteration from 'x0'
double sqrt_newton(double num, double x0);


// Newton's method is applicable to real valued functions.
// The problem of finding the root of a real number can be rephrased to fit Newton's method.
// The root problem (x^2 = a) is equivalent to finding the zero of f(x) = x^2 - a
// The most general and efficient solution is to define f(x) and the derivative thereof as inline functions:
// Such that as long as the method is implemented, only the expression f(x) (and f'(x)) would have to be changed for later use.


int N = 5; // number of iterations


inline double f(double x, double a)
{
    return x*x - a;
}
inline double df(double x)
{
    return 2*x;
}

// Here we define the function that implements Newton's method having the same signature as above
double sqrt_newton(double num, double x0)
{
    double x1;

    for(int i = 0; i < N; ++i)
    {
        x1 = x0 - f(x0, num)/df(x0);
        x0 = x1; // every iteration's x0 is the previous iteration's x1
    }

    return x1;
}








int main(int, char**)
{

    double num, x0, result;
    num = 2; // the number we want the square root of
    x0 = 6; // the initial guess for the square root


    result = sqrt_newton(num, x0); // function call and storing the result
    // Note : It's redundant to store the result, it could be passed to std::cout directly.




    std::cout << "The square root of " << num << " after " << N << " iteratons : " << result << "\n";
    std::cout << "The initial guess was " << x0 << "\n";



    return 0;
}
