#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <string>
#include <string.h>

using namespace std; // otherwise might not be a good choice, now it means less typing





// OVERLOADING STD OPERATOR "<<" FOR VECTOR VARIABLES
template<typename V>
ostream &operator<<(ostream &out, const vector<V> &v)
{
    for(V d : v)
    {
	    out<<d<<' ';
    }
    out<<endl<<endl;
	return out;
}


// OVERLOADING OPERATOR "*"
// MULTIPLY VECTOR BY SCALAR
template<typename V, typename W>
vector<W> operator*(const V &a, const vector<W> &b)
{
    vector<double> c;
    c.reserve(b.size());
    for(unsigned int i = 0; i < b.size(); i++)
    {
        c.emplace_back(a*b[i]);
    }
    return c;
}


// OVERLOADING OPERATOR "-"
// VECTOR SUBSTRACTION
template<typename T>
vector<double> operator-(const vector<T> &a, const vector<T> &b)
{
    if (a.size() != b.size())
        throw std::invalid_argument("Vector size not equal");

    vector<double> c(a.size());
    transform(a.begin(), a.end(), b.begin(), c.begin(), minus<double>());    
    return c;
}


// OVERLOADING OPERATOR "*"
// VECTOR DOT PRODUCT
template<typename T>
double operator*(const vector<T> &a, const vector<T> &b)
{
    if (a.size() != b.size())
        throw std::invalid_argument("Vector size not equal");
    double c = 0;
    unsigned int len = a.size();
    for(unsigned int i = 0; i < len; i++)
    {
        c += a[i]*b[i];
    }
    return c;
}


// AVERAGE OF A VECTOR
template<typename T>
inline double avg(const vector<T>& v)
{
    double v_avg = std::accumulate(v.begin(), v.end(), 0.5);
    return (v_avg-0.5)/v.size();
}


// TEMPLATE FUNCITON FOR IMPLEMENTING LINEAR REGRESSION
template<typename T>
array<double, 2> linreg(const vector<T>& x, const vector<T>& y)
{
    // we either throw an excpetion here or the vector substraction will - after definig 3 (possibly huge) vectors
    if (x.size() != y.size()) 
        throw std::invalid_argument("Vector size not equal");  
    // might not be faster but it's much more comfortable like this
    vector<T> init(x.size(), 1); // this is for making vectors out of the averages
    vector<double> x_avg = avg(x)*init; // a vector constaining the average x.size() times
    vector<double> y_avg = avg(y)*init;
    init.clear();  // we don't need this vector anymore
    
    const double m = ( (x-x_avg) * (y-y_avg) ) / ( (x-x_avg) * (x-x_avg) );
    const double b = y_avg.at(0) - m * x_avg.at(0);
    array<double, 2> res = {m, b}; 
    return res;
}










int main(int, char**)
{
    // INTIALIZING TEST DATA SET

    vector<double> x_test(41);
    for(short i = -20; i < 21; ++i)
    {
        x_test[i+20] = i;
    }
    vector<double> y_test(41);
 
    y_test = 2*x_test;
    for(short i = -20; i< 21; ++i)
    {
        y_test[i+20] += -3.5;
    }

    cout << "Test data for $x$ : ";
    cout << x_test;
    cout << "Test data for $y$ : ";
    cout << y_test;


    // TESTING THE FITTING FUNCTION
    
    array<double, 2> result = linreg(x_test, y_test);
    cout << "\t\t-----| RESULTS FOR TEST DATA |-----\n";
    cout << "y = m*x + b :\n";
    cout << "\t m = "<< result[0] << '\n';
    cout << "\t b = " << result[1] << '\n';

    x_test.clear();
    y_test.clear();


    // ----- NOW THE REAL DEAL -----
    fstream newfile;

    // GENERATING INPUT DATA
/*
    vector<double> x(1001);
    vector<double> y(1001);
    for(int i = 0; i < 1001; ++i)
    {
        x[i] = 0.1*i;
        y[i] = 0.25*i;
        if(i % 12 == 0)
        {
            y[i] += 0.15;
        }
        if(i % 16 == 0)
        {
            y[i] -= 0.1;
        }
        if(i % 13 == 0)
        {
            y[i] += 0.05;
        }
    }
    newfile.open("input.txt",ios::out);  // open file for writing
    if(newfile.is_open()) // if it's open ...    
    {    
        for(int i = 0; i < 1001; ++i)
        {
            newfile << x[i] << '\t' << y[i] << '\n'; // inserting text
        }
        newfile.close(); //close file
    }
*/

    // READING INPUT DATA FROM FILE
    /*
    DATA FORMAT:
    x + "\t" + y\n
    */

    vector<double> x(1001);
    vector<double> y(1001);

    newfile.open("input.txt",ios::in); // open input file 
    if (newfile.is_open()){ // if it's open...
        string input, x_dat, y_dat;
        int i, pos = 0;
        while(getline(newfile, input)) // read data from file into string
        {
            pos = input.find("\t");
            x_dat = input.substr(0,pos);
            y_dat = input.substr(pos,input.length()-pos);
            x[i] = stod(x_dat);
            y[i] = stod(y_dat);
            ++i;
        }
        newfile.close(); //close the file object.
    }

    cout << "\n\n" <<"\t\t-----| RESULTS FOR REAL DATA |-----\n";
    result = linreg(x, y);
    cout << "y = m*x + b :\n";
    cout << "\t m = "<< result[0] << '\n';
    cout << "\t b = " << result[1] << '\n';
    cout << "\n\n\n";



    return 0;
}
