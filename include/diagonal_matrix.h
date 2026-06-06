#ifndef LAB3_DIAGONAL_MATRIX_H
#define LAB3_DIAGONAL_MATRIX_H

#include "square_matrix.h"

namespace lab3 {

template <class T>
class DiagonalMatrix : public SquareMatrix<T> {
public:
    explicit DiagonalMatrix(int size);
    DiagonalMatrix(int size, const T* data);
    DiagonalMatrix(const DiagonalMatrix<T>& other);
    DiagonalMatrix<T>& operator=(const DiagonalMatrix<T>& other);

    void Set(int row, int col, const T& value) override;
    void AddMatrix(const Matrix<T>& other) override;

private:
    void Validate(const T* data) const;
};

}  // namespace lab3

#include "diagonal_matrix.tpp"

#endif
