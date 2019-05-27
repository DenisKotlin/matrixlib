#include "stdafx.h"
#include "matrix.h"

std::ifstream inputf;
std::ofstream outputf;
bool size_or_loc::operator == (size_or_loc &loc) const
{
	return (this->lin == loc.lin && this->col == loc.col);
}

bool size_or_loc::operator != (size_or_loc &loc) const
{
	return !(*this == loc);
}

/*matrix::matrix(int numerator, int denominator) // Constructor function
{
	num = numerator;
	den = denominator;
}
*/
bool matrix::operator == (const matrix &mtx) const
{
	matrix mtx1 = *this, mtx2 = mtx;
	mtx1.reduce();  mtx2.reduce();
	return (mtx1.num == mtx2.num && mtx1.den == mtx2.den);
}

bool matrix::operator == (const long &lng) const
{
	matrix mtx(lng), mtx1 = *this, mtx2 = mtx;
	mtx1.reduce();  mtx2.reduce();
	return (mtx1.num == mtx2.num && mtx1.den == mtx2.den);
}

bool matrix::operator != (const matrix &mtx) const
{
	return !(*this == mtx);
}

bool matrix::operator != (const long &lng) const
{
	matrix mtx(lng);
	return !(*this == mtx);
}

bool matrix::operator < (const matrix &mtx) const
{
	matrix res = *this - mtx;
	res.reduce();
	if (res.num < 0)
		return true;
	else
		return false;
}

bool matrix::operator < (const long &lng) const
{
	matrix mtx(lng), res = *this - mtx;
	res.reduce();
	if (res.num < 0)
		return true;
	else
		return false;
}

bool matrix::operator > (const matrix &mtx) const
{
	matrix res = *this - mtx;
	res.reduce();
	if (res.num > 0)
		return true;
	else
		return false;
}

bool matrix::operator > (const long &lng) const
{
	matrix mtx(lng), res = *this - mtx;
	res.reduce();
	if (res.num > 0)
		return true;
	else
		return false;
}

bool matrix::operator <= (const matrix &mtx) const
{
	return ((*this < mtx)||(*this == mtx));
}

bool matrix::operator <= (const long &lng) const
{
	matrix mtx(lng);
	return ((*this < mtx)||(*this == mtx));
}

bool matrix::operator >= (const matrix &mtx) const
{
	return ((*this > mtx)||(*this == mtx)); 
}

bool matrix::operator >= (const long &lng) const
{
	matrix mtx(lng);
	return ((*this > mtx)||(*this == mtx));
}

bool matrix::operator ! () const
{
	return (this->num == 0);
}
matrix matrix::operator - () const
{
	matrix res = *this;
	res.num = - res.num;
	return res;
}

matrix matrix::operator - (const matrix &mtx) const
{
	matrix dif;
	dif.num = this->num * mtx.den - mtx.num * this->den;
    dif.den = this->den * mtx.den;
	return dif.reduce();
}

matrix matrix::operator - (const long &subtrlong) const
{
	matrix dif = *this, subtr(subtrlong);
	dif -= subtr; 
	return dif.reduce();
}

matrix matrix::operator + (const matrix &mtx) const
{
	matrix dif;
	dif.num = this->num * mtx.den + mtx.num * this->den;
    dif.den = this->den * mtx.den;
	return dif.reduce();
}

matrix matrix::operator + (const long &addlong) const
{
	matrix dif = *this, add(addlong);
	dif += add; 
	return dif.reduce();
}

matrix matrix::operator * (const matrix &mtx) const
{
	matrix mult;
	mult.num = this->num * mtx.num;
	mult.den = this->den * mtx.den;
	return mult.reduce();
}

matrix matrix::operator * (const long &multlong) const
{
	matrix multiplied = *this, mult(multlong);
	multiplied *= mult;
	return multiplied.reduce();
}

matrix matrix::operator / (const matrix &mtx) const
{
	matrix quot;
	quot.num = this->num * mtx.den;
	quot.den = this->den * mtx.num;
	return quot.reduce();
}

