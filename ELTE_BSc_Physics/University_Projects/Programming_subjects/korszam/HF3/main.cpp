#include "vector2.h"





int main(int, char**)
{
    Vector2d<double> a, b, d;
    
    std::cout << "Enter 1st vector :\n";
    std::cin >> a;
    std::cout << "Enter 2nd vector:\n";
    std::cin >> b;

    double c;
    std::cout << "Enter a scalar:\n";
    std::cin >> c;

    


    std::cout << "\n\n\n-----TESTING FUNCTIONS-----\n\n";
    d.x = 6;
    d.y = 11;
    std::cout << "test variable $d$ = " << d << "\n";
    std::cout << "\t ADDITION\n";
    std::cout << "a + b = " << a+b;
    d += a;
    std::cout << "d += a : " << d;
    d += b;
    std::cout << "d += b : " << d;
    std::cout << "\n";

    std::cout << "\t SUBTRACTION\n";
    std::cout << "a - b = " << a-b;
    d -= a;
    std::cout << "d -= a : " << d;
    d -= b;
    std::cout << "d -= b : " << d;
    std::cout << "\n";



    std::cout << "\t MULTIPLICATION BY SCALAR\n";
    std::cout << "c * a = " << c*a;
    std::cout << "a * c = " << a*c;
    std::cout << "c * b = " << c*b;
    std::cout << "b * c = " << b*c;
    std::cout << "a *= c : ";
    a *= c;
    std::cout << a;
    std::cout << "b *= c : ";
    b *= c;
    std::cout << b;
    std::cout << "\n";

    std::cout << "reminder:\n" << "a = " << a << "b = " << b << "\n"; 

    std::cout << "\t DIVISION BY SCALAR\n";
    std::cout << "a / c = " << a/c;
    std::cout << "b / c = " << b/c;
    std::cout << "a /= c : ";
    a /= c;
    std::cout << a;
    std::cout << "b /= c : ";
    b /= c;
    std::cout << b;
    std::cout << "\n";

    std::cout << "\t VECTOR OPERATIONS\n";
    std::cout << "a * b = " << dot(a, b) << "\n";
    std::cout << "length(a) = " << length(a) << "\n";
    std::cout << "sqlength(a) = " << sqlength(a) << "\n";
    std::cout << "normalize(a) = " << normalize(a) << "\n";
    std::cout << "length(b) = " << length(b) << "\n";
    std::cout << "sqlength(b) = " << sqlength(b) << "\n";
    std::cout << "normalize(b) = " << normalize(b) << "\n";


}
