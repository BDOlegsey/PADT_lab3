#ifndef LAB3_SPARSE_MATRIX_TPP
#define LAB3_SPARSE_MATRIX_TPP

#include <cmath>

namespace lab3 {

template <class T>
void SparseMatrix<T>::CheckBounds(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_)
        throw lab2::IndexOutOfRange("sparse matrix index out of range");
}

template <class T>
void SparseMatrix<T>::CheckSameShape(const SparseMatrix<T>& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw lab2::InvalidArgument("matrix shapes differ");
}

template <class T>
SparseMatrix<T>::SparseMatrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols),
      entries_(new lab2::MutableArraySequence<SparseEntry<T>>()),
      zero_(T()) {}

template <class T>
SparseMatrix<T>::SparseMatrix(size_t rows, size_t cols, const T* data)
    : rows_(rows), cols_(cols),
      entries_(new lab2::MutableArraySequence<SparseEntry<T>>()),
      zero_(T()) {
    if (rows * cols > 0 && data == nullptr) {
        delete entries_;
        throw lab2::InvalidArgument("data pointer is null");
    }
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            const T& v = data[r * cols + c];
            if (!(v == T())) entries_->Append(SparseEntry<T>(r, c, v));
        }
    }
}

template <class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& other)
    : rows_(other.rows_), cols_(other.cols_),
      entries_(new lab2::MutableArraySequence<SparseEntry<T>>()),
      zero_(T()) {
    const int len = other.entries_->GetLength();
    for (int i = 0; i < len; ++i) entries_->Append(other.entries_->Get(i));
}

template <class T>
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix<T>& other) {
    if (this == &other) return *this;
    rows_ = other.rows_;
    cols_ = other.cols_;
    delete entries_;
    entries_ = new lab2::MutableArraySequence<SparseEntry<T>>();
    const int len = other.entries_->GetLength();
    for (int i = 0; i < len; ++i) entries_->Append(other.entries_->Get(i));
    zero_ = T();
    return *this;
}

template <class T>
SparseMatrix<T>::~SparseMatrix() {
    delete entries_;
}

template <class T>
size_t SparseMatrix<T>::FindIdx(size_t row, size_t col) const {
    const int len = entries_->GetLength();
    for (int i = 0; i < len; ++i) {
        const SparseEntry<T> e = entries_->Get(i);
        if (e.row == row && e.col == col) return static_cast<size_t>(i);
    }
    return kNotFound;
}

template <class T>
void SparseMatrix<T>::EraseAt(size_t idx) {
    const int last = entries_->GetLength() - 1;
    const int sidx = static_cast<int>(idx);
    if (sidx < last) entries_->Set(sidx, entries_->Get(last));
    lab2::MutableArraySequence<SparseEntry<T>>* next =
        new lab2::MutableArraySequence<SparseEntry<T>>();
    for (int i = 0; i < last; ++i) next->Append(entries_->Get(i));
    delete entries_;
    entries_ = next;
}

template <class T>
const T& SparseMatrix<T>::Get(size_t row, size_t col) const {
    CheckBounds(row, col);
    const size_t idx = FindIdx(row, col);
    if (idx == kNotFound) { zero_ = T(); return zero_; }
    zero_ = entries_->Get(static_cast<int>(idx)).value;
    return zero_;
}

template <class T>
void SparseMatrix<T>::Set(size_t row, size_t col, const T& value) {
    CheckBounds(row, col);
    const size_t idx = FindIdx(row, col);
    if (value == T()) {
        if (idx != kNotFound) EraseAt(idx);
    } else {
        if (idx != kNotFound) {
            SparseEntry<T> e = entries_->Get(static_cast<int>(idx));
            e.value = value;
            entries_->Set(static_cast<int>(idx), e);
        } else {
            entries_->Append(SparseEntry<T>(row, col, value));
        }
    }
}

template <class T>
void SparseMatrix<T>::AddMatrix(const SparseMatrix<T>& other) {
    CheckSameShape(other);
    const int len = other.entries_->GetLength();
    for (int i = 0; i < len; ++i) {
        const SparseEntry<T> e = other.entries_->Get(i);
        const T cur = Get(e.row, e.col);
        Set(e.row, e.col, cur + e.value);
    }
}

template <class T>
void SparseMatrix<T>::MulScalar(const T& scalar) {
    if (scalar == T()) {
        delete entries_;
        entries_ = new lab2::MutableArraySequence<SparseEntry<T>>();
        return;
    }
    const int len = entries_->GetLength();
    for (int i = 0; i < len; ++i) {
        SparseEntry<T> e = entries_->Get(i);
        e.value = e.value * scalar;
        entries_->Set(i, e);
    }
}

template <class T>
double SparseMatrix<T>::Norm() const {
    double acc = 0.0;
    const int len = entries_->GetLength();
    for (int i = 0; i < len; ++i) {
        const double v = static_cast<double>(entries_->Get(i).value);
        acc += v * v;
    }
    return std::sqrt(acc);
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::Multiply(const SparseMatrix<T>& other) const {
    if (cols_ != other.rows_)
        throw lab2::InvalidArgument("matrix shapes incompatible for multiplication");
    SparseMatrix<T> result(rows_, other.cols_);
    const int la = entries_->GetLength();
    const int lb = other.entries_->GetLength();
    for (int i = 0; i < la; ++i) {
        const SparseEntry<T> a = entries_->Get(i);
        for (int j = 0; j < lb; ++j) {
            const SparseEntry<T> b = other.entries_->Get(j);
            if (a.col == b.row) {
                const T cur = result.Get(a.row, b.col);
                result.Set(a.row, b.col, cur + a.value * b.value);
            }
        }
    }
    return result;
}

template <class T>
size_t SparseMatrix<T>::GetNnz() const {
    return static_cast<size_t>(entries_->GetLength());
}

}  // namespace lab3

#endif
