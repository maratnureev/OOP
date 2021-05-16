#pragma once
#include <math.h>
#include <float.h>
#include <iostream>

class CComplex
{
public:
	CComplex(double real = 0, double image = 0);
	double Re()const;
	double Im()const;
	double GetMagnitude()const;
	double GetArgument()const;
	friend std::ostream& operator<< (std::ostream& out, const CComplex& a);
	friend std::istream& operator>> (std::istream& in, CComplex& a);
	CComplex& operator + ();
	CComplex& operator - ();
	CComplex& operator += (const CComplex& a);
	CComplex& operator -= (const CComplex& a);
	CComplex& operator *= (const CComplex& a);
	CComplex& operator /= (const CComplex& a);
	friend CComplex operator + (const CComplex& a, const CComplex& b);
	friend CComplex operator + (const double& a, const CComplex& b);
	friend CComplex operator - (const CComplex& a, const CComplex& b);
	friend CComplex operator - (const double& a, const CComplex& b);
	friend CComplex operator * (const CComplex& a, const CComplex& b);
	friend CComplex operator * (const double& a, const CComplex& b);
	friend CComplex operator / (const CComplex& a, const CComplex& b);
	friend CComplex operator / (const double& a, const  CComplex& b);
	friend bool operator == (const CComplex& a, const  CComplex& b);
	friend bool operator == (const double& a, const  CComplex& b);
	friend bool operator != (const CComplex& a, const  CComplex& b);
	friend bool operator != (const double& a, const  CComplex& b);
	
private:
	double m_real;
	double m_image;
};

