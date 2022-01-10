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

double& Matrix::atne(const unsigned int& i, const unsigned int& j)
{
    return *gsl_matrix_ptr(_matrix, i, j);
}

Vector Matrix::getRow(const unsigned int& i)
{
    return Vector(gsl_matrix_row(_matrix, i));
}

Vector Matrix::getCol(const unsigned int& i)
{
    return Vector(gsl_matrix_column(_matrix, i));
}

int Matrix::nrows(){ return _nCols; }

int Matrix::nlines(){ return _nLines; }

std::string Matrix::toString()
{
    std::string rtn = "|" + std::to_string(gsl_matrix_get(_matrix, 0, 0));
    for(int i=1; i<_nCols; i++)
        rtn += "\t" + std::to_string(gsl_matrix_get(_matrix, 0, i));
    rtn += "|";
    for(int i=1; i<_nLines; i++)
    {
        rtn += "\n|" + std::to_string(gsl_matrix_get(_matrix, i, 0));
        for(int j=1; j<_nCols; j++)
        {
            rtn += "\t" + std::to_string(gsl_matrix_get(_matrix, i, j));
        }
        rtn += "|";
    }
    return rtn;
}

void Matrix::operator+=(const Matrix& mat)
{
    gsl_matrix_add(_matrix, mat._matrix);
}
void Matrix::operator+=(const double& a)
{
    gsl_matrix_add_constant(_matrix, a);
}

void Matrix::operator-=(const Matrix& mat)
{
    gsl_matrix_sub(_matrix, mat._matrix);
}
void Matrix::operator-=(const double& a)
{
    gsl_matrix_add_constant(_matrix, -a);
}

void Matrix::operator*=(const Matrix& mat)
{
    gsl_matrix_mul_elements(_matrix, mat._matrix);
}
void Matrix::operator*=(const double& a)
{
    gsl_matrix_scale(_matrix, a);
}

void Matrix::operator/=(const Matrix& mat)
{
    gsl_matrix_div_elements(_matrix, mat._matrix);
}
void Matrix::operator/=(const double& a)
{
    gsl_matrix_scale(_matrix, 1/a);
}

double& Matrix::operator[](const couple& i)
{
    return *gsl_matrix_ptr(_matrix, i.x, i.y);
}

void Matrix::setIdentity()
{
    gsl_matrix_set_identity(_matrix);
}

Matrix::~Matrix()
{
    gsl_matrix_free(_matrix);
}


Matrix createIndentity(const unsigned int n, const unsigned int m)
{
    Matrix mat(n, m);
    mat.setIdentity();
    return mat;
}

Matrix operator+(const Matrix& mat, const Matrix& mat1)
{
    Matrix c(mat);
    c+=mat1;
    return c;
}
Matrix operator+(const Matrix& mat, const double& a)
{
    Matrix c(mat);
    c+= a;
    return c;
}
Matrix operator-(const Matrix& mat, const Matrix& mat1)
{
    Matrix c(mat);
    c-= mat1;
    return c;
}
Matrix operator-(const Matrix& mat, const double& a)
{
    Matrix c(mat);
    c-= a;
    return c;
}
Matrix operator*(const Matrix& mat, const Matrix& mat1)
{
    Matrix c(mat);
    c*= mat1;
    return c;
}
Matrix operator*(const Matrix& mat, const double& a)
{
    Matrix c(mat);
    c*= a;
    return c;
}
Matrix operator/(const Matrix& mat, const Matrix& mat1)
{
    Matrix c(mat);
    c/= mat1;
    return c;
}
Matrix operator/(const Matrix& mat, const double& a)
{
    Matrix c(mat);
    c/= a;
    return c;
}

std::ostream& operator<<(std::ostream& stream, Matrix& mat)
{
    stream << mat.toString();
    return stream;
}

Matrix dot(const Matrix& A, const Matrix& B)
{
    Matrix C(A._nLines, B._nCols);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., A._matrix, B._matrix, 0., C._matrix);
    return C;
}