matrix matrix::operator / (const long &divlong) const
{
	matrix divided = *this, divider(divlong);
	return (divided /= divider).reduce();
}

matrix matrix::operator % (const matrix &mtx) const
{
	matrix integer = (*this / mtx); 
	return (*this - mtx * (integer.num / integer.den)).reduce();
}

matrix matrix::operator % (const long &divlong) const
{
	matrix divider(divlong), integer = (*this / divider);
	return  (*this - divider * (integer.num / integer.den)).reduce();
}

matrix matrix::operator += (const matrix &mtx)
{
	*this = *this + mtx;
	return this->reduce();
}

matrix matrix::operator += (const long &addlong)
{
	matrix add(addlong);
	*this = *this + add;
	return this->reduce();
}

matrix matrix::operator -= (const matrix &mtx)
{
	*this = *this - mtx;
	return this->reduce();
}

matrix matrix::operator -= (const long &subtrlong)
{
	matrix dif(subtrlong);
	*this = *this - dif;
	return this->reduce();
}

matrix matrix::operator *= (const matrix &mtx)
{
	*this = *this * mtx;
	return this->reduce();
}

matrix matrix::operator *= (const long &multlong)
{
	matrix mult(multlong);
	*this = *this * mult;
	return this->reduce();
}

matrix matrix::operator /= (const matrix &mtx)
{
	*this = *this / mtx;
	return this->reduce();
}

matrix matrix::operator /= (const long &divlong)
{
	matrix divided(divlong);
	*this = *this / divided;
	return this->reduce();
}

matrix matrix::operator ++ (int)
{
	matrix mtx = *this, add(1);
	*this += add;
	return mtx.reduce();
}

matrix matrix::operator ++ ()
{
	matrix add(1);
	*this += add;
	return this->reduce();
}

matrix matrix::operator -- (int)
{
	matrix mtx = *this, subtr(1);
	*this -= subtr;
	return mtx.reduce();
}

matrix matrix::operator -- ()
{
	matrix subtr(1);
	*this -= subtr;
	return this->reduce();
}

std::ostream& operator << (std::ostream &ostr, const matrix &mtx)
{
	return ostr << mtx.get_num() << '/' << mtx.get_den() << std::endl;
}
std::istream& operator >> (std::istream &istr, matrix &mtx)
{
	return istr >> mtx.num >> mtx.den;
}
bool operator == (const long &lng, const matrix &mtx)
{
	return mtx == lng;
}

bool operator != (const long &lng, const matrix &mtx)
{
	return mtx != lng;
}

bool operator > (const long &lng, const matrix &mtx)
{
	return mtx < lng;
}

bool operator < (const long &lng, const matrix &mtx)
{
	return mtx > lng;
}

bool operator >= (const long &lng, const matrix &mtx)
{
	return mtx <= lng;
}

bool operator <= (const long &lng, const matrix &mtx)
{
	return mtx >= lng;
}

matrix operator + (const long &lng, const matrix &mtx)
{
	matrix add(lng);
	return (add + mtx).reduce();
}

matrix operator - (const long &lng, const matrix &mtx)
{
	matrix dif(lng);
	return (dif - mtx).reduce();
}

matrix operator * (const long &lng, const matrix &mtx)
{
	matrix mult(lng);
	return (mult * mtx).reduce();
}

matrix operator / (const long &lng, const matrix &mtx)
{
	matrix divided(lng);
	return (divided / mtx).reduce();
}

matrix operator % (const long &lng, const matrix &mtx)
{
	matrix divided(lng);
	return (divided % mtx).reduce();
}

matrix operator += (const long &lng, const matrix &mtx)
{
	matrix add(lng);
	return (add += mtx).reduce();
}

matrix operator -= (const long &lng, const matrix &mtx)
{
	matrix dif(lng);
	return (dif -= mtx).reduce();
}

