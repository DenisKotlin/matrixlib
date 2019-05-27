#ifndef MATRIX_H
#define MATRIX_H

// Denis Pokidov 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>

class size_or_loc // size_or_loc (line, column) of an element in a matrix;
{
public:
	int lin; // line
	int col; // column
	size_or_loc(int line = 0, int column = 0) // Default constructor
	{
		lin = line;
		col = column;
	}
	bool operator == (size_or_loc &loc) const;
	bool operator != (size_or_loc &loc) const;
};

class matrix
{
	// Element of a matrix as ordinary fraction;
	int num; // numerator
    int den; // denominator
	//int size; // size of a matrix
	static matrix det; // determinant of a matrix;
	void zero_above(const size_or_loc &diag); // This function by means of arithmetic operations (addition and subtraction) does equal to zero all elements located above the top-left element of the current submatrix;
	void zero_below(const size_or_loc &diag); // This function by means of arithmetic operations (addition and subtraction) does equal to zero all elements located under the top-left element of the current submatrix;
	size_or_loc get_nonzero(); // This function searches for the first nonzero element in an initial submatrix and transfers his coordinates (number of a line and number of a column) to the following function;
	void set_at_one(const size_or_loc &diag); // This function set at one the current diagonal element of the given matrix;
	static bool check_right(char *ifname = "input.txt"); // This function return TRUE if contents of input text file are right and FALSE otherwise;
public:
	// Default constructor
	matrix(int numerator = 0, int denominator = 1) : num(numerator),den(denominator){}; 
	//~matrix(); // Destructor function;
	int get_num() const // get a numerator
	{	return num;	}
	int get_den() const // get a denominator
	{	return den;	}
	void set_num(int numerator) // set a numerator
	{	num = numerator;	}
	void set_den(int denominator) // set a denominator
	{	den = denominator;	}
	size_or_loc size(char *ifname = "input.txt");
	bool is_identical(matrix *mtx_ptr); //
	void print(char *ofname = "output.txt"); // This function print a fraction; 
	void print_all(char *ofname = "output.txt"); // This function print a matrix; 
	bool readfile(char *ifname = "input.txt"); // This function read out a matrix from a text file;
	matrix reduce(); // This function reduces fractions, after operations of addition and multiplication, used by other function;
	matrix* reduce_all(); // This function reduces fractions (each element of the current submatrix), after operations of addition and multiplication, used by other function;
    void swap_lines(size_or_loc &loc_line1, int num_line2 ); //This function interchanges the position of sublines at the current submatrix; 
    void swap_lines(int num_line1, int num_line2 ); //This function interchanges the position of lines at the current submatrix; 
	void swap_columns(size_or_loc &loc_col1, int num_col2 ); //This function interchanges the position of subcolumns at the current submatrix;
	void swap_columns(int num_col1, int num_col2 ); //This function interchanges the position of columns at the current submatrix;
	matrix triangle(bool print_details = false); // This function lead the current matrix to a triangular kind and return its determinant;
	void gauss(bool print_details = false); // this function solve a current matrix with the Gauss's algorithm;
	bool operator == (const matrix &mtx) const;
	bool operator != (const matrix &mtx) const;
	bool operator < (const matrix &mtx) const;
	bool operator > (const matrix &mtx) const;
	bool operator >= (const matrix &mtx) const;
	bool operator <= (const matrix &mtx) const;
	bool operator == (const long &lng) const;
	bool operator != (const long &lng) const;
	bool operator < (const long &lng) const;
	bool operator > (const long &mlng) const;
	bool operator >= (const long &lng) const;
	bool operator <= (const long &lng) const;
	bool operator ! () const;
    matrix operator - () const;
	matrix operator + (const matrix &mtx) const;
	matrix operator + (const long &addlong) const;
	matrix operator - (const matrix &mtx) const;
	matrix operator - (const long &subtrlong) const;
	matrix operator * (const matrix &mtx) const;
	matrix operator * (const long &multlong) const;
	matrix operator / (const matrix &mtx) const;
	matrix operator / (const long &divlong) const;
	matrix operator % (const matrix &mtx) const;
	matrix operator % (const long &divlong) const;
	matrix operator += (const matrix &mtx);
	matrix operator += (const long &addlong);
	matrix operator -= (const matrix &mtx);
	matrix operator -= (const long &subtrlong);
	matrix operator *= (const matrix &mtx);
	matrix operator *= (const long &multlong);
	matrix operator /= (const matrix &mtx);
	matrix operator /= (const long &divlong);
	matrix operator ++ (int); //postfix increment
	matrix operator ++ (); //prefix increment
	matrix operator -- (int); //postfix decrement
	matrix operator -- (); //prefix decrement
	friend std::istream& operator >> (std::istream&, matrix&);
};

# endif
