// EuropeanOption.hpp

// check if not defined to prevent multidefintion

#ifndef EuropeanOption_HPP
#define EuropeanOption_HPP

// include necessary files
#include "BaseOption.hpp"
#include <vector>
#include <iostream>
using namespace std;

// declare class
class EuropeanOption: public BaseOption
{
private:
	// declare data member
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	double b;		// Cost of carry
	double S;		// Current stock price
	int optType;	// Option name (call, put)

	// Gaussian functions
	double n(double x); // PDF
	double N(double x); // CDF

	// 'Kernel' functions to calculate option price and sensitivities
	double CallPrice();
	double PutPrice();
	double CallDelta();	// delta of european call option
	double PutDelta();
	double CallGamma();
	double PutGamma();

	// 'Kernel' functions to calculate option price with a given S
	double CallPrice(double U);
	double PutPrice(double U);
	double CallDelta(double U);
	double PutDelta(double U);

public:
	EuropeanOption();							// Default contructor, default is call option
	EuropeanOption(double date, double strike, double sigma, double rate, double s, double carry, int type);	// Set the option
	EuropeanOption(const EuropeanOption& option2);	// Copy constructor
	virtual ~EuropeanOption();			// Destructor

	// Assignment Operator
	EuropeanOption& operator = (const EuropeanOption& option2);

	// Functions to return option price and sensitivities
	virtual double Price();
	virtual double Price(int U);	// return option price with a given S 
	double Delta();
	double Delta(int U);		// return option delta with a given S
	double Gamma();

	// Approximate option sensitivities using divided differences
	double Delta(double h);	// return delta
	double Gamma(double h);	// return gamma
	double Delta(int U, double h);	// return delta given S

	// Put-Call Parity
	double Put_Call_Parity(); // get the option price according to put call parity 
	bool Check_Parity(); // set a tolerance and check if it satisfies put call parity
	
	// Ouput an matrix of option prices or sensitivities
	virtual void Mesh_Price(int range);		// Calculate and display the option prices of monotonically increasing range of S
	void Mesh_Delta(int range);				// Calculate and display the option delta of monotonically increasing range of S
	void Mesh_Delta(int range, double h);	// Use divided differences to approximate option delta of monotonically increasing range of S
	virtual void Mesh_Price(const vector<vector<double>>& mesh);	// Calculate and display the option prices of an option matrix
	void Mesh_Delta(const vector<vector<double>>& mesh);			// Calculate and display the option delta of an option matrix
	void Mesh_Gamma(const vector<vector<double>>& mesh);			// Calculate and display the option gamma of an option matrix

	// Modifier functions
	void toggle();		// Change option type (C/P, P/C)
	void SetParameters(double date, double strike, double sigma, double rate, double s, double carry, int type);	// Set option parameters
};

#endif