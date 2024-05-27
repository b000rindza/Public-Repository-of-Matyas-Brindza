#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <exception>

/* 
TODO :
    - throwing exceptions
    - operators for rewriting values - similar to the vector based constructors in the comments
    - contruction of matrices with lambda functions
*/



template<typename T>
class Matrix
{
    public :

        int N, M;
        std::vector<T> data;
        
        // DEFAULT CONSTRUCTOR
        Matrix() : data{0.0}, N{0}, M{0}
        {}
        
        // CONSTRUCTION BY SIZE
        Matrix(const int N_, int const M_)
        {
            std::vector<T> buffer(N_*M_, 0); // not so well optimized

            data = buffer;
            N = N_;
            M = M_;
        }

                ////  CONSTRUCTORS  ////
            // in the case of these constructors, the underlying working principle is self-explanatory

        
            // "COPY" CONSTRUCTORS


        // SIMPLE COPY CONSTRUCTORS FOR MATRICES
        Matrix(Matrix<T>&  cp)
        {
            if((cp.N==0) || (cp.M==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                data = cp.data;
                N = cp.N;
                M = cp.M;
            }
        }
        

        // SIMPLE COPY CONSTRUCTORS FOR VECTORS
        Matrix(std::vector<T>const& cp, const int N_, int const M_)
        {
            if((N_==0) || (M_==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                data = cp;
                N = N_;
                M = M_;
            }
        }
        /*
        Matrix(std::vector<T>const& cp)
        {
            if((N==0) || (M==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                data = cp;
            }

        }
        */

        // COPY= CONSTRUCTORS FOR MATRICES
        Matrix<T>& operator=(Matrix<T> const& cp)
        {
            if(&cp == this){ return *this; }
            if((cp.N==0) || (cp.M==0))
            {
                throw "Please enter valid matrix dimensions!\n";
            }
            else
            {
                data = cp.data;
                N = cp.N;
                M = cp.M;
                return *this;
            }
        }


        // COPY= CONSTRUCTORS FOR VECTORS
/*        Matrix<T>& operator=(std::vector<T> const& cp)
        {   
          if((N==0) || (M==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                data = cp;
                return *this;
            }

        }
 */       
        
        
        
        
            // "MOVE" CONSTRUCTORS
        
        // SIMPLE MOVE CONSTRUCTORS FOR MATRICES
        Matrix(Matrix<T>&& mv)
        {
            if((mv.N==0) || (mv.M==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                std::swap(data, mv.data);
                std::swap(N, mv.N);
                std::swap(M, mv.M);
            }
        }


        // SIMPLE MOVE CONSTRUCTORS FOR VECTORS
        Matrix(std::vector<T>&& mv, int N_, int M_)
        {
            if((N_==0) || (M_==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                std::swap(data, mv);
                N = N_;
                M = M_;
            }
        }
/*        Matrix(std::vector<T>&& mv, int&& N_, int&& M_)
        {
            if((N_==0) || (M_==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                std::swap(data, mv);
                std::swap(N, N_);
                std::swap(M, M_);
            }
        }
 */
/*
        Matrix(std::vector<T>&& mv)
        {
            if((N==0) || (M==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                std::swap(data, mv);
            }
        }
*/

        // MOVE= CONSTRUCTORS FOR MATRICES
        Matrix<T>& operator=(Matrix<T>&& mv)
        {
            if(&mv == this){ return *this; }
            /*
            if((mv.N==0) || (mv.M==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                std::swap(data, mv.data);
                std::swap(N, mv.N);
                std::swap(M, mv.M);
                return *this;
            }
            */
            std::swap(data, mv.data);
            std::swap(N, mv.N);
            std::swap(M, mv.M);
            return *this;

        }


        // MOVE= CONSTRUCTORS FOR VECTORS
/*        Matrix<T>& operator=(std::vector<T>&& mv)
        {   
            if((N==0) || (M==0))
            {
                std::cout << "Please enter valid matrix dimensions!\n";
            }
            else
            {
                data = mv;
                return *this;
            }
        }
*/


                ////  INDEXING  ////
        // 1D INDEXING
        T& operator[]( int i ) { return data[i]; }
        T const& operator[]( int i ) const { return data[i]; }


        // 2D INDEXING
        T& operator()( int i, int j ){ return data[N*i+j]; }
        T const& operator()(int i, int j )const{ return data[N*i+j]; }




                ////  FUNCTIONS  ////
                
        int size()
        {
            return N*M;
        }        


};







// OVERLOADING STD OPERATOR "<<" FOR Matrix VARIABLES
template<typename T>
std::ostream& operator<<( std::ostream& o, Matrix<T> const& a )
{   
    o << "data :\n";
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            o << a.data.at(i*a.M + j) << "\t";
        }
        o << "\n";
    }
    o << "N : " << a.N << "\nM : " << a.M << "\n";
    return o;
}

// OVERLOADING STD OPERATOR "<<" FOR std::vector<T> VARIABLES
template<typename T>
std::ostream& operator<<( std::ostream& o, std::vector<T> const& v )
{
    o << "{  ";
    for(auto i : v)
    {
        o << i << "  ";
    }
    o << "}\n";

    return o;
}


// OVERLOADING OPERATOR "+"
// MATRIX ADDITION
template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) + b(i, j);
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator+(const Matrix<T> &&a, const Matrix<T> &b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) + b(i, j);
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &&b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) + b(i, j);
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator+(const Matrix<T> &&a, const Matrix<T> &&b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) + b(i, j);
        }
    }
    return c;
}


