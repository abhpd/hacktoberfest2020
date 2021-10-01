//What is Fast Fourier Transformation and where are we going to use it ??
//FFT allows us to multiply two polynomials of length n in O(nlogn) time,
//which is better than the trivial multiplication which takes O(n^2) time. 

// How FFT is able to multiply large polynomials in O(nlogn) time step by stp break down !!!
// The basic idea of the FFT is to apply divide and conquer. We divide the coefficient vector
//  of the polynomial into two vectors, recursively compute the DFT for each of them, and combine 
// the results to compute the DFT of the complete polynomial.

//Now what the heck is DFT??
//Discrete fourier transfromation(DFT) of the polynomial A(x) (or equivalently the vector 
// of coefficients (a0,a1,…,an−1) is defined as the values of the polynomial at the points x=wn,k,
//  i.e. it is the vector:


//now lets see how we are going to implement it
#include <vector>
#include <complex>
#include <math.h>
#include <iostream>
#define endl '\n'
#define int long long
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(0)
#define base complex<double>
using namespace std;

vector<base> init_omega(int n)
{
    vector<base> omega(n);
    double PI = acos(-1);
    double angle = 2 * (PI / n);
    for (int i = 0; i < n; i++)
    {
        omega[i] = base(cos(angle * i), sin(angle * i));
    }
    return omega;
}
vector<base> fft(vector<base> &a, vector<base> omega)
{
    int n = (int)a.size();
    if (n == 1)
    {
        return a;
    }
    int half = n >> 1; //it is n/2
    vector<base> aeven(half);
    vector<base> aodd(half);
    for (int i = 0, j = 0; i < n; i += 2, j++)
    {
        aeven[j] = a[i];
        aodd[j] = a[i + 1];
    }
    auto yeven = fft(aeven, omega);
    auto yodd = fft(aodd, omega);
    vector<base> y(n);
    for (int i = 0; i < half; i++)
    {
        y[i] = yeven[i] + omega[i] * yodd[i];
        y[i + half] = yeven[i] - omega[i] * yodd[i];
    }
    return y;
}
int32_t main()
{
    fast;
    vector<base> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    vector<base> omega = init_omega(a.size());
    vector<base> y = fft(a, omega);
    for (int i = 0; i < y.size(); i++)
    {
        cout << y[i] << endl;
    }
    return 0;
}

//To understand it more clearly i am attaching some links that can be helpful
//https://cp-algorithms.com/algebra/fft.html
//https://codeforces.com/blog/entry/43499

//:)