#ifndef LAB3_SPARSE_MATRIX_TPP
#define LAB3_SPARSE_MATRIX_TPP

#include <cmath>

namespace lab3 {

template <class T>
SparseMatrix<T>::SparseMatrix(int rows, int cols)
    : Matrix<T>(rows, cols),
      entries_(new lab2::MutableArraySequence<SparseEntry<T>>()),
      zero_(T()) {}

template <class T>
SparseMatrix<T>::SparseMatrix(int rows, int cols, const T* data)
    : Matrix<T>(rows, cols),
      entries_(new lab2::MutableArraySequence<SparseEntry<T>>()),
      zero_(T()) {
    if (rows * cols > 0 && data == nullptr) {
        delete entries_;
        throw lab2::InvalidArgument("data pointer is null");
    }
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const T& v = data[r * cols + c];
            if (!(v == T())) {
                entries_->Append(SparseEntry<T>(r, c, v));
            }
        }
    }
}

template <class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& other)
    : Matrix<T>(other.rows_, other.cols_),
      entries_(new lab2::MutableArraySequence<SparseEntry<T>>()),
      zero_(T()) {
    const int len = other.entries_->GetLength();
    for (int i = 0; i < len; ++i) {
        entries_->Append(other.entries_->Get(i));
    }
}

template <class T>
SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix<T>& other) {
    if (this == &other) {
        return *this;
    }
    Matrix<T>::operator=(other);
    delete entries_;
    entries_ = new lab2::MutableArraySequence<SparseEntry<T>>();
    const int len = other.entries_->GetLength();
    for (int i = 0; i < len; ++i) {
        entries_->Append(other.entries_->Get(i));
    }
    zero_ = T();
    return *this;
}

template <class T>
SparseMatrix<T>::~SparseMatrix() {
    delete entries_;
}

template <class T>
int SparseMatrix<T>::FindIdx(int row, int col) const {
    const int len = entries_->GetLength();
    for (int i = 0; i < len; ++i) {
        const SparseEntry<T> e = entries_->Get(i);
        if (e.row == row && e.col == col) {
            return i;
        }
    }
    return -1;
}

template <class T>
void SparseMatrix<T>::EraseAt(int idx) {
    const int last = entries_->GetLength() - 1;
    if (idx < last) {
        entries_->Set(idx, entries_->Get(last));
    }
    lab2::MutableArraySequence<SparseEntry<T>>* next =
        new lab2::MutableArraySequence<SparseEntry<T>>();
    for (int i = 0; i < last; ++i) {
        next->Append(entries_->Get(i));
    }
    delete entries_;
    entries_ = next;
}

template <class T>
const T& SparseMatrix<T>::Get(int row, int col) const {
    this->CheckBounds(row, col);
    const int idx = FindIdx(row, col);
    if (idx < 0) {
        zero_ = T();
        return zero_;
    }
    zero_ = entries_->Get(idx).value;
    return zero_;
}

template <class T>
void SparseMatrix<T>::Set(int row, int col, const T& value) {
    this->CheckBounds(row, col);
    const int idx = FindIdx(row, col);
    if (value == T()) {
        if (idx >= 0) {
            EraseAt(idx);
        }
    } else {
        if (idx >= 0) {
            SparseEntry<T> e = entries_->Get(idx);
            e.value = value;
            entries_->Set(idx, e);
        } else {
            entries_->Append(SparseEntry<T>(row, col, value));
        }
    }
}

template <class T>
void SparseMatrix<T>::AddMatrix(const Matrix<T>& other) {
    this->CheckSameShape(other);
    for (int r = 0; r < this->rows_; ++r) {
        for (int c = 0; c < this->cols_; ++c) {
            const T sum = Get(r, c) + other.Get(r, c);
            Set(r, c, sum);
        }
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
    if (this->cols_ != other.rows_) {
        throw lab2::InvalidArgument("matrix shapes incompatible for multiplication");
    }
    SparseMatrix<T> result(this->rows_, other.cols_);
    const int la = entries_->GetLength();
    const int lb = other.entries_->GetLength();
    for (int i = 0; i < la; ++i) {
        const SparseEntry<T> a = entries_->Get(i);
        for (int j = 0; j < lb; ++j) {
            const SparseEntry<T> b = other.entries_->Get(j);
            if (a.col == b.row) {
                result.Set(a.row, b.col, result.Get(a.row, b.col) + a.value * b.value);
            }
        }
    }
    return result;
}

template <class T>
int SparseMatrix<T>::GetNnz() const {
    return entries_->GetLength();
}

}  // namespace lab3

#endif
