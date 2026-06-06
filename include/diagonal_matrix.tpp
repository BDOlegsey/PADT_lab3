#ifndef LAB3_DIAGONAL_MATRIX_TPP
#define LAB3_DIAGONAL_MATRIX_TPP

namespace lab3 {

template <class T>
void DiagonalMatrix<T>::Validate(const T* data) const {
    const int n = this->GetSize();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r != c && !(data[r * n + c] == T())) {
                throw lab2::InvalidArgument("data violates diagonal structure");
            }
        }
    }
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(int size) : SquareMatrix<T>(size) {}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(int size, const T* data) : SquareMatrix<T>(size) {
    if (size > 0 && data == nullptr) {
        throw lab2::InvalidArgument("data pointer is null");
    }
    if (data != nullptr) {
        Validate(data);
    }
    const int n = size;
    for (int i = 0; i < n; ++i) {
        this->data_.Set(this->Index(i, i), data[i * n + i]);
    }
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(const DiagonalMatrix<T>& other)
    : SquareMatrix<T>(other) {}

template <class T>
DiagonalMatrix<T>& DiagonalMatrix<T>::operator=(const DiagonalMatrix<T>& other) {
    SquareMatrix<T>::operator=(other);
    return *this;
}

template <class T>
void DiagonalMatrix<T>::Set(int row, int col, const T& value) {
    this->CheckBounds(row, col);
    if (row != col && !(value == T())) {
        throw lab2::InvalidArgument("write outside diagonal");
    }
    this->data_.Set(this->Index(row, col), value);
}

template <class T>
void DiagonalMatrix<T>::AddMatrix(const Matrix<T>& other) {
    this->CheckSameShape(other);
    const DiagonalMatrix<T>* diag = dynamic_cast<const DiagonalMatrix<T>*>(&other);
    if (diag == nullptr) {
        throw lab2::InvalidArgument("operand is not a diagonal matrix");
    }
    const int n = this->GetSize();
    for (int i = 0; i < n; ++i) {
        this->data_.Set(this->Index(i, i),
                        this->data_.Get(this->Index(i, i)) + other.Get(i, i));
    }
}

}  // namespace lab3

#endif
