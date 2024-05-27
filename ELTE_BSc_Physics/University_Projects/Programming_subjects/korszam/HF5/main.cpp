#include "matrix.h"
# include <random>
#include <chrono>




int main(int, char**) {

    std::cout << "\t---TESTING---\n\n";
    std::mt19937_64 gen(42);

    std::uniform_real_distribution<double> distr(100,20);


    int n = 3;
    
    Matrix<double> m1(n, n);
    Matrix<double> m2(n, n);

    std::vector<double> vec_buff1;
    std::vector<double> vec_buff2;

    std::cout << "First matrix :\n";
    for(int i=0; i<n*n; ++i)
    {
        vec_buff1.push_back(distr(gen));
    }
    m1.data = vec_buff1;
    std::cout << m1;
    std::cout << "\n \nSecond matrix :\n";
    for(int i=0; i<n*n; ++i)
    {
        vec_buff2.push_back(distr(gen));
    }
    m2.data = vec_buff2;
    std::cout << m2;

    // MULTIPLICATION AND THE DURATION THEREOF
    Matrix<double> res0;
    auto t1 = std::chrono::high_resolution_clock::now();
    res0 = m1*m2;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();

    std::cout << "\n\n\t---MULTIPLICATION AND THE DURATION THEREOF---\n";

    std::cout << "Result matrix :\n" << res0 << "\n";
    //std::cout << "Multiplication began at : " << t1 << "\n";
    //std::cout << "Multiplication ended at : " << t2 << "\n";
    std::cout << "\nMultiplication ran for " << t << " nanoseconds";




    // GENERATING DATA FOR FITTING
    std::cout << "\n\n\nGenerating data with many different dimensions\n";
    std::cout << "\tFor each N there are 10 attemps";
    std::fstream newfile;
    newfile.open("data.txt",std::ios::out);
    if(newfile.is_open())    
    {
        for(int N = 1; N < 251; N++)
        {
            std::cout << "\nNow running : N = " << N << "\n";
            //std::vector<double> times;
            newfile << N;
            for(int j = 0; j < 10; j++)
            {
                std::vector<double> vec1, vec2;
                for(int i=0; i<N*N; i++)
                {
                    vec1.push_back(distr(gen));
                    vec2.push_back(distr(gen));
                }
                Matrix<double> M1(N, N), M2(N, N);
                M1.data = vec1;
                M2.data = vec2;

                Matrix<double> res;
                auto T1 = std::chrono::high_resolution_clock::now();
                res = M1*M2;
                auto T2 = std::chrono::high_resolution_clock::now();
                auto T = std::chrono::duration_cast<std::chrono::nanoseconds>(T2-T1).count();
                newfile << "\t" << T;
                //std::cout << "\n\nResult matrix :\n" << res << "\n";
                std::cout << "\n\tMultiplication ran for " << T << " nanoseconds";
//                times.push_back(T);
            }

//            int tmin = *std::min_element(times.begin(), times.end());
//            newfile << tmin;
            newfile << "\n";
        }
        newfile.close();
    }






}
