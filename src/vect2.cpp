#include "vect2.h"

Vect2::Vect2()
{
    _size = 2;
    _vect = gsl_vector_alloc(_size);
}

Vect2::Vect2(const double& x, const double& y)
{
    _size = 2;
    _vect = gsl_vector_alloc(_size);
    gsl_vector_set(_vect, 0, x);
    gsl_vector_set(_vect, 1, y);
}

double scalar(const Vect2& u, const Vect2& v)
{
    return gsl_vector_get(u._vect, 0)*gsl_vector_get(v._vect, 0) + gsl_vector_get(u._vect, 1)*gsl_vector_get(v._vect, 1);
}