#include "easy_vector.h"
#include <stdexcept>

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

double Vector::get(const unsigned int& i)
{
    if(i>=_size)
        throw std::out_of_range("Index out of range");
    else
       return gsl_vector_get(_vect, i);
}

void Vector::set(const unsigned int& i, const double value)
{
    if(i>_size)
        throw std::out_of_range("Index out of range");
    else
        gsl_vector_set(_vect, i, value);
}

double& Vector::at(const unsigned int& i)
{
    if(i>=_size)
        throw std::out_of_range("Index out of range");
    else
        return *gsl_vector_ptr(_vect, i);
}

std::string Vector::toString()
{
    std::string str = "(";
    str += std::to_string(operator[](0));
    for(int i=1; i<_size; i++)
    {
        str += "  ";
        str += std::to_string(operator[](i));
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

double& Vector::operator[](const unsigned int& i)
{
    return *gsl_vector_ptr(_vect, i);
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