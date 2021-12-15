#ifndef EASYMATRIX
#define EASYMATRIX

#include <gsl/gsl_matrix.h>
#include <iostream>

typedef struct couple couple;
struct couple
{
    unsigned int x;
    unsigned int y;
};

class Matrix
{
public:
    Matrix(const unsigned int& n, const unsigned int& m);
    Matrix(const unsigned int& n, const unsigned int& m, const double value);
    Matrix(const Matrix& mat);
    double& at(const unsigned int& i, const unsigned int& j);
    std::string toString();     // TODO
    void setIdentity();
    double& operator[](const couple& i);
private:
    unsigned int _nLines, _nCols;
    gsl_matrix* _matrix;
};

Matrix createIndentity(const unsigned int n, const unsigned int m);

#endif