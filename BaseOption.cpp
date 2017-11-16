// BaseOption.cpp

#include "BaseOption.hpp"

BaseOption::BaseOption() {}	// Default constructor

BaseOption::BaseOption(const BaseOption& obj) {}	// Copy constructor

BaseOption::~BaseOption() {}		// Destructor

BaseOption& BaseOption::operator = (const BaseOption& obj)		// Assignment Operator
{
	if (this == &obj) return *this;

	return *this;
}

// Add more options at run time
void BaseOption::Add_more_options(vector<vector<double>>& option_mesh, int size, int more_rows)		// Function to add more options at run time
{
	double parameter;	// For parameter input
	vector<double> row;	// A vector to store the input

	cout << "Add " << more_rows << " more options (rows). Input the parameters in this order below:"
		 << endl << "T, K, sigma, r, S, b, type(1 for call, -1 for put)"
		 << endl << "Use ENTER or SPACE to seperate parameters. Use ENTER to finish one line input."  << endl;

	for(int i=0; i < more_rows; i++)
	{
		cout << "Add option " << i+1 << ": ";

		for(int j=0; j < size; j++)
		{
			cin >> parameter;
			row.push_back(parameter);
		}

		option_mesh.push_back(row);
		row.clear();
	}
}