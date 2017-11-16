// BaseOption.hpp

// provide bass formula and data for the derived class, such as europearn option for code resuability and simplicity

// check if not defined to prevent multidefintion

#ifndef BaseOption_HPP
#define BaseOption_HPP

// include necessary files
#include <vector>
#include <iostream>
using namespace std;

// declare class
class BaseOption
{
public:
	// Constructors and destructor
	BaseOption();							// Default constructor
	BaseOption(const BaseOption& obj);	// Copy constructor
	virtual ~BaseOption();			// Destructor

	// Assignment Operator
	BaseOption& operator = (const BaseOption& obj);

	// Overloaded functions that return one option price
	virtual double Price() = 0;
	virtual double Price(int U) = 0;

	// Overloaded functions that return a matrix of option prices
	virtual void Mesh_Price(int range) = 0; // present the vectior of price based on different S value
	virtual void Mesh_Price(const vector<vector<double>>& mesh) = 0; // get the price based on parameter input matrix

	// A vector to store the array input for further modification(e.g., add more rows)
	template <size_t rows, size_t cols>
	vector<vector<double>> matrix_function(double (&array)[rows][cols], int size);

	// Add more options at run time
	void Add_more_options(vector<vector<double>>& option_mesh, int size, int more_rows);	// Function to add more options at run time
};

// A vector to store the array input for further modification(e.g., add more rows)
template <size_t rows, size_t cols>
inline vector<vector<double>> BaseOption::matrix_function(double (&array)[rows][cols], int size)
{
	vector<vector<double>> parameter_matrix;	// Create a vector of vector
	vector<double> row;		// Create an empty row

	// loop through the matrix by using inner for loop
	for (unsigned int i = 0; i < sizeof(array) / sizeof(double) / size; i++)	// equivalent to i < number of rows of the 2D array
	{
		for (int j = 0; j < size; j++) // loop through different colon
			row.push_back(array[i][j]);		// for each particular row

		parameter_matrix.push_back(row);	// Store a row in the 2d vector
		row.clear(); // clear row 
	}

	return parameter_matrix;
}

#endif