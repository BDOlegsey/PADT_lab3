#ifndef LAB3_TRIANGULAR_MATRIX_TPP
#define LAB3_TRIANGULAR_MATRIX_TPP

namespace lab3 {

template <class T>
bool TriangularMatrix<T>::IsAllowed(int row, int col) const {
    return (kind_ == TriKind::Upper) ? (row <= col) : (col <= row);
}

template <class T>
void TriangularMatrix<T>::Validate(const T* data) const {
    const int n = this->GetSize();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (!IsAllowed(r, c) && !(data[r * n + c] == T())) {
                throw lab2::InvalidArgument("data violates triangular structure");
            }
        }
    }
}

template <class T>
TriangularMatrix<T>::TriangularMatrix(int size, TriKind kind)
    : SquareMatrix<T>(size), kind_(kind) {}

template <class T>
TriangularMatrix<T>::TriangularMatrix(int size, TriKind kind, const T* data)
    : SquareMatrix<T>(size), kind_(kind) {
    if (size > 0 && data == nullptr) {
        throw lab2::InvalidArgument("data pointer is null");
    }
    if (data != nullptr) {
        Validate(data);
    }
    const int total = size * size;
    for (int i = 0; i < total; ++i) {
        this->data_.Set(i, data[i]);
    }
}

template <class T>
TriangularMatrix<T>::TriangularMatrix(const TriangularMatrix<T>& other)
    : SquareMatrix<T>(other), kind_(other.kind_) {}

template <class T>
TriangularMatrix<T>& TriangularMatrix<T>::operator=(const TriangularMatrix<T>& other) {
    SquareMatrix<T>::operator=(other);
    kind_ = other.kind_;
    return *this;
}

template <class T>
void TriangularMatrix<T>::Set(int row, int col, const T& value) {
    this->CheckBounds(row, col);
    if (!IsAllowed(row, col) && !(value == T())) {
        throw lab2::InvalidArgument("write outside triangular part");
    }
    this->data_.Set(this->Index(row, col), value);
}

template <class T>
void TriangularMatrix<T>::AddMatrix(const Matrix<T>& other) {
    this->CheckSameShape(other);
    const TriangularMatrix<T>* tri = dynamic_cast<const TriangularMatrix<T>*>(&other);
    if (tri == nullptr || tri->GetKind() != kind_) {
        throw lab2::InvalidArgument("triangular kinds differ");
    }
    const int n = this->GetSize();
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (IsAllowed(r, c)) {
                this->data_.Set(this->Index(r, c),
                                this->data_.Get(this->Index(r, c)) + other.Get(r, c));
            }
        }
    }
}

}  // namespace lab3

#endif
