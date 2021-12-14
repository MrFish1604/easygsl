#include "easy_vector.h"

Vector::Vector(const unsigned int n): _size(n)
{
    _vect = gsl_vector_alloc(_size);
}
Vector::Vector(const unsigned int n, const double x): _size(n)
{
    _vect = gsl_vector_alloc(_size);
    setAll(x);
}
Vector::Vector(const Vector& v)
{
    _size = v._size;
    _vect = gsl_vector_alloc(_size);
    gsl_vector_memcpy(_vect, v._vect);
}

double Vector::getne(const unsigned int& i)
{
    return gsl_vector_get(_vect, i);
}

void Vector::setne(const unsigned int& i, const double value)
{
    gsl_vector_set(_vect, i, value);
}

std::string Vector::toString()
{
    std::string str = "(";
    str += std::to_string(getne(0));
    for(int i=1; i<_size; i++)
    {
        str += "  ";
        str += std::to_string(getne(i));
    }
    str += ")";
    return str;
}

void Vector::zeros()
{
    gsl_vector_set_zero(_vect);
}

void Vector::setAll(const double x)
{
    gsl_vector_set_all(_vect, x);
}

void Vector::basisne(const unsigned int i)
{
    gsl_vector_set_basis(_vect, i);
}

void Vector::operator+=(const Vector& v)
{
    gsl_vector_add(_vect, v._vect);
}

void Vector::operator*=(const Vector& v)
{
    gsl_vector_mul(_vect, v._vect);
}

void Vector::operator*=(const double& a)
{
    gsl_vector_scale(_vect, a);
}

void Vector::operator/=(const Vector& v)
{
    gsl_vector_div(_vect, v._vect);
}

void Vector::operator/=(const double& a)
{
    gsl_vector_scale(_vect, 1/a);
}

Vector operator+(const Vector& a, const Vector& b)
{
    Vector c(a);
    c+=b;
    return c;
}
Vector operator*(const Vector& a, const Vector& b)
{
    Vector c(a);
    c*=b;
    return c;
}
Vector operator*(const Vector& v, const double& a)
{
    Vector c(v);
    c*=a;
    return c;
}
Vector operator*(const double& a, const Vector& v)
{
    Vector c(v);
    c*=a;
    return c;
}
Vector operator/(const Vector& a, const Vector& b)
{
    Vector c(a);
    c/=b;
    return c;
}
Vector operator/(const Vector& v, const double& a)
{
    Vector c(v);
    c/=a;
    return c;
}

std::ostream& operator<<(std::ostream& stream, Vector& vect)
{
    stream << vect.toString();
    return stream;
}