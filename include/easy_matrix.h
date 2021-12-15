#ifndef EASYMATRIX
#define EASYMATRIX

#include <gsl/gsl_matrix.h>

class Matrix
{
public:
    Matrix(const unsigned int n, const unsigned int m);
    Matrix(const Matrix& mat);
    void setIdentity();
private:
    unsigned int _nLines, _nCols;
    gsl_matrix _matrix;
};

Matrix createIndentity(const unsigned int n, const unsigned int m);

#endif