// Main.cpp

// include necessary files
#include "BaseOption.hpp"
#include "EuropeanOption.hpp"
#include <vector>
#include <iomanip>	// Manipulate the output format
#include <iostream>
using namespace std;

/*
Data sets:
Batch 1: T = 0.25, K = 65, sig = 0.30, r = 0.08, S = 60 (then C = 2.13337, P = 5.84628). 
Batch 2: T = 1.0, K = 100, sig = 0.2, r = 0.0, S = 100 (then C = 7.96557, P = 7.96557). 
Batch 3: T = 1.0, K = 10, sig = 0.50, r = 0.12, S = 5 (C = 0.204058, P = 4.07326). 
Batch 4: T = 30.0, K = 100.0, sig = 0.30, r = 0.08, S = 100.0 (C = 92.17570, P = 1.24750).
*/

int main()
{   //cout << setprecision(9);		// Display as many as 9 digits
	// question (a) and (b)
	// Batch 1 data:
	cout << "Testing..... (a) and (b)" << endl;
	cout << "batch 1......" << endl;
	double T = 0.25;		// Expiry date
	double K = 65;		// Strike price
	double sig = 0.30;		// Volatility
	double r = 0.08;		// Interest rate
	double S = 60;		// Current stock price
	double b = r;		// Cost of carry
	int type = 1;	// Option type (1 for call, -1 for put)

	// create an object of european option
	EuropeanOption* option = new EuropeanOption(T, K, sig, r, S, b, type);	// Use pointer
	// Calcualte the price of the call option since type = 1
	cout << "Call option price: " << option->Price() << endl;
	option->toggle();	// Toggle the option type
	// Calcualte the price of the put option
	cout << "Put option price: " << option->Price() << endl;
	// calculate the price of the option using put-call parity
	cout << "Option price dervied from put call parity: " << option->Put_Call_Parity() << endl;
	// check put-call parity satisfaction
	cout << "Put call parity check (1: hold, 0: not hold): " << option->Check_Parity() << endl;
	delete option;

	// Batch 2 data:
	cout << endl << "batch 2......" << endl;
	T = 1.0;		// Expiry date
	K = 100;		// Strike price
	sig = 0.2;		// Volatility
	r = 0.0;		// Interest rate
	S = 100;		// Current stock price
	b = r;		// Cost of carry
	type = 1;	// Option type (1 for call, -1 for put)

	// create an object of european option
	option = new EuropeanOption(T, K, sig, r, S, b, type);	// Use pointer
	// Calcualte the price of the call option since type = 1
	cout << "Call option price: " << option->Price() << endl;
	option->toggle();	// Toggle the option type
	// Calcualte the price of the put option
	cout << "Put option price: " << option->Price() << endl;
	// calculate the price of the option using put-call parity
	cout << "Option price dervied from put call parity: " << option->Put_Call_Parity() << endl;
	// check put-call parity satisfaction
	cout << "Put call parity check (1: hold, 0: not hold): " << option->Check_Parity() << endl;
	delete option;

	// Batch 3 data:
	cout << endl << "batch 3......" << endl;
	T = 1;		// Expiry date
	K = 10.0;		// Strike price
	sig = 0.5;		// Volatility
	r = 0.12;		// Interest rate
	S = 5.0;		// Current stock price
	b = r;		// Cost of carry
	type = 1;	// Option type (1 for call, -1 for put)

	// create an object of european option
	EuropeanOption option1(T, K, sig, r, S, b, type);	// Not use pointer
	// Calcualte the price of the call option since type = 1
	cout << "Call option price: " << option1.Price() << endl;
	option1.toggle();	// Toggle the option type
	// Calcualte the price of the put option
	cout << "Put option price: " << option1.Price() << endl;
	// calculate the price of the option using put-call parity
	cout << "Option price dervied from put call parity: " << option1.Put_Call_Parity() << endl;
	// check put-call parity satisfaction
	cout << "Put call parity check (1: hold, 0: not hold): " << option1.Check_Parity() << endl;

	// Batch 4 data:
	cout << endl << "batch 4......" << endl;
	T = 30.0;		// Expiry date
	K = 100.0;		// Strike price
	sig = 0.30;		// Volatility
	r = 0.08;		// Interest rate
	S = 100.0;		// Current stock price
	b = r;		// Cost of carry
	type = 1;	// Option type (1 for call, -1 for put)

	// create an object of european option
	option1.SetParameters(T, K, sig, r, S, b, type);	// Not use pointer
	// Calcualte the price of the call option since type = 1
	cout << "Call option price: " << option1.Price() << endl;
	option1.toggle();	// Toggle the option type
	// Calcualte the price of the put option
	cout << "Put option price: " << option1.Price() << endl;
	// calculate the price of the option using put-call parity
	cout << "Option price dervied from put call parity: " << option1.Put_Call_Parity() << endl;
	// check put-call parity satisfaction
	cout << "Put call parity check (1: hold, 0: not hold): " << option1.Check_Parity() << endl;

	// question(c)
	cout << endl << "Testing question c using batch 4 call with S starting from 0" << endl;

	S = 0;		// Set the starting price
	option = new EuropeanOption(T, K, sig, r, S, b, type);	// Right now the parameters hold batch 4 data with S = 0

	int range = 20;		// Monotonically increase range of S by a number
	option->Mesh_Price(range);			// Calculate and display the option prices of a option matrix
	delete option;


	// question (d)
	cout << endl << "Testing question d..." << endl;
	const int size = 7;		// specify the array size for parameters, aka the number of option parameters to input
	// Create an array for easy input. The input orders are: T, K, sigma, r, S, b, type(1 for call, -1 for put)
	double parameter_matrix[][size] = { { 0.25,		65,		0.3,	0.08,	60,		0.08,	1 },		// batch 1
										{ 1,		100,	0.2,	0,		100,	0,		1 },	// batch 2
										{ 1,		10,		0.5,	0.12,	5,		0.12,	-1 },		// batch 3
										{ 30,		100,	0.3,	0.08,	100,	0.08,	-1 }		// batch 4
										// batch 5...
										// batch 6...
										// Can input as many options as the user wants
										//
									};

	option = new EuropeanOption;
	// Store the array of array in a vector of vector for further modification
	vector<vector<double>> option_matrix = option->matrix_function(parameter_matrix, size);

	// Can add more rows at run time
	int more_rows = 2;	// For example, add 2 more rows at run time
	option->Add_more_options(option_matrix, size, more_rows);

	// Display the mesh option prices
	option->Mesh_Price(option_matrix);
	delete option;

	// Option Sensitivities, aka the Greeks
	cout << endl << "Part 2: Option Sensitivities, aka the Greeks" << endl;

	// Question (a)
	cout << endl << "Testing question a..." << endl;
	K = 100;
	S = 105;
	T = 0.5;
	r = 0.1;
	b = 0;
	sig = 0.36;
	type = 1;
	
	option = new EuropeanOption(T, K, sig, r, S, b, type);
	// Calcualte the delta of the call option
	cout << "Call option delta: " << option->Delta() << endl;
	// Calcualte the gamma of the call option
	cout << "Call option gamma: " << option->Gamma() << endl;
	option->toggle();		// Toggle the option type
	// Calcualte the delta of the put option
	cout << "Put option delta: " << option->Delta() << endl;
	// Calcualte the gamma of the call option
	cout << "Put option gamma: " << option->Gamma() << endl;
	
	// Question (b)
	// right now the option object holds question (a) data for put since I didn't delete it above.
	// and right now S = 105, range =20
	cout << endl << "Testing question b using question (a) data put option with S = 105, range =20..." << endl;
	option->Mesh_Delta(range);			// Display the price of the option matrix
	delete option;

// Question (c)
	cout << endl << "Testing question c..." << endl;

	option = new EuropeanOption;
	option->Mesh_Delta(option_matrix);			// Display the delta of the option matrix
	option->Mesh_Gamma(option_matrix);			// Display the gamma of the option matrix
	delete option;

// Question (d)
	cout << endl << "Testing question d..." << endl;
	double h = 0.000005;		// Set the value of h

	option = new EuropeanOption(T, K, sig, r, S, b, type);
	// Calcualte the approximated delta of the call option
	cout << "Approximate call option delta: " << option->Delta(h) << endl;
	// Calcualte the approximated gamma of the call option
	cout << "Approximate call option gamma: " << option->Gamma(h) << endl;
	option->toggle();		// Toggle the option type
	// Calcualte the approximated delta of the put option
	cout << "Approximate put option delta: " << option->Delta(h) << endl;
	// Calcualte the approximated gamma of the put option
	cout << "Approximate put option gamma: " << option->Gamma(h) << endl;

	// right now the option object holds question (a) data for call.
	// and right now S = 105, range =20
	cout << endl << "Testing question d using question (a) data put option with S = 105, range =20..." << endl;
	option->Mesh_Delta(range, h);			// Display the approximated price of the option matrix
	delete option;

	return 0;
}
	