matrix operator *= (const long &lng, const matrix &mtx)
{
	matrix mult(lng);
	return (mult *= mtx).reduce();
}

matrix operator /= (const long &lng, const matrix &mtx)
{
	matrix divided(lng);
	return (divided /= mtx).reduce();
}


bool matrix::check_right(char *ifname) // This function return TRUE if contents of input text file are right and FALSE otherwise
{
	bool is_right;
	std::ifstream inputf;
	do
	{
		is_right = true;
		try
		{
			inputf.open(ifname);
			if (!inputf.fail())  
			{
				std::string line; // current line in text file
				std::string number;
				bool is_first_line = true; // this variable is check whether line is first
				unsigned int lineCounter = 0;
				unsigned int amountFirst = 0, amountLast = 0; // amount of integer words in first line and amount of integer words in last line (compare with a first line)
				while ((is_right)&&(std::getline(inputf, line)))
				{
					lineCounter++;
					amountLast = 0; 
					size_t pos = 0, curpos;
					size_t len = line.length();
					line.push_back(' ');
					while((is_right)&&(pos <= len)) // while line is non finished
					{
						curpos = line.find(' ',pos);
						if (curpos > pos) // found an integer word
						{
							is_first_line ? amountFirst++ : amountLast++;
							number = line.substr(pos,curpos - pos); // extract an integer word;
							// check to right of integer word
							size_t incorrect_pos; // position of incorrect character in an integer word
							if ((number[0]=='-')||(number[0]=='+')) 
							{
								if ((incorrect_pos = number.substr(1,number.length()-1).find_first_not_of("0123456789"))>=0) incorrect_pos++;
							}
							else
								incorrect_pos = number.find_first_not_of("0123456789");
							if (incorrect_pos >= 0) 
							{ 
								is_right = false; 
								std::cerr << "\a\r\nERROR! 'check_right()': error in " << lineCounter << " line and " << pos + incorrect_pos + 1 << " position!\r\n" << std::endl;
								throw "error";
							}
							pos = curpos;
						}
						else pos++;
					}
					// if amountLast == 0 consequently line is empty or line is first
					if ((is_right)&&(amountLast > 0)&&(amountLast != amountFirst)) 
					{
						is_right = false; 
						std::cerr << "\a\r\nERROR! 'check_right()': amount of integer words in line " << lineCounter << " unequal to amount of integer words in first line.\r\n" << std::endl;
						throw "error";
					}
					is_first_line = false;
				}
			}
			else 
			{
				is_right = false;
				std::cerr << "\a\r\nERROR! 'matrix::check_right()': file not found.\r\n";
				throw "error";
			}
			inputf.close();
		}
		catch(...)
		{
			inputf.close();
			std::cout << "\r\nCorrect the input file and save it.(type 'c' to continue or other to exit).\r\n";
			char ok;
			std::cin >> ok;
			if (ok != 'c') exit(-1);
		}
	}while(!is_right);
	return is_right;
}
size_or_loc matrix::size(char *ifname)
{
	size_or_loc size;
	if (check_right())
	{	
		std::ifstream inputf;
		inputf.open(ifname);
		int nstr = 0, ncol = 0;
		if (!inputf.fail())  
		{
			std::string line;
			// amount of columns
			size_t pos = 0, curpos;
			if (std::getline(inputf,line))
			{
				nstr++; 
				size_t len = line.length();
				line.push_back(' ');
				while( pos <= len )
				{
					curpos = line.find(' ',pos);
					if (curpos > pos)
					{
						ncol++;
						pos = curpos;
					}
					else pos++;
				}
			}
			// amount of strings 
			while (std::getline(inputf, line))
			{
				pos = line.find_first_of("0123456789");
				if (pos >= 0) nstr++;
			}
			size.lin = nstr/2;
			size.col = ncol;
		}
		else std::cerr << "\a\r\nERROR! 'matrix::size()': file not found.\r\n";
		inputf.close();
	}
	else 
	{
		std::cerr << "\a'size' function: Current text file is contain an incorrected characters!\r\n" << std::endl;
		//terminate();
	}
	return size;
} // end of size();

