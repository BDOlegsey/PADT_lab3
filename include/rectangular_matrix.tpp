#ifndef LAB3_RECTANGULAR_MATRIX_TPP
#define LAB3_RECTANGULAR_MATRIX_TPP

namespace lab3 {

template <class T>
RectangularMatrix<T>::RectangularMatrix(int rows, int cols)
    : Matrix<T>(rows, cols) {}

template <class T>
RectangularMatrix<T>::RectangularMatrix(int rows, int cols, const T* data)
    : Matrix<T>(rows, cols, data) {}

template <class T>
RectangularMatrix<T>::RectangularMatrix(const RectangularMatrix<T>& other)
    : Matrix<T>(other) {}

template <class T>
RectangularMatrix<T>& RectangularMatrix<T>::operator=(const RectangularMatrix<T>& other) {
    Matrix<T>::operator=(other);
    return *this;
}

}  // namespace lab3

#endif
