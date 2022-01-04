#ifndef VECT3_H
#define VECT3_H

#include "easy_vector.h"

class Vect3 : public Vector
{
public:
    Vect3();
    Vect3(const double& x, const double& y, const double& z);
    void cross(const Vect3& v);
friend Vect3 cross(const Vect3& u, const Vect3& v);
friend double scalar(const Vect3& u, const Vect3& v);
};

Vect3* basis_ortho(const double& a=1);

#endif