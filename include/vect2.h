#ifndef VECT2_H
#define VECT2_H

#include "easy_vector.h"

class Vect2 : public Vector
{
public:
    Vect2();
    Vect2(const double& x, const double& y);
friend double scalar(const Vect2& u, const Vect2& v);
};

#endif