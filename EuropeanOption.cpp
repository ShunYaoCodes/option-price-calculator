//EuropeanOption.cpp

// include necessary files
#include "EuropeanOption.hpp"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>
using namespace boost::math;

// Gaussian functions
double EuropeanOption::n(double x)	 // PDF
{// pdf
	normal_distribution<> myNormal(0.0, 1.0); 
	return pdf(myNormal, x);
}

double EuropeanOption::N(double x) // CDF
{ // cumulative normal distribution
	normal_distribution<> myNormal(0.0, 1.0); 
	return cdf(myNormal, x);
}

// 'Kernel' functions to calculate option price and sensitivities
double EuropeanOption::CallPrice()
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (S * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));
}

double EuropeanOption::PutPrice()
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T)* N(-d2)) - (S * exp((b-r)*T) * N(-d1));
}

double EuropeanOption::CallDelta()
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * N(d1);
}

double EuropeanOption::PutDelta()
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(S/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * (N(d1) - 1.0);
}

double EuropeanOption::CallGamma() 
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(S/K) + (b + (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return ( n(d1) * exp((b-r)*T) ) / (S * tmp);
}

double EuropeanOption::PutGamma() 
{
	return CallGamma();
}

// 'Kernel' functions to calculate option price with a given S
double EuropeanOption::CallPrice(double U)
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (U * exp((b-r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));
}

double EuropeanOption::PutPrice(double U)
{
	double tmp = sig * sqrt(T);
	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T)* N(-d2)) - (U * exp((b-r)*T) * N(-d1));
}

double EuropeanOption::CallDelta(double U)
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * N(d1);
}

double EuropeanOption::PutDelta(double U)
{
	double tmp = sig * sqrt(T);

	double d1 = ( log(U/K) + (b+ (sig*sig)*0.5 ) * T )/ tmp;

	return exp((b-r)*T) * (N(d1) - 1.0);
}

///////////////////////////////////////////////////////

// b = r: Black and Scholes stock option model (1973)
EuropeanOption::EuropeanOption() : BaseOption(), T(0.25), K(65.0), sig(0.3), r(0.08), S(60), b(r), optType(1) {}	// Default constructor, default is call option

EuropeanOption::EuropeanOption(double date, double strike, double sigma, double rate, double s, double carry, int type)
	: BaseOption(), T(date), K(strike), sig(sigma), r(rate), S(s), b(carry), optType(type) {}			// Set the option

EuropeanOption::EuropeanOption(const EuropeanOption& option2) : BaseOption(option2)
{ // Copy constructor
	r = option2.r;
	sig = option2.sig;
	K = option2.K;
	T = option2.T;
	b = option2.b;
	S = option2.S;
	optType = option2.optType;
}

EuropeanOption::~EuropeanOption() {}		// Destructor

EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option2)		// Assignment Operator
{
	if (this == &option2) return *this;
	
	BaseOption::operator = (option2);

	r = option2.r;
	sig = option2.sig;
	K = option2.K;
	T = option2.T;
	b = option2.b;
	S = option2.S;
	optType = option2.optType;

	return *this;
}

// Functions to return option price and sensitivities
double EuropeanOption::Price()
{
	if (optType == 1)
		return CallPrice();
	else
		return PutPrice();
}

double EuropeanOption::Price(int U)	// return option price with a given S 
{
	if (optType == 1)
		return CallPrice(U);
	else
		return PutPrice(U);
}

double EuropeanOption::Delta()
{
	if (optType == 1)
		return CallDelta();
	else
		return PutDelta();
}

double EuropeanOption::Delta(int U)		// return option delta with a given S
{
	if (optType == 1)
		return CallDelta(U);
	else
		return PutDelta(U);
}

double EuropeanOption::Gamma()  
{
	if (optType == 1)
		return CallGamma();
	else
		return PutGamma();
}

// Approximate option sensitivities using divided differences
double EuropeanOption::Delta(double h)	// return delta
{
	if (optType == 1)
		return (CallPrice(S + h) - CallPrice(S - h)) / (2.0*h);
	else
		return (PutPrice(S + h) - PutPrice(S - h)) / (2.0*h);
}

double EuropeanOption::Gamma(double h)	// return gamma
{
	if (optType == 1)
		return (CallPrice(S + h) - 2 * CallPrice(S) + CallPrice(S - h)) / (h*h);
	else
		return (PutPrice(S + h) - 2 * PutPrice(S) + PutPrice(S - h)) / (h*h);
}

double EuropeanOption::Delta(int U, double h)	// return delta given S
{
	if (optType == 1)
		return (CallPrice(U + h) - CallPrice(U - h)) / (2.0*h);
	else
		return (PutPrice(U + h) - PutPrice(U - h)) / (2.0*h);
}

