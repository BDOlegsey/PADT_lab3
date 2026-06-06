#ifndef LAB3_RECTANGULAR_MATRIX_H
#define LAB3_RECTANGULAR_MATRIX_H

#include "matrix.h"

namespace lab3 {

template <class T>
class RectangularMatrix : public Matrix<T> {
public:
    RectangularMatrix(int rows, int cols);
    RectangularMatrix(int rows, int cols, const T* data);
    RectangularMatrix(const RectangularMatrix<T>& other);
    RectangularMatrix<T>& operator=(const RectangularMatrix<T>& other);
};

}  // namespace lab3

#include "rectangular_matrix.tpp"

#endif
