#ifndef LAB2_DYNAMIC_ARRAY_TPP
#define LAB2_DYNAMIC_ARRAY_TPP

#include <algorithm>
#include <new>

namespace lab2 {

template <class T>
DynamicArray<T>::DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}

template <class T>
DynamicArray<T>::DynamicArray(int size) : data_(nullptr), size_(0), capacity_(0) {
    if (size < 0) throw InvalidArgument("negative size");
    if (size > 0) {
        data_     = new T[size]();
        size_     = size;
        capacity_ = size;
    }
}

template <class T>
DynamicArray<T>::DynamicArray(const T* items, int count)
    : data_(nullptr), size_(0), capacity_(0) {
    if (count < 0) throw InvalidArgument("negative count");
    if (count == 0) return;
    if (items == nullptr) throw InvalidArgument("null pointer");
    data_     = new T[count];
    size_     = count;
    capacity_ = count;
    for (int i = 0; i < count; ++i) data_[i] = items[i];
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : data_(nullptr), size_(0), capacity_(0) {
    if (other.size_ == 0) return;
    data_     = new T[other.size_];
    size_     = other.size_;
    capacity_ = other.size_;
    for (int i = 0; i < size_; ++i) data_[i] = other.data_[i];
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this == &other) return *this;
    DynamicArray<T> tmp(other);
    Swap(tmp);
    return *this;
}

template <class T>
DynamicArray<T>::~DynamicArray() { delete[] data_; }

template <class T>
void DynamicArray<T>::Swap(DynamicArray<T>& other) {
    std::swap(data_,     other.data_);
    std::swap(size_,     other.size_);
    std::swap(capacity_, other.capacity_);
}

template <class T>
int DynamicArray<T>::GetSize() const { return size_; }

template <class T>
int DynamicArray<T>::GetCapacity() const { return capacity_; }

template <class T>
void DynamicArray<T>::EnsureIndexValid(int index) const {
    if (index < 0 || index >= size_)
        throw IndexOutOfRange("index out of range");
}

template <class T>
void DynamicArray<T>::EnsureCapacity(int min_capacity) {
    if (min_capacity <= capacity_) return;
    int new_cap = (capacity_ == 0) ? 1 : capacity_;
    while (new_cap < min_capacity) new_cap *= 2;
    T* new_data = new T[new_cap]();
    for (int i = 0; i < size_; ++i) new_data[i] = data_[i];
    delete[] data_;
    data_     = new_data;
    capacity_ = new_cap;
}

template <class T>
T& DynamicArray<T>::Get(int index) { EnsureIndexValid(index); return data_[index]; }

template <class T>
const T& DynamicArray<T>::Get(int index) const { EnsureIndexValid(index); return data_[index]; }

template <class T>
void DynamicArray<T>::Set(int index, const T& value) {
    EnsureIndexValid(index);
    data_[index] = value;
}

template <class T>
void DynamicArray<T>::Resize(int new_size) {
    if (new_size < 0) throw InvalidArgument("negative size");
    EnsureCapacity(new_size);
    if (new_size > size_) {
        for (int i = size_; i < new_size; ++i) data_[i] = T();
    }
    size_ = new_size;
}

template <class T>
T& DynamicArray<T>::operator[](int index) { return Get(index); }

template <class T>
const T& DynamicArray<T>::operator[](int index) const { return Get(index); }

}  // namespace lab2

#endif
