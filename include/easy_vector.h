#ifndef GSLPPVECTOR
#define GSLPPVECTOR

#include <iostream>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>

class Vector
{
public:
    Vector();
    Vector(const unsigned int n);
    Vector(const unsigned int n, const double x);
    Vector(gsl_vector_view vv);
    Vector(const Vector& v);
    double get(const unsigned int& i);
    void set(const unsigned int& i, const double value);
    double& at(const unsigned int& i);
    gsl_vector* getptr();
    int dim();
    std::string toString();
    void zeros();
    void setAll(const double x);
    void basisne(const unsigned int i);
    double max();
    double min();
    double max(unsigned int* i);
    double min(unsigned int* i);
    double norm();
    double sum();
    double dot(const Vector& v);
    void operator+=(const Vector& v);
    void operator*=(const Vector& v);
    void operator*=(const double& a);
    void operator/=(const Vector& v);
    void operator/=(const double& a);
    double& operator[](const unsigned int& i);
    bool operator==(const Vector& v);
    void operator=(const Vector& v);
    ~Vector();
protected:
    gsl_vector* _vect;
    unsigned int _size;
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator*(const Vector& a, const Vector& b);
Vector operator*(const Vector& v, const double& a);
Vector operator*(const double& a, const Vector& v);
Vector operator/(const Vector& a, const Vector& b);
Vector operator/(const Vector& v, const double& a);

void createBasis(const unsigned int& dim, Vector* basis);

std::ostream& operator<<(std::ostream& stream, Vector& vect);

#endif