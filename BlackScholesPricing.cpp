#define _USE_MATH_DEFINES
#include<iostream>
#include<cmath>
using namespace std;

int x = 1 

double CDF(double); // function declaration – takes 1 real i.e. RV X
double delta(double);

int main()
{
    double Option_Call, d1, d2, Option_Put, Put_Price_PutCallParity, Option_Call_Delta;
    double S = 100, E = 100, r = 0.05, vol = 0.2, tau = 1.0; //tau=time to expiry

    d1 = (log(S / E) + (r + 0.5 * vol * vol) * tau) / (vol * sqrt(tau));
    d2 = d1 - vol * sqrt(tau);

    Option_Call = S * CDF(d1) - E * exp(-r * tau) * CDF(d2);
    cout << "Call Option price is: " << Option_Call <<endl;

    Option_Put = E * exp(-r * tau) * CDF(-d2) - S * CDF(-d1);
    cout << "Put Option price is: " << Option_Put <<endl;

    Put_Price_PutCallParity = Option_Call - S + (E*exp(-r*tau));
    cout << "Put Option price under put call parity is: " << Put_Price_PutCallParity <<endl;

    Option_Call_Delta = delta(d1);
    cout << "Delta for call option is: " << Option_Call_Delta <<endl;


    return 0;
}

/* Now define the function */
double CDF(double X)
{
    const double a1 = 0.319381530, a2 = -0.356563782, a3 = 1.781477937,
    a4 = -1.821255978, a5 = 1.330274429;

    double x = 0, k = 0; //always good to initialise variables

    double N, CDF, n;

    x = fabs(X);
    k = 1 / (1 + 0.2316419 * x);
    n = (1 / sqrt(2 * M_PI)) * exp(-0.5 * x * x);
    N = 1 - n * (a1 * k + a2 * k * k + a3 * pow(k, 3) + a4 * pow(k, 4) + a5
    * pow(k, 5));
    if (X >= 0)
    CDF = N;
    else
    CDF = 1 - N;
    return CDF;
}

double delta(double u)
{   
    double cdf = 0.5 * erfc(-u / sqrt(2));
    return cdf ;
}