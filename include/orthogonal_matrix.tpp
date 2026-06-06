#ifndef LAB3_ORTHOGONAL_MATRIX_TPP
#define LAB3_ORTHOGONAL_MATRIX_TPP

#include <cmath>

namespace lab3 {

template <class T>
OrthogonalMatrix<T>::OrthogonalMatrix(int size) : SquareMatrix<T>(size) {}

template <class T>
OrthogonalMatrix<T>::OrthogonalMatrix(int size, const T* data, double eps)
    : SquareMatrix<T>(size, data) {
    if (size > 0 && !IsOrthogonal(eps)) {
        throw lab2::InvalidArgument("matrix is not orthogonal");
    }
}

template <class T>
OrthogonalMatrix<T>::OrthogonalMatrix(const OrthogonalMatrix<T>& other)
    : SquareMatrix<T>(other) {}

template <class T>
OrthogonalMatrix<T>& OrthogonalMatrix<T>::operator=(const OrthogonalMatrix<T>& other) {
    SquareMatrix<T>::operator=(other);
    return *this;
}

template <class T>
bool OrthogonalMatrix<T>::IsOrthogonal(double eps) const {
    const int n = this->GetSize();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double dot = 0.0;
            for (int k = 0; k < n; ++k) {
                dot += static_cast<double>(this->Get(k, i)) *
                       static_cast<double>(this->Get(k, j));
            }
            const double expected = (i == j) ? 1.0 : 0.0;
            if (std::fabs(dot - expected) > eps) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace lab3

#endif
