#include "easy_matrix.h"

Matrix::Matrix(const unsigned int n, const unsigned int m) _nLines(n), _nCols(m)
{
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
}

Matrix::Matrix(const Matrix& mat)
{
    _nLines = mat._nLines;
    _nCols = mat._nCols;
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
    gsl_matrix_memcpy(_matrix, mat._matrix);
}

void Matrix::setIdentity()
{
    gsl_matrix_set_identity(_matrix);
}

Matrix createIndentity(const unsigned int n, const unsigned int m)
{
    Matrix mat(n, m);
    mat.setIdentity();
    return mat;
}