#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	this->capacity = source.capacity;
	this->terms = source.terms;
	this->termArray = new Term[capacity];
	for ( int i = 0 ; i < terms ; i++ )
	{
		this->termArray[i] = source.termArray[i];
	}
}	

// Destructor
Polynomial::~Polynomial()
{
	delete[] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
	if ( this == &source )
	{
		return *this;
	}
	else
	{
		delete[] this->termArray;
		this->capacity = source.capacity;
		this->terms = source.terms;
		this->termArray = new Term[capacity];
		for ( int i = 0 ; i < terms; i++ )
		{
			this->termArray[i] = source.termArray[i];
		}
		return *this;
	}
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
	Polynomial c;
	float c_coef;
	int a_start = 0;
	int b_start = 0;
	
	while ( a_start < terms && b_start < source.terms )
	{
		if ( termArray[a_start].exp == source.termArray[b_start].exp )
		{
			c_coef = termArray[a_start].coef + source.termArray[b_start].coef;
			if ( fabs(c_coef) < 1.0e-6 )
			{
				a_start++;
				b_start++;
			}
			else
			{
				c.CreateTerm(c_coef, termArray[a_start].exp);
				a_start++;
				b_start++;
			}
		}
		else
		{
			if ( termArray[a_start].exp > source.termArray[b_start].exp ) 
			{
				c_coef = termArray[a_start].coef;
				c.CreateTerm(c_coef, termArray[a_start].exp);
				a_start++;
			}
			else
			{
				c_coef = source.termArray[b_start].coef;
				c.CreateTerm(c_coef, source.termArray[b_start].exp);
				b_start++;
			}
		}
	}
	
	while ( a_start < terms )
	{
		c_coef = termArray[a_start].coef;
		c.CreateTerm(c_coef, termArray[a_start].exp);
		a_start++;
	}
	
	while ( b_start < source.terms )
	{
		c_coef = source.termArray[b_start].coef;
		c.CreateTerm(c_coef, source.termArray[b_start].exp);
		b_start++;
	}
	
	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;
	float c_coef;
	int a_start = 0;
	int b_start = 0;
	
	while ( a_start < terms && b_start < source.terms )
	{
		if ( termArray[a_start].exp == source.termArray[b_start].exp )
		{
			c_coef = termArray[a_start].coef - source.termArray[b_start].coef;
			if ( fabs(c_coef) < 1.0e-6 )
			{
				a_start++;
				b_start++;
			}
			else
			{
				c.CreateTerm(c_coef, termArray[a_start].exp);
				a_start++;
				b_start++;
			}
		}
		else
		{
			if ( termArray[a_start].exp > source.termArray[b_start].exp ) 
			{
				c_coef = termArray[a_start].coef;
				c.CreateTerm(c_coef, termArray[a_start].exp);
				a_start++;
			}
			else
			{
				c_coef = float(0) - source.termArray[b_start].coef;
				c.CreateTerm(c_coef, source.termArray[b_start].exp);
				b_start++;
			}
		}
	}
	
	while ( a_start < terms )
	{
		c_coef = termArray[a_start].coef;
		c.CreateTerm(c_coef, termArray[a_start].exp);
		a_start++;
	}
	
	while ( b_start < source.terms )
	{
		c_coef = float(0) - source.termArray[b_start].coef;
		c.CreateTerm(c_coef, source.termArray[b_start].exp);
		b_start++;
	}
	
	return c;
	
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;
	Polynomial temp;
	float temp_coef;
	int temp_exp;
	int a_start, b_start;
	int idx = -1;
	
	for ( a_start = 0 ; a_start < terms ; a_start++ )
	{
		for ( b_start = 0 ; b_start < source.terms ; b_start++ )
		{
			temp_exp = termArray[a_start].exp + source.termArray[b_start].exp;
			temp_coef = termArray[a_start].coef * source.termArray[b_start].coef;
			idx = -1;
			for ( int k = 0 ; k < temp.terms ; k++ )
			{
				if ( temp.termArray[k].exp == temp_exp )
				{
					idx = k;
				}
			}
			if ( idx == -1 )
			{
				temp.CreateTerm(temp_coef, temp_exp);
			}
			else
			{
				temp.termArray[idx].coef += temp_coef;
			}
		}
	}
	
	for ( int i = 0 ; i < temp.terms ; i++ )
	{
		if ( fabs(temp.termArray[i].coef) < 1.0e-6 )
		{
			continue;
		}
		else
		{
			c.CreateTerm(temp.termArray[i].coef, temp.termArray[i].exp);
		}
	}
	
	return c;	
}

