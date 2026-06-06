#ifndef LAB3_SQUARE_MATRIX_H
#define LAB3_SQUARE_MATRIX_H

#include "matrix.h"

namespace lab3 {

template <class T>
class SquareMatrix : public Matrix<T> {
public:
    explicit SquareMatrix(int size);
    SquareMatrix(int size, const T* data);
    SquareMatrix(const SquareMatrix<T>& other);
    SquareMatrix<T>& operator=(const SquareMatrix<T>& other);

    int GetSize() const { return this->rows_; }

    T Trace() const;

    static SquareMatrix<T> Identity(int size);
};

}  // namespace lab3

#include "square_matrix.tpp"

#endif
