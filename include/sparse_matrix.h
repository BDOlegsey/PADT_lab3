#ifndef LAB3_SPARSE_MATRIX_H
#define LAB3_SPARSE_MATRIX_H

#include <cstddef>

#include "array_sequence.h"
#include "errors.h"

namespace lab3 {

template <class T>
struct SparseEntry {
    size_t row;
    size_t col;
    T      value;
    SparseEntry() : row(0), col(0), value(T()) {}
    SparseEntry(size_t r, size_t c, const T& v) : row(r), col(c), value(v) {}
};

template <class T>
class SparseMatrix {
public:
    SparseMatrix(size_t rows, size_t cols);
    SparseMatrix(size_t rows, size_t cols, const T* data);
    SparseMatrix(const SparseMatrix<T>& other);
    SparseMatrix<T>& operator=(const SparseMatrix<T>& other);
    ~SparseMatrix();

    size_t GetRows() const { return rows_; }
    size_t GetCols() const { return cols_; }

    const T& Get(size_t row, size_t col) const;
    void Set(size_t row, size_t col, const T& value);

    void AddMatrix(const SparseMatrix<T>& other);
    void MulScalar(const T& scalar);
    double Norm() const;

    SparseMatrix<T> Multiply(const SparseMatrix<T>& other) const;

    size_t GetNnz() const;

private:
    size_t rows_;
    size_t cols_;
    lab2::MutableArraySequence<SparseEntry<T>>* entries_;
    mutable T zero_;

    size_t FindIdx(size_t row, size_t col) const;
    void   EraseAt(size_t idx);
    void   CheckBounds(size_t row, size_t col) const;
    void   CheckSameShape(const SparseMatrix<T>& other) const;

    static const size_t kNotFound = static_cast<size_t>(-1);
};

}  // namespace lab3

#include "sparse_matrix.tpp"

#endif