bool matrix::readfile(char *ifname) // This function read out a matrix from a text file
{
	bool goodfile = false;
	matrix *currentp = this;
	size_or_loc sz = currentp->size();
	if (1/*right condition*/)
	{
		goodfile = true;
		inputf.open(ifname);
		for (int i = 0, j; i < sz.lin * sz.col; i += sz.col)
		{
			for (j = 0; j < sz.col; j++) inputf >> (currentp + i + j)->num;
			for (j = 0; j < sz.col; j++) inputf >> (currentp + i + j)->den;
		}
		inputf.close();
	}
	else std::cerr << "\afile is fail!\r\n" << std::endl;
	return goodfile;
} // end of readfile();
void matrix::print(char *ofname) // This function prints a fraction 
{
	matrix *currentp = this;
	std::ofstream outputf(ofname);
	currentp->reduce(); // reduce fraction
	std::cout << currentp->num << "/" << currentp->den <<std::endl;
	outputf << currentp->num << "/" << currentp->den <<std::endl;
	outputf.close();
} // end of print();

void matrix::print_all(char *ofname) // This function print the current matrix 
{
	std::ofstream outputf(ofname);
	matrix *currentp = this;
	currentp->reduce_all(); // reduce all fractions at the current matrix
	size_or_loc size = currentp->size();

	std::cout << std::endl;
	outputf   << std::endl;
	for (int i = 0, j; i < size.lin * size.col; i += size.col)
	{
		for (j = 0; j < size.col; j++)
		{
			std::cout << std::setw(4) << (currentp + i + j)->num << ' ';
			outputf   << std::setw(4) << (currentp + i + j)->num << ' ';
		}
		std::cout << std::endl;
		outputf   << std::endl;
		for (j = 0; j < size.col; j++)
		{
			std::cout << std::setw(4) << (currentp + i + j)->den << ' ';
			outputf   << std::setw(4) << (currentp + i + j)->den << ' ';
		}
		std::cout << std::endl << std::endl;
		outputf   << std::endl << std::endl;
	}
	outputf.close();
} // end of print_all();

matrix matrix::reduce() // This function reduces fractions, after operations of addition and the multiplication, used in a triangle function
{
	matrix *currentp = this;
	bool reduced;
	if (!currentp->num) currentp->den = 1;
    if (currentp->den < 0)
	{
		currentp->num = -(currentp->num);
        currentp->den = -(currentp->den);
	}
	int initDev;
    if ( abs(currentp->num) < abs(currentp->den) )
		initDev = currentp->num;
    else
		initDev = currentp->den;
    reduced = false;
	int p = abs(initDev);
	while ((p > 1)&&(!reduced))
	{
		if ((!(currentp->num % p))&&(!(currentp->den % p)))
		{
			(currentp->num) /= p;
			(currentp->den) /= p;
			reduced = true;
		}
		p--;
	}
	return *currentp;
} // end of reduce();

matrix* matrix::reduce_all() // This function reduces fractions (each element of the current submatrix), after operations of addition and the multiplication, used in a triangle function
{
	matrix *currentp = this;
	size_or_loc size = currentp->size();
	for (int i = 0, j; i < size.lin * size.col; i += size.col)
	{
		for (j = 0; j < size.col; j++) (currentp + i + j)->reduce();
		for (j = 0; j < size.col; j++) (currentp + i + j)->reduce();
	}
	return currentp;
} //end of reduce_all();

size_or_loc matrix::get_nonzero() //This function searches for the first nonzero element in an initial submatrix and transfers his coordinates (number of a line and number of a column) to the following function  
{
	matrix *currentp = this;
	size_or_loc size = currentp->size();
	size_or_loc nz(-1,-1);
	static size_or_loc diag(-1,-1);
	diag.lin = ++diag.col;
	for (int i = diag.lin; (i < size.lin)&&(nz.lin == -1); i++)
	{
		if ((currentp + i*size.col + diag.col)->num)
		{
			nz.lin = i; 
			nz.col = diag.col;
		}
	}
	if (nz.lin != nz.col) currentp->swap_lines(nz, nz.col);
	return nz;
} //end of get_nonzero();