bool Polynomial::operator == (const Polynomial& source)
{
	bool ret;
	int flag = 0;
	
	if ( terms != source.terms )
	{
		ret = false;
		return ret;
	}
	else
	{
		for ( int i = 0 ; i < terms ; i++ )
		{
			if ( (termArray[i].exp != source.termArray[i].exp) || fabs(termArray[i].coef - source.termArray[i].coef) >= 1.0e-6 )
			{
				flag = 1;
			}
		}
	}
	
	if ( flag == 0 )
	{
		ret = true;
	}
	else
	{
		ret = false;
	}
	
	return ret;
}

float Polynomial::Eval(float x)
{
	float ret = 0;
	float temp = 0;
	
	for ( int i = 0 ; i < terms ; i++ )
	{
		temp += termArray[i].coef;
		for ( int j = 0 ; j < termArray[i].exp ; j++ )
		{
			temp *= x;
		}
		ret += temp;
		temp = 0;
	}
	
	return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;
	float c_coef;
	int c_exp;
	
	if ( terms == 1 && termArray[0].exp == 0 )
	{
		c_coef = float(0);
		c_exp = 0;
		c.CreateTerm(c_coef, c_exp);
		return c;
	}
	
	for ( int i = 0 ; i < terms ; i++ )
	{
		if ( termArray[i].exp == 0 )
		{
			break;
		}
		c_coef = termArray[i].coef * float(termArray[i].exp);
		c_exp = termArray[i].exp - 1;
		c.CreateTerm(c_coef, c_exp);
	}
	
	return c;	

}

void Polynomial::CreateTerm(const float coef, const int exp)
{
	int flag = 0;
	
	if ( terms == capacity )
	{
		capacity += 10;
		Term* newtermArray = new Term[capacity];
		for ( int i = 0 ; i < terms ; i++ )
		{
			newtermArray[i] = termArray[i];
		}
		delete[] termArray;
		termArray = new Term[capacity];
		for ( int i = 0 ; i < terms ; i++ )
		{
			termArray[i] = newtermArray[i];
		}
		delete[] newtermArray;
	}
	
	if ( terms >= 1 )
	{
		for ( int i = 0 ; i < terms; i++ )
		{
			if ( termArray[i].exp == exp )
			{
				termArray[i].coef = coef;
				flag = 1;
				break;
			}
		}
	}
	
	if ( flag == 0 )
	{
		termArray[terms].coef = coef;
		termArray[terms].exp = exp;
		terms += 1;
	}
	
	for ( int i = 1; i < terms ; i++ )
	{
		int j = i;
		while ( j >= 1 && termArray[j].exp > termArray[j-1].exp )
		{
			Term temp = termArray[j];
			termArray[j] = termArray[j-1];
			termArray[j-1] = temp;
			j--;
		}
	}
}

void Polynomial::Print()  // made by professor 
{
	if(terms == 0) std::cout << "0" << std::endl;
	else
	{
		for(int i=0; i<terms; i++)
		{
			float c = termArray[i].coef;
			int e = termArray[i].exp;
						
			if(c > 0 && i > 0)
			{
				std::cout << "+";
			}
			
			std::cout << c;
			if(e > 0) std::cout<<"x^"<<e;
		}
		std::cout << std::endl;
	}
}

