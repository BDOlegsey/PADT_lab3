#ifndef LAB3_ORTHOGONAL_MATRIX_H
#define LAB3_ORTHOGONAL_MATRIX_H

#include "square_matrix.h"

namespace lab3 {

template <class T>
class OrthogonalMatrix : public SquareMatrix<T> {
public:
    explicit OrthogonalMatrix(int size);
    OrthogonalMatrix(int size, const T* data, double eps = 1e-9);
    OrthogonalMatrix(const OrthogonalMatrix<T>& other);
    OrthogonalMatrix<T>& operator=(const OrthogonalMatrix<T>& other);

    bool IsOrthogonal(double eps = 1e-9) const;
};

}  // namespace lab3

#include "orthogonal_matrix.tpp"

#endif
