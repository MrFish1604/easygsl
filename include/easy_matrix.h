#ifndef EASYMATRIX
#define EASYMATRIX

#include <gsl/gsl_matrix.h>
#include <iostream>
#include <gsl/gsl_blas.h>
#include "easy_vector.h"

typedef struct couple couple;
struct couple
{
    int x;
    int y;
};

class Matrix
{
public:
    Matrix(const unsigned int& n);
    Matrix(const unsigned int& n, const unsigned int& m);
    Matrix(const unsigned int& n, const unsigned int& m, const double value);
    Matrix(const Matrix& mat);
    double& at(const unsigned int& i, const unsigned int& j);
    double& atne(const unsigned int& i, const unsigned int& j);
    Vector getRow(const unsigned int& i);
    Vector getCol(const unsigned int& i);
    int nrows();
    int ncols();
    std::string toString();     // TODO
    void setIdentity();
    void operator+=(const Matrix& mat);
    void operator+=(const double& a);
    void operator-=(const Matrix& mat);
    void operator-=(const double& a);
    void operator*=(const Matrix& mat);
    void operator*=(const double& a);
    void operator/=(const Matrix& mat);
    void operator/=(const double& a);
    double& operator[](const couple& i);
    void copy(const Matrix& mat);
    ~Matrix();
protected:
    unsigned int _nLines, _nCols;
    gsl_matrix* _matrix;

friend Matrix dot(const Matrix& A, const Matrix& B);
friend double dot00(const Matrix& A, const Matrix& B);
friend Matrix transpose(const Matrix& A);
};

Matrix createIdentity(const unsigned int n, const unsigned int m);

Matrix operator+(const Matrix& mat, const Matrix& mat1);
Matrix operator+(const Matrix& mat, const double& a);
Matrix operator-(const Matrix& mat, const Matrix& mat1);
Matrix operator-(const Matrix& mat, const double& a);
Matrix operator*(const Matrix& mat, const Matrix& mat1);
Matrix operator*(const Matrix& mat, const double& a);
Matrix operator*(const double& a, const Matrix& mat);
Matrix operator/(const Matrix& mat, const Matrix& mat1);
Matrix operator/(const Matrix& mat, const double& a);
std::ostream& operator<<(std::ostream& stream, Matrix& mat);

#endif