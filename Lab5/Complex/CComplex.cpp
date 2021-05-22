#include "CComplex.h"
#include <iomanip>


CComplex::CComplex(double real, double image)
	: m_real(real)
	, m_image(image)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(m_real * m_real + m_image * m_image);
}

double CComplex::GetArgument() const
{
	if (m_image != 0)
	{
		return tan(m_image / m_real);
	}
	// use optional
	return double(NAN);
}

CComplex& CComplex::operator += (const CComplex& a)
{
	m_real += a.Re();
	m_image += a.Im();

	return *this;
}

CComplex& CComplex::operator -= (const CComplex& a)
{
	m_real -= a.Re();
	m_image -= a.Im();

	return *this;
}

CComplex& CComplex::operator *= (const CComplex& a)
{
	double real = m_real * a.Re() - m_image * a.Im();
	double image = m_image * a.Re() + m_real * a.Im();
	m_real = real;
	m_image = image;

	return *this;
}

CComplex& CComplex::operator/= (const CComplex& a)
{
	double real = (m_real * a.Re() + m_image * a.Im()) / (a.Im() * a.Im() + a.Re() * a.Re());
	double image = (m_image * a.Re() - m_real * a.Im()) / (a.Im() * a.Im() + a.Re() * a.Re());
	m_image = image;
	m_real = real;

	return *this;
}

CComplex operator + (const CComplex& a, const CComplex& b)
{
	auto c = a;
	return c += b;
}

CComplex operator + (const double& a, const CComplex& b)
{
	return CComplex(a + b.Re(), b.Im());
}

CComplex operator - (const CComplex& a, const CComplex& b)
{
	auto c = a;
	return c -= b;
}

CComplex operator - (const double& a, const CComplex& b)
{
	return CComplex(a - b.Re(), b.Im());
}

CComplex operator * (const CComplex& a, const CComplex& b)
{
	auto c = a;
	return c *= b;
}

CComplex operator * (const double& a, const CComplex& b)
{
	return CComplex(a * b.Re(), a * b.Im());
}

CComplex operator / (const CComplex& a, const CComplex& b)
{
	auto c = a;
	return c /= b;
}

CComplex operator / (const double& a, const CComplex& b)
{
	double real = (a * b.Re()) / (b.Im() * b.Im() + b.Re() * b.Re());
	double image = (- a * b.Im()) / (b.Im() * b.Im() + b.Re() * b.Re());

	return CComplex(real, image);
}

CComplex& CComplex::operator + ()
{
	return *this;
}

CComplex& CComplex::operator - ()
{
	m_real = -m_real;
	m_image = -m_image;
	return *this;
}

bool operator == (const CComplex& a, const CComplex& b)
{
	bool realsAreEqual = (fabs(a.Re() - b.Re()) < DBL_EPSILON);
	bool imagesAreEqual = (fabs(a.Im() - b.Im()) < DBL_EPSILON);

	return realsAreEqual && imagesAreEqual;
}

bool operator == (const double& a, const CComplex& b)
{
	bool realsAreEqual = (fabs(a - b.Re()) < DBL_EPSILON);

	return realsAreEqual && b.Im() == 0;
}

bool operator != (const CComplex& a, const CComplex& b)
{
	return !(a == b);
}

bool operator != (const double& a, const CComplex& b)
{
	return !(a == b);
}

std::ostream& operator<< (std::ostream& out, const CComplex& a)
{
	out << a.Re() << '+' << a.Im() << 'i';

	return out;
}

std::istream& operator>> (std::istream& in, CComplex& a)
{
	double real;
	double image;
	char plus;
	in >> real;
	in >> plus;
	in >> image;
	a.m_real = real;
	a.m_image = image;

	return in;
}