// Put-Call Parity
// get the option price according to put call parity
double EuropeanOption::Put_Call_Parity()
{
	if (optType == 1)
		return  CallPrice() + K*exp(-r*T) - S;
	else
		return  PutPrice() + S - K*exp(-r*T);
}

// set a tolerance and check if it satisfies put call parity
bool EuropeanOption::Check_Parity()
{
	double tol = 1e-10;

	return abs(PutPrice() + S - CallPrice() - K*exp(-r*T)) < tol;
}

// Ouput an matrix of option prices or sensitivities
// Calculate and display the option prices of monotonically increasing range of S
void EuropeanOption::Mesh_Price(int range)
{
	//creat a vector to hold the price
	vector<double> Mesh_price;

	// loop through to get the S within the range
	for (int i = int(S); i <= S + range; i++)
		Mesh_price.push_back(Price(i));

	// loop to display the price
	for (unsigned int i = 0; i < Mesh_price.size(); i++)
		cout << "underlying price: "<<S+i<<", "<<"option price: "<< Mesh_price[i] << endl;
}

// Calculate and display the option delta of monotonically increasing range of S
void EuropeanOption::Mesh_Delta(int range)
{
	//creat a vector to hold the price
	vector<double> Mesh_delta;

	// loop through to get the S within the range
	for (int i = int(S); i <= S + range; i++)
		Mesh_delta.push_back(Delta(i));

	// loop to display the price
	for (unsigned int i = 0; i < Mesh_delta.size(); i++)
		cout << "underlying price: "<<S+i<<", "<<"option delta: "<< Mesh_delta[i] << endl;
}

// Use divided differences to approximate option delta of monotonically increasing range of S
void EuropeanOption::Mesh_Delta(int range, double h)
{
	//creat a vector to hold the price
	vector<double> Mesh_delta;

	// loop through to get the S within the range
	for (int i = int(S); i <= S + range; i++)
		Mesh_delta.push_back(Delta(i, h));

	// loop to display the price
	for (unsigned int i = 0; i < Mesh_delta.size(); i++)
		cout << "underlying price: "<<S+i<<", "<<"approximated option delta: "<< Mesh_delta[i] << endl;
}

// Calculate and display the option prices of an option matrix
void EuropeanOption::Mesh_Price(const vector<vector<double>>& mesh)
{

	vector<double> mesh_prices;
	// loop through
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		T = mesh[i][0];
		K = mesh[i][1];
		sig = mesh[i][2];
		r = mesh[i][3];
		S = mesh[i][4];
		b = mesh[i][5];
		optType = (int)mesh[i][6];

		mesh_prices.push_back(this->Price());
	}

	for (unsigned int i = 0; i < mesh_prices.size(); i++)
		// display the price of each option
		cout << "Option " << i + 1 << " price: " << mesh_prices[i] << endl;
}

// Calculate and display the option delta of an option matrix
void EuropeanOption::Mesh_Delta(const vector<vector<double>>& mesh)
{
	vector<double> mesh_delta;
	// loop through
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		T = mesh[i][0];
		K = mesh[i][1];
		sig = mesh[i][2];
		r = mesh[i][3];
		S = mesh[i][4];
		b = mesh[i][5];
		optType = (int)mesh[i][6];

		mesh_delta.push_back(Delta());
	}

	for (unsigned int i = 0; i < mesh_delta.size(); i++)
		// display the price of each option
		cout << "Option " << i + 1 << " delta: " << mesh_delta[i] << endl;
}

// Calculate and display the option gamma of an option matrix
void EuropeanOption::Mesh_Gamma(const vector<vector<double>>& mesh)
{
	vector<double> mesh_gamma;
	// loop through
	for (unsigned int i = 0; i < mesh.size(); i++)
	{
		T = mesh[i][0];
		K = mesh[i][1];
		sig = mesh[i][2];
		r = mesh[i][3];
		S = mesh[i][4];
		b = mesh[i][5];
		optType = (int)mesh[i][6];

		mesh_gamma.push_back(Gamma());
	}

	for (unsigned int i = 0; i < mesh_gamma.size(); i++)
		// display the price of each option
		cout << "Option " << i + 1 << " gamma: " << mesh_gamma[i] << endl;
}

// Modifier functions
void EuropeanOption::toggle()		// Change option type (C/P, P/C)
{ // Change option type (C/P, P/C)

	if (optType == 1)
		optType = -1;
	else
		optType = 1;
}

// Set option parameters
void EuropeanOption::SetParameters(double date, double strike, double sigma, double rate, double s, double carry, int type)
{
	T = date;
	K = strike;
	sig = sigma;
	r = rate;
	S = s;
	b = carry;
	optType = type;
}	