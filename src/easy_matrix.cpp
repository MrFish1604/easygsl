#include "easy_matrix.h"

Matrix::Matrix(const unsigned int& n, const unsigned int& m): _nLines(n), _nCols(m)
{
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
}
Matrix::Matrix(const unsigned int& n, const unsigned int& m, const double value): _nLines(n), _nCols(m)
{
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
    gsl_matrix_set_all(_matrix, value);
}
Matrix::Matrix(const Matrix& mat)
{
    _nLines = mat._nLines;
    _nCols = mat._nCols;
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
    gsl_matrix_memcpy(_matrix, mat._matrix);
}

double& Matrix::at(const unsigned int& i, const unsigned int& j)
{
    if(i>=_nLines || j>=_nCols)
        throw std::out_of_range("Index out of range");
    else
        return *gsl_matrix_ptr(_matrix, i, j);
}

std::string Matrix::toString()
{
    return "";
}

double& Matrix::operator[](const couple& i)
{
    return *gsl_matrix_ptr(_matrix, i.x, i.y);
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