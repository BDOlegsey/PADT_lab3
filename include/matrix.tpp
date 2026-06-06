#ifndef LAB3_MATRIX_TPP
#define LAB3_MATRIX_TPP

#include <cmath>

namespace lab3 {

template <class T>
Matrix<T>::Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_() {
    if (rows < 0 || cols < 0) throw lab2::InvalidArgument("matrix size is negative");
    if ((rows == 0) != (cols == 0)) throw lab2::InvalidArgument("matrix dimensions inconsistent");
    data_.Resize(rows * cols);
}

template <class T>
Matrix<T>::Matrix(int rows, int cols, const T* values)
    : rows_(rows), cols_(cols), data_() {
    if (rows < 0 || cols < 0) throw lab2::InvalidArgument("matrix size is negative");
    if ((rows == 0) != (cols == 0)) throw lab2::InvalidArgument("matrix dimensions inconsistent");
    const int total = rows * cols;
    if (total > 0 && values == nullptr) throw lab2::InvalidArgument("data pointer is null");
    data_.Resize(total);
    for (int i = 0; i < total; ++i) data_.Set(i, values[i]);
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this == &other) return *this;
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = other.data_;
    return *this;
}

template <class T>
void Matrix<T>::CheckBounds(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw lab2::IndexOutOfRange("matrix index out of range");
}

template <class T>
void Matrix<T>::CheckRow(int row) const {
    if (row < 0 || row >= rows_) throw lab2::IndexOutOfRange("row index out of range");
}

template <class T>
void Matrix<T>::CheckCol(int col) const {
    if (col < 0 || col >= cols_) throw lab2::IndexOutOfRange("column index out of range");
}

template <class T>
void Matrix<T>::CheckSameShape(const Matrix<T>& other) const {
    if (rows_ != other.GetRows() || cols_ != other.GetCols())
        throw lab2::InvalidArgument("matrix shapes differ");
}

template <class T>
const T& Matrix<T>::Get(int row, int col) const {
    CheckBounds(row, col);
    return data_.Get(Index(row, col));
}

template <class T>
void Matrix<T>::Set(int row, int col, const T& value) {
    CheckBounds(row, col);
    data_.Set(Index(row, col), value);
}

template <class T>
void Matrix<T>::AddMatrix(const Matrix<T>& other) {
    CheckSameShape(other);
    const int total = rows_ * cols_;
    for (int i = 0; i < total; ++i)
        data_.Set(i, data_.Get(i) + other.data_.Get(i));
}

template <class T>
void Matrix<T>::MulScalar(const T& scalar) {
    const int total = rows_ * cols_;
    for (int i = 0; i < total; ++i) data_.Set(i, data_.Get(i) * scalar);
}

template <class T>
double Matrix<T>::Norm() const {
    double acc = 0.0;
    const int total = rows_ * cols_;
    for (int i = 0; i < total; ++i) {
        const double v = static_cast<double>(data_.Get(i));
        acc += v * v;
    }
    return std::sqrt(acc);
}

template <class T>
void Matrix<T>::SwapRows(int i, int j) {
    CheckRow(i); CheckRow(j);
    if (i == j) return;
    for (int c = 0; c < cols_; ++c) {
        T tmp = data_.Get(Index(i, c));
        data_.Set(Index(i, c), data_.Get(Index(j, c)));
        data_.Set(Index(j, c), tmp);
    }
}

template <class T>
void Matrix<T>::SwapCols(int i, int j) {
    CheckCol(i); CheckCol(j);
    if (i == j) return;
    for (int r = 0; r < rows_; ++r) {
        T tmp = data_.Get(Index(r, i));
        data_.Set(Index(r, i), data_.Get(Index(r, j)));
        data_.Set(Index(r, j), tmp);
    }
}

template <class T>
void Matrix<T>::MulRow(int row, const T& factor) {
    CheckRow(row);
    for (int c = 0; c < cols_; ++c)
        data_.Set(Index(row, c), data_.Get(Index(row, c)) * factor);
}

template <class T>
void Matrix<T>::MulCol(int col, const T& factor) {
    CheckCol(col);
    for (int r = 0; r < rows_; ++r)
        data_.Set(Index(r, col), data_.Get(Index(r, col)) * factor);
}

template <class T>
void Matrix<T>::AddRowMultiplied(int target, int source, const T& factor) {
    CheckRow(target); CheckRow(source);
    if (target == source) throw lab2::InvalidArgument("target and source rows must differ");
    for (int c = 0; c < cols_; ++c)
        data_.Set(Index(target, c),
                  data_.Get(Index(target, c)) + data_.Get(Index(source, c)) * factor);
}

template <class T>
void Matrix<T>::AddColMultiplied(int target, int source, const T& factor) {
    CheckCol(target); CheckCol(source);
    if (target == source) throw lab2::InvalidArgument("target and source columns must differ");
    for (int r = 0; r < rows_; ++r)
        data_.Set(Index(r, target),
                  data_.Get(Index(r, target)) + data_.Get(Index(r, source)) * factor);
}

template <class T>
bool Matrix<T>::Equals(const Matrix<T>& other) const {
    if (rows_ != other.GetRows() || cols_ != other.GetCols()) return false;
    const int total = rows_ * cols_;
    for (int i = 0; i < total; ++i)
        if (!(data_.Get(i) == other.data_.Get(i))) return false;
    return true;
}

}  // namespace lab3

#endif