// OVERLOADING OPERATOR "-"
// MATRIX ADDITION
template<typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) - b(i, j);
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator-(const Matrix<T> &&a, const Matrix<T> &b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) - b(i, j);
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &&b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) - b(i, j);
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator-(const Matrix<T> &&a, const Matrix<T> &&b)
{
    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            c(i, j) += a(i, j) - b(i, j);
        }
    }
    return c;
}


// OVERLOADING OPERATOR "/"
// DIVISION OF Matrix BY SCALAR
template<typename T, typename W>
Matrix<T> operator/(const Matrix<T>& a, const W& c)
{
    Matrix<T> b(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            b(i, j) += a(i, j) / c;
        }
    }
    return b;
}
template<typename T, typename W>
Matrix<T> operator/(const Matrix<T>&& a, const W& c)
{
    Matrix<T> b(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            b(i, j) += a(i, j) / c;
        }
    }
    return b;
}


// OVERLOADING OPERATOR "*"
// MULTIPLICATION OF Matrix BY SCALAR
template<typename T, typename W>
Matrix<T> operator*(const Matrix<T>& a, const W& c)
{
    Matrix<T> b(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            b(i, j) += a(i, j) * c;
        }
    }
    return b;
}
template<typename T, typename W>
Matrix<T> operator*(const W& c, const Matrix<T>& a)
{
    Matrix<T> b(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            b(i, j) += a(i, j) * c;
        }
    }
    return b;
}
template<typename T, typename W>
Matrix<T> operator*(const Matrix<T>&& a, const W& c)
{
    Matrix<T> b(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            b(i, j) += a(i, j) * c;
        }
    }
    return b;
}
template<typename T, typename W>
Matrix<T> operator*(const W& c, const Matrix<T>&& a)
{
    Matrix<T> b(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < a.M; ++j)
        {
            b(i, j) += a(i, j) * c;
        }
    }
    return b;
}



// OVERLOADING OPERATOR "*"
// MATRIX MULTIPLICATION
template<typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    double buffer;

    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < b.M; ++j)
        {
            buffer = 0;
            for(int k = 0; k < a.M; ++k)
            {
                buffer += a(i, k) * b (k, j);
            }
            c(i, j) = buffer;
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator*(const Matrix<T> &&a, const Matrix<T> &b)
{
    double buffer;

    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < b.M; ++j)
        {
            buffer = 0;
            for(int k = 0; k < a.M; ++k)
            {
                buffer += a(i, k) * b (k, j);
            }
            c(i, j) = buffer;
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &&b)
{
    double buffer;

    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < b.M; ++j)
        {
            buffer = 0;
            for(int k = 0; k < a.M; ++k)
            {
                buffer += a(i, k) * b (k, j);
            }
            c(i, j) = buffer;
        }
    }
    return c;
}
template<typename T>
Matrix<T> operator*(const Matrix<T> &&a, const Matrix<T> &&b)
{
    double buffer;

    Matrix<T> c(a.N, a.M);
    for(int i = 0; i < a.N; ++i)
    {
        for(int j = 0; j < b.M; ++j)
        {
            buffer = 0;
            for(int k = 0; k < a.M; ++k)
            {
                buffer += a(i, k) * b (k, j);
            }
            c(i, j) = buffer;
        }
    }
    return c;
}




