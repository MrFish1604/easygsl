#include "vect3.h"

Vect3::Vect3()
{
    _size = 3;
    _vect = gsl_vector_alloc(_size);
}

Vect3::Vect3(const double& x, const double& y, const double& z)
{
    _size = 3;
    _vect = gsl_vector_alloc(_size);
    gsl_vector_set(_vect, 0, x);
    gsl_vector_set(_vect, 1, y);
    gsl_vector_set(_vect, 2, z);
}

void Vect3::cross(const Vect3& v)
{
    double x = gsl_vector_get(_vect, 1)*gsl_vector_get(v._vect, 2) - gsl_vector_get(_vect, 2)*gsl_vector_get(v._vect, 1);
    double y = gsl_vector_get(_vect, 2)*gsl_vector_get(v._vect, 0) - gsl_vector_get(_vect, 0)*gsl_vector_get(v._vect, 2);
    gsl_vector_set(_vect, 2, gsl_vector_get(_vect, 0)*gsl_vector_get(v._vect, 1) - gsl_vector_get(_vect, 1)*gsl_vector_get(v._vect, 0));
    gsl_vector_set(_vect, 1, y);
    gsl_vector_set(_vect, 0, x);
}

Vect3 cross(const Vect3& u, const Vect3& v)
{
    Vect3 w = u;
    w.cross(v);
    return w;
}

double scalar(const Vect3& u, const Vect3& v)
{
    return gsl_vector_get(u._vect, 0)*gsl_vector_get(v._vect, 0) + gsl_vector_get(u._vect, 1)*gsl_vector_get(v._vect, 1) + gsl_vector_get(u._vect, 2)*gsl_vector_get(v._vect, 2);
}

Vect3* basis_ortho(const double& a)
{
    Vect3* basis = new Vect3[3];
    basis[0][0] = a;
    basis[1][1] = a;
    basis[2][2] = a;
    return basis;
}