#ifndef LAB3_SQUARE_MATRIX_TPP
#define LAB3_SQUARE_MATRIX_TPP

namespace lab3 {

template <class T>
SquareMatrix<T>::SquareMatrix(int size) : Matrix<T>(size, size) {}

template <class T>
SquareMatrix<T>::SquareMatrix(int size, const T* data) : Matrix<T>(size, size, data) {}

template <class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& other) : Matrix<T>(other) {}

template <class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T>& other) {
    Matrix<T>::operator=(other);
    return *this;
}

template <class T>
T SquareMatrix<T>::Trace() const {
    T acc = T();
    const int n = this->rows_;
    for (int i = 0; i < n; ++i) acc = acc + this->Get(i, i);
    return acc;
}

template <class T>
SquareMatrix<T> SquareMatrix<T>::Identity(int size) {
    SquareMatrix<T> result(size);
    for (int i = 0; i < size; ++i) result.Set(i, i, static_cast<T>(1));
    return result;
}

}  // namespace lab3

#endif
