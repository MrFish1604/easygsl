#ifndef GSLPPVECTOR
#define GSLPPVECTOR

#include <iostream>
#include <gsl/gsl_vector.h>

class Vector
{
public:
    Vector(const unsigned int n);
    Vector(const unsigned int n, const double x);
    Vector(const Vector& v);
    double getne(const unsigned int& i);
    void setne(const unsigned int& i, const double value);
    std::string toString();
    void zeros();
    void setAll(const double x);
    void basisne(const unsigned int i);
    void operator+=(const Vector& v);
    void operator*=(const Vector& v);
    void operator*=(const double& a);
    void operator/=(const Vector& v);
    void operator/=(const double& a);
private:
    gsl_vector* _vect;
    unsigned int _size;
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator*(const Vector& a, const Vector& b);
Vector operator*(const Vector& v, const double& a);
Vector operator*(const double& a, const Vector& v);
Vector operator/(const Vector& a, const Vector& b);
Vector operator/(const Vector& v, const double& a);

std::ostream& operator<<(std::ostream& stream, Vector& vect);

#endif