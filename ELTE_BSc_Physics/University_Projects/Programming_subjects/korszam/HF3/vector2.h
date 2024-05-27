#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <string>
#include <string.h>



template<typename T>
struct Vector2d
{
    T x, y;




    Vector2d& operator+=( Vector2d const& v )
        {
            x += v.x;
            y += v.y;
            return *this;
        }

    Vector2d& operator-=( Vector2d const& v )
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }
    
    Vector2d& operator*=( T const& v )
        {
            x = x*v;
            y = y*v;
            return *this;
        }
    
    Vector2d& operator/=( T const& v )
        {
            x = x/v;
            y = y/v;
            return *this;
        }


};

// OVERLOADING STD OPERATOR "<<" FOR Vector2d VARIABLES
template<typename T>
std::istream& operator>>( std::istream& i, Vector2d<T>& v )
{
    i >> v.x;
    i >> v.y;
    return i;
}



// OVERLOADING STD OPERATOR "<<" FOR Vector2d VARIABLES
template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2d<T> const& v )
{
    o << "{ " << v.x << ", " << v.y << " }\n";
    return o;
}



// OVERLOADING OPERATOR "-"
// VECTOR SUBTRACTION
template<typename T>
Vector2d<T> operator-(const Vector2d<T> &a, const Vector2d<T> &b)
{
    Vector2d<T> c;
    c.x = a.x-b.x;
    c.y = a.y-b.y;
    return c;
}



// OVERLOADING OPERATOR "-"
// VECTOR ADDITION
template<typename T>
Vector2d<T> operator+(const Vector2d<T> &a, const Vector2d<T> &b)
{
    Vector2d<T> c;
    c.x = a.x+b.x;
    c.y = a.y+b.y;
    return c;
}




// OVERLOADING OPERATOR "*"
// MULTIPLICATION OF Vector2d BY SCALAR
template<typename T, typename W>
Vector2d<T> operator*(const Vector2d<T>& a, const W& c)
{
    Vector2d<T> b;
    b.x = c * a.x;
    b.y = c * a.y;
    return b;
}
template<typename T, typename W>
Vector2d<T> operator*(const W& c, const Vector2d<T>& a)
{
    Vector2d<T> b;
    b.x = c * a.x;
    b.y = c * a.y;
    return b;
}



// OVERLOADING OPERATOR "/"
// DIVISION OF Vector2d BY SCALAR
template<typename T, typename W>
Vector2d<T> operator/(const Vector2d<T>& a, const W& c)
{
    Vector2d<T> b;
    b.x = a.x / c;
    b.y = a.y / c;
    return b;
}


// DOT PRODUCT FOR Vector2d
template<typename T, typename W>
double dot(Vector2d<T> const& a, Vector2d<W> const& b)
{
    return a.x*b.x + a.y*b.y;
}

// LENGTH OF Vector2d
template<typename T>
double length(Vector2d<T> const& a)
{
    return sqrt( a.x*a.x + a.y*a.y );
}


// LENGTH SQUARED OF Vector2d
template<typename T>
double sqlength(Vector2d<T> const& a)
{
    return a.x*a.x + a.y*a.y;
}


// NORMALIZING FUNCTION FOR Vector2d
template<typename T>
Vector2d<T> normalize(Vector2d<T> const& a)
{
    return a/sqrt( a.x*a.x + a.y*a.y );
}