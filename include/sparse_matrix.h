#ifndef LAB3_SPARSE_MATRIX_H
#define LAB3_SPARSE_MATRIX_H

#include "array_sequence.h"
#include "matrix.h"

namespace lab3 {

template <class T>
struct SparseEntry {
    int row;
    int col;
    T   value;
    SparseEntry() : row(0), col(0), value(T()) {}
    SparseEntry(int r, int c, const T& v) : row(r), col(c), value(v) {}
};

template <class T>
class SparseMatrix : public Matrix<T> {
public:
    SparseMatrix(int rows, int cols);
    SparseMatrix(int rows, int cols, const T* data);
    SparseMatrix(const SparseMatrix<T>& other);
    SparseMatrix<T>& operator=(const SparseMatrix<T>& other);
    ~SparseMatrix() override;

    const T& Get(int row, int col) const override;
    void Set(int row, int col, const T& value) override;

    void AddMatrix(const Matrix<T>& other) override;
    void MulScalar(const T& scalar) override;
    double Norm() const override;

    SparseMatrix<T> Multiply(const SparseMatrix<T>& other) const;

    int GetNnz() const;

private:
    lab2::MutableArraySequence<SparseEntry<T>>* entries_;
    mutable T zero_;

    int  FindIdx(int row, int col) const;
    void EraseAt(int idx);
};

}  // namespace lab3

#include "sparse_matrix.tpp"

#endif
