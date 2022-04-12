#include "easy_matrix.h"

Matrix::Matrix()
{
    _matrix = nullptr;
    _p = nullptr;
}

Matrix::Matrix(const unsigned int& n): _nLines(n), _nCols(n), _signum(0), _p(nullptr)
{
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
}
Matrix::Matrix(const unsigned int& n, const unsigned int& m): _nLines(n), _nCols(m), _signum(0), _p(nullptr)
{
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
}
Matrix::Matrix(const unsigned int& n, const unsigned int& m, const double value): _nLines(n), _nCols(m), _signum(0), _p(nullptr)
{
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
    gsl_matrix_set_all(_matrix, value);
}
Matrix::Matrix(const Matrix& mat): _p(nullptr)
{
    copy(mat);
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

double Matrix::at(const unsigned int& i, const unsigned int& j) const
{
    if(i>=_nLines || j>=_nCols)
        throw std::out_of_range("Index out of range");
    else
        return *gsl_matrix_ptr(_matrix, i, j);
}

double Matrix::atne(const unsigned int& i, const unsigned int& j) const
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

int Matrix::nrows() const { return _nLines; }

int Matrix::ncols() const { return _nCols; }

std::string Matrix::toString() const
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
double Matrix::operator[](const couple& i) const
{
    return *gsl_matrix_ptr(_matrix, i.x, i.y);
}

void Matrix::operator=(const Matrix& mat)
{
    // gsl_matrix_memcpy(_matrix, mat._matrix);
    copy(mat);
}
void Matrix::copy(const Matrix& mat)
{
    gsl_matrix_free(_matrix);
    _nLines = mat._nLines;
    _nCols = mat._nCols;
    _matrix = gsl_matrix_alloc(_nLines, _nCols);
    gsl_matrix_memcpy(_matrix, mat._matrix);
    _signum = mat._signum;
    if(mat._p!=nullptr)
        gsl_permutation_memcpy(_p, mat._p);
    else
        _p = nullptr;
}

void Matrix::computeLU()
{
    _p = gsl_permutation_alloc(_nLines);
    gsl_linalg_LU_decomp(_matrix, _p, &_signum);
}

Matrix Matrix::getLU()
{
    Matrix rtn;
    rtn.copy(*this);
    rtn.computeLU();
    return rtn;
}

int Matrix::signum()
{
    return _signum;
}

bool Matrix::LUcomputed()
{
    return _p!=nullptr;
}

void Matrix::setIdentity()
{
    gsl_matrix_set_identity(_matrix);
}

Matrix::~Matrix()
{
    gsl_matrix_free(_matrix);
    gsl_permutation_free(_p);
}


Matrix createIdentity(const unsigned int n, const unsigned int m)
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
Matrix operator*(const double& a, const Matrix& mat)
{
    Matrix c(mat);
    c*=a;
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

bool operator==(const Matrix& A, const Matrix& B)
{
    if(A._nLines != B._nLines)
        return false;
    if(A._nCols != B._nCols)
        return false;
    
    for(int i=0; i<A._nLines; i++)
    {
        for(int j=0; j<A._nCols; j++)
        {
            if(A.atne(i,j)!=B.atne(i,j))
                return false;
        }
    }
    return true;
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

double dot00(const Matrix& A, const Matrix& B)
{
    Matrix C(A._nLines, B._nCols);
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1., A._matrix, B._matrix, 0., C._matrix);
    return C.atne(0,0);
}

Matrix transpose(const Matrix& A)
{
    Matrix mat(A._nCols, A._nLines);
    gsl_matrix_transpose_memcpy(mat._matrix, A._matrix);
    return mat;
}