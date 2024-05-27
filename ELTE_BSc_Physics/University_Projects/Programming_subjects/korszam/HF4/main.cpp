#include "matrix.h"


template<typename T>
Matrix<T>& right(Matrix<T> const& asd)
{
    return asd;
}


int main(int, char**)
{
    // TEST DATASET
    Matrix<double> test;
    test.data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    test.N = 3;
    test.M = 3;
    std::vector<double> testvec{10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0};


        std::cout << "\tTESTING CONSTRUCTORS :\n";    

    std::cout << "---DEFAULT CONSTRUCTOR---\n";    
    Matrix<double> mat1;
    // "std::cout <<" wouldn't work now, it relies on non-zero N and M
    std::cout << "mat1.data = " << mat1.data;
    std::cout << "mat1.N = " << mat1.N << "\n";
    std::cout << "mat1.M = " << mat1.M << "\n";

    std::cout << "---CONSTRUCTION BY SIZE---";
    std::cout << "Matrix<double> testx(3, 3) :\n";
    Matrix<double> testx(3, 3);
    std::cout << testx;

    std::cout << "---COPY CONSTRUCTORS---\n";
    std::cout << "--SIMPLE COPY CONSTRUCTORS FOR MATRICES, << OPERATOR OVERLOAD--\n";    
    std::cout << "Matrix<double> mat2(test) :\n";
    Matrix<double> mat2(test);
    std::cout << mat2;
    std::cout << "--SIMPLE COPY CONSTRUCTORS FOR VECTORS--\n";
    std::cout << "Matrix<double> mat3(testvec, test.N, test.M) :\n";
    Matrix<double> mat3(testvec, test.N, test.M);
    std::cout << mat3;

    std::cout << "--COPY= CONSTRUCTORS FOR MATRICES--\n";
    std::cout << "Matrix<double> mat4 = test :\n";
    Matrix<double> mat4 = test;
    std::cout << mat4;

    
        std::cout << "---MOVE CONSTRUCTORS---\n";
    
    std::cout << "--SIMPLE MOVE CONSTRUCTORS FOR MATRICES--\n";
    std::cout << "Matrix<double> mat5(std::move(test5)) :\n";
    Matrix<double> test5 = test;
    Matrix<double> mat5(std::move(test5));
    std::cout << mat5;

    std::cout << "--MOVE= CONSTRUCTORS FOR MATRICES--\n";
    std::cout << "Matrix<double> mat6 = std::move(test6) :\n";
    Matrix<double> test6 = test;
    Matrix<double> mat6  = std::move(test6);
    std::cout << mat6;


        std::cout << "\tTESTING .size() MEMBER FUNCTION :\n";
    
    std::cout << "int len = test.size() : ";
    int len = test.size();
    std::cout << len << "\n";


        std::cout << "\tTESTING INDEXING :\n";

    std::cout << "---1D INDEXING---\n";
    for(int i = 0; i < test.size(); ++i)
    {
        std::cout << "std::cout << test[ " << i << " ] : ";
        std::cout << test[i];
        std::cout << "\n";
    }

    std::cout << "---2D INDEXING---\n";
    for(int i = 0; i < test.N; ++i)
    {
        for(int j = 0; j < test.N; ++j)
        {
            std::cout << "std::cout << test[ " << i << ", " << j << " ] : ";
            std::cout << test(i, j);
            std::cout << "\n";
        }
    }

        std::cout << "\tTESTING OPERATORS:\n";
    
    std::cout << "---ADDITION---\n";
    std::cout << "Matrix<double> a = mat3 + mat2 :\n";
    Matrix<double> a = mat3 + mat2;
    std::cout << a;
    std::cout << "a = mat3 + std::move(mat2) :\n";
    a = mat3 + std::move(mat2);
    std::cout << a;
    std::cout << "a = std::move(mat3) + mat2 :\n";
    a = std::move(mat3) + mat2;
    std::cout << a;
    std::cout << "a = std::move(mat3) + std::move(mat2) :\n";
    a = std::move(mat3) + std::move(mat2);
    std::cout << a;

    std::cout << "---SUBTRACTION---\n";
    std::cout << "Matrix<double> b = mat3 - mat2 :\n";
    Matrix<double> b = mat3 - mat2;
    std::cout << b;
    std::cout << "b = mat3 - std::move(mat2) :\n";
    b = mat3 - std::move(mat2);
    std::cout << b;
    std::cout << "b = std::move(mat3) - mat2 :\n";
    b = std::move(mat3) - mat2;
    std::cout << b;
    std::cout << "b = std::move(mat3) - std::move(mat2) :\n";
    b = std::move(mat3) - std::move(mat2);
    std::cout << b;

    std::cout << "---DIVISION BY SCALAR---\n";
    std::cout << "Matrix<double> c = test / 4 :\n";
    Matrix<double> c = test / 4;
    std::cout << c;
    std::cout << "c = std::move(mat2) / 4 :\n";
    c = std::move(mat2) / 4;
    std::cout << c;

    std::cout << "---MULTIPLICATION BY SCALAR---\n";    
    std::cout << "Matrix<double> d = test * 4 :\n";
    Matrix<double> d = test * 4;
    std::cout << d;
    std::cout << "d = 0.2 * d :\n";
    d = 0.2 * d;
    std::cout << d;
    std::cout << "d = std::move(mat2) * 4 :\n";
    d = std::move(mat2) * 4;
    std::cout << d;
    std::cout << "d = 0.2 * std::move(d) :\n";
    d = 0.2 * std::move(d);
    std::cout << d;


    std::cout << "---MULTIPLICATION---\n";
    std::cout << "Matrix<double> f = test * test :\n";
    Matrix<double> f = test * test;
    std::cout << f;
    std::cout << "f = mat2 * std::move(mat3) :\n";
    f = mat2 * std::move(mat3);
    std::cout << f;
    std::cout << "f = std::move(mat2) * mat3 :\n";
    f = std::move(mat2) * mat3;
    std::cout << f;
    std::cout << "f = std::move(mat2) * std::move(mat3) :\n";
    f = std::move(mat2) * std::move(mat3);
    std::cout << f;






}