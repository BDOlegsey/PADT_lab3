#ifndef LAB3_TRIANGULAR_MATRIX_H
#define LAB3_TRIANGULAR_MATRIX_H

#include "square_matrix.h"

namespace lab3 {

enum class TriKind { Upper, Lower };

template <class T>
class TriangularMatrix : public SquareMatrix<T> {
public:
    TriangularMatrix(int size, TriKind kind);
    TriangularMatrix(int size, TriKind kind, const T* data);
    TriangularMatrix(const TriangularMatrix<T>& other);
    TriangularMatrix<T>& operator=(const TriangularMatrix<T>& other);

    TriKind GetKind() const { return kind_; }

    void Set(int row, int col, const T& value) override;
    void AddMatrix(const Matrix<T>& other) override;

private:
    TriKind kind_;

    bool IsAllowed(int row, int col) const;
    void Validate(const T* data) const;
};

}  // namespace lab3

#include "triangular_matrix.tpp"

#endif
