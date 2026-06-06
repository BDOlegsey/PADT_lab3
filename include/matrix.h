#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include "dynamic_array.h"
#include "errors.h"

namespace lab3 {

template <class T>
class Matrix {
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, const T* data);
    Matrix(const Matrix<T>& other);
    Matrix<T>& operator=(const Matrix<T>& other);
    virtual ~Matrix() = default;

    int GetRows() const { return rows_; }
    int GetCols() const { return cols_; }

    virtual const T& Get(int row, int col) const;
    virtual void Set(int row, int col, const T& value);

    virtual void AddMatrix(const Matrix<T>& other);
    virtual void MulScalar(const T& scalar);

    virtual double Norm() const;

    void SwapRows(int i, int j);
    void SwapCols(int i, int j);
    void MulRow(int row, const T& factor);
    void MulCol(int col, const T& factor);
    void AddRowMultiplied(int target, int source, const T& factor);
    void AddColMultiplied(int target, int source, const T& factor);

    bool Equals(const Matrix<T>& other) const;

protected:
    int rows_;
    int cols_;
    lab2::DynamicArray<T> data_;

    int Index(int row, int col) const { return row * cols_ + col; }
    void CheckBounds(int row, int col) const;
    void CheckSameShape(const Matrix<T>& other) const;
    void CheckRow(int row) const;
    void CheckCol(int col) const;
};

}  // namespace lab3

#include "matrix.tpp"

#endif