void matrix::set_at_one(const size_or_loc &diag) // This function pays the current diagonal element of the given matrix in the one;
{
	matrix *currentp = this;
	size_or_loc size = currentp->size();
	matrix reverse = 1 / *(currentp + diag.lin * size.col + diag.col);
    for (int j = diag.col; j < size.col; j++)
        (*(currentp + diag.lin*size.col + j) *= reverse).reduce();
} // end of set_at_one();

void matrix::swap_columns(int num_col1, int num_col2 ) //This function interchanges the position columns of the current submatrix 
{
	size_or_loc loc_col1(0, num_col1);
	swap_columns(loc_col1, num_col2);
} // end of swap_columns(); 

void matrix::swap_columns(size_or_loc &loc_col1, int num_col2 ) //This function interchanges the position subcolumns of the current submatrix 
{
	det.num = -det.num;
	matrix *currentp = this;
	size_or_loc size = currentp->size();
	if ((loc_col1.lin >= size.lin)||(loc_col1.col >= size.col)||
		(loc_col1.lin < 0)||(loc_col1.col < 0)||
		(num_col2 >= size.col)||(num_col2 < 0))
	{
		std::cerr << "\a\r\nERROR! 'matrix::swap_columns()': out of range.\r\n";
	}
    for (int i = loc_col1.lin; i < size.lin; i++)
	{
		std::swap((currentp + i*size.col + loc_col1.col)->num, (currentp + i*size.col + num_col2)->num);
		std::swap((currentp + i*size.col + loc_col1.col)->den, (currentp + i*size.col + num_col2)->den);
		// column of nonzero element = line of zero element (for triangle function);
	}
	loc_col1.col = loc_col1.lin;
} // end of swap_columns(); 

void matrix::swap_lines(int num_line1, int num_line2 ) //This function interchanges the position lines of the current submatrix 
{
	size_or_loc loc_line1(num_line1, 0);
	swap_lines(loc_line1, num_line2);
} // end of swap_lines(); 

void matrix::swap_lines(size_or_loc &loc_line1, int num_line2 ) //This function interchanges the position sublines of the current submatrix 
{
	det.num = -det.num;
	matrix *currentp = this;
	size_or_loc size = currentp->size();
	if ((loc_line1.lin >= size.lin)||(loc_line1.col >= size.col)||
		(loc_line1.lin < 0)||(loc_line1.col < 0)||
		(num_line2 >= size.col)||(num_line2 < 0))
	{
		std::cerr << "\a\r\nERROR! 'matrix::swap_lines()': out of range.\r\n";
	}
    for (int j = loc_line1.col; j < size.col; j++)
	{
		std::swap((currentp + num_line2 * size.col + j)->num, (currentp + loc_line1.lin * size.col + j)->num);
		std::swap((currentp + num_line2 * size.col + j)->den, (currentp + loc_line1.lin * size.col + j)->den);
		// column of nonzero element = line of zero element (for triangle function);
	}
	loc_line1.lin = loc_line1.col;
} // end of swap_lines(); 

void matrix::zero_above(const size_or_loc &diag) // This function with means of the arithmetic operations (addition and subtraction) does equal to zero all elements located above the top-left element of the current submatrix;
{
	matrix *currentp = this;
	size_or_loc size = currentp->size();
    matrix transit, subtract;
	for (int i = diag.lin - 1; i > -1; i--)
	{
		transit = *(currentp + i*size.col + diag.col) / *(currentp + diag.lin*size.col + diag.col);
		for (int j = diag.col; j < size.col; j++)
		{
            subtract = *(currentp + diag.lin*size.col + j) * transit;
			//subtraction of fractions;
			*(currentp + i*size.col + j) -= subtract;
		}
	}
	currentp->reduce_all(); // reduction of the fraction in the whole matrix after the arithmetic operations;
} //end of zero_above();

void matrix::zero_below(const size_or_loc &diag) // This function with means of the arithmetic operations (addition and subtraction) does equal to zero all elements located under the top-left element of the current submatrix;
{
	matrix *currentp = this;
	size_or_loc size = currentp->size();
    matrix transit, subtract;
	for (int i = diag.lin + 1; i < size.lin; i++)
	{
		transit = *(currentp + i*size.col + diag.col) / *(currentp + diag.lin*size.col + diag.col);
        for (int j = diag.col; j < size.col; j++)
		{
            subtract = *(currentp + diag.lin*size.col + j) * transit;
			//subtraction of fractions;
			*(currentp + i*size.col + j) -= subtract;
		}
	}
	currentp->reduce_all(); // Reduction of the fraction after the arithmetic operations;
} //end of zero_below();

matrix matrix::triangle(bool print_details) // This function lead the current matrix to a triangular kind and return its determinant;
{
	det = 1; // initialize the determinant of the current matrix
	matrix *currentp = this;
	size_or_loc size = currentp->size();
	if (size.lin == size.col) // is the current matrix square?
	{
		size_or_loc diag;
		int i = 0;
		for (i = 0; i < size.col; i++)
		{
			diag = get_nonzero();
			if (diag.lin == -1) break;
		    currentp->zero_below(diag);
			if (print_details) currentp->print_all();
		}
		// calculate the determinant;
		for (i = 0; i < size.col; i++)
			det *= *(currentp + i*size.col + i);
		det.reduce();
	}
	else
	{
		std::cerr << "\aERROR! 'matrix::triangle()' : the current matrix is not square.\r\n" << std::endl;
		terminate();
	}
	return det;
} // end of triangle();

void matrix::gauss(bool print_details) // this function solve a current matrix with the Gauss's algorithm;
{
	matrix *currentp = this;
	size_or_loc diag; // the location of a diagonal element at the current matrix
	size_or_loc size = currentp->size(); // the size of the current matrix
	for (int i = 0; i < size.col; i++)
	{
		diag = get_nonzero();
		if (diag.lin == -1) break; // this case matrix no contain nonzero elements at the diagonal; 
		currentp->set_at_one(diag);
	    currentp->zero_below(diag);
		if (print_details) currentp->print_all();
		currentp->zero_above(diag);
		if (print_details) currentp->print_all();
	}
}
bool matrix::is_identical(matrix *mtx_ptr) // This function allows to avoid a conclusion of current matrixes, for example if after application to a matrix of one of the procedures which are included in Triangle procedure, she has not changed(returns TRUE), she does not need to be printed
{
	bool is_identical = true;
	matrix *currentp = this;
	size_or_loc cur_sz = currentp->size(), size = mtx_ptr->size();
	if (cur_sz != size) is_identical = false;
    for (int i = 0; (i < cur_sz.lin*cur_sz.col)&&(is_identical); i += cur_sz.col)
		for (int j = 0; (j < cur_sz.col)&&(is_identical); j++)
			if ( *(currentp + i + j) != *(mtx_ptr + i + j) )
				is_identical = false;

	return is_identical;
} // end of is_identical();

matrix matrix::det; 
size_t combinations(std::vector<int> & source, std::vector<int> & result, const int &n, const int &k) // return an amount of combinations
{
	if ((n >= k)&&(k > 1))
	{
		for(int i = 0; i <= n - k; i++)
		{
			for(int t = i+k-1; t < n; t++)
			{
				for(int j = i; j < i+k-1; j++)
					result.push_back(source[j]);
				result.push_back(source[t]);
			}
		}
	}
	else std::cerr << "\aERROR! 'combinations': conditions (n > k and k > 1) are failed.\r\n" << std::endl;
	return result.size() / k;
}

///////////////////////////////---END OF DETERMINATION---////////////////////////////


