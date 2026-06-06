#ifndef LAB2_ARRAY_SEQUENCE_TPP
#define LAB2_ARRAY_SEQUENCE_TPP

namespace lab2 {

template <class T>
ArraySequence<T>::ArraySequence() : items_() {}

template <class T>
ArraySequence<T>::ArraySequence(const T* items, int count) : items_(items, count) {}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& source) : items_(source) {}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) : items_(other.items_) {}

template <class T>
ArraySequence<T>& ArraySequence<T>::operator=(const ArraySequence<T>& other) {
    if (this != &other) items_ = other.items_;
    return *this;
}

template <class T>
ArraySequence<T>::~ArraySequence() {}

template <class T>
int ArraySequence<T>::GetLength() const { return items_.GetSize(); }

template <class T>
T ArraySequence<T>::GetFirst() const {
    if (items_.GetSize() == 0) throw EmptyContainer("sequence is empty");
    return items_.Get(0);
}

template <class T>
T ArraySequence<T>::GetLast() const {
    if (items_.GetSize() == 0) throw EmptyContainer("sequence is empty");
    return items_.Get(items_.GetSize() - 1);
}

template <class T>
T ArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= items_.GetSize())
        throw IndexOutOfRange("sequence index out of range");
    return items_.Get(index);
}

template <class T>
void ArraySequence<T>::AppendInternal(const T& item) {
    items_.Resize(items_.GetSize() + 1);
    items_.Set(items_.GetSize() - 1, item);
}

template <class T>
void ArraySequence<T>::PrependInternal(const T& item) {
    const int sz = items_.GetSize();
    items_.Resize(sz + 1);
    for (int i = sz; i > 0; --i) items_.Set(i, items_.Get(i - 1));
    items_.Set(0, item);
}

template <class T>
void ArraySequence<T>::InsertAtInternal(const T& item, int index) {
    if (index < 0 || index > items_.GetSize())
        throw IndexOutOfRange("insert index out of range");
    const int sz = items_.GetSize();
    items_.Resize(sz + 1);
    for (int i = sz; i > index; --i) items_.Set(i, items_.Get(i - 1));
    items_.Set(index, item);
}

template <class T>
Sequence<T>* ArraySequence<T>::Append(const T& item) {
    ArraySequence<T>* inst = Instance();
    inst->AppendInternal(item);
    return inst;
}

template <class T>
Sequence<T>* ArraySequence<T>::Prepend(const T& item) {
    ArraySequence<T>* inst = Instance();
    inst->PrependInternal(item);
    return inst;
}

template <class T>
Sequence<T>* ArraySequence<T>::InsertAt(const T& item, int index) {
    ArraySequence<T>* inst = Instance();
    inst->InsertAtInternal(item, index);
    return inst;
}

template <class T>
Sequence<T>* ArraySequence<T>::Set(int index, const T& value) {
    if (index < 0 || index >= items_.GetSize())
        throw IndexOutOfRange("set index out of range");
    ArraySequence<T>* inst = Instance();
    inst->items_.Set(index, value);
    return inst;
}

template <class T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int start, int end) const {
    if (start < 0 || end >= items_.GetSize() || start > end)
        throw IndexOutOfRange("subsequence range invalid");
    ArraySequence<T>* result = MakeEmpty();
    for (int i = start; i <= end; ++i) result->AppendInternal(items_.Get(i));
    return result;
}

template <class T>
Sequence<T>* ArraySequence<T>::Concat(const Sequence<T>* other) {
    ArraySequence<T>* result = MakeEmpty();
    for (int i = 0; i < items_.GetSize(); ++i) result->AppendInternal(items_.Get(i));
    for (int i = 0; i < other->GetLength(); ++i) result->AppendInternal(other->Get(i));
    return result;
}

template <class T>
IEnumerator<T>* ArraySequence<T>::GetEnumerator() const {
    return new ArrayEnumerator(this);
}

template <class T>
MutableArraySequence<T>::MutableArraySequence() : ArraySequence<T>() {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(const T* items, int count)
    : ArraySequence<T>(items, count) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(const DynamicArray<T>& source)
    : ArraySequence<T>(source) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(const MutableArraySequence<T>& other)
    : ArraySequence<T>(other) {}

template <class T>
Sequence<T>* MutableArraySequence<T>::Clone() const {
    return new MutableArraySequence<T>(*this);
}

template <class T>
ArraySequence<T>* MutableArraySequence<T>::Instance() { return this; }

template <class T>
ArraySequence<T>* MutableArraySequence<T>::MakeEmpty() const {
    return new MutableArraySequence<T>();
}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence() : ArraySequence<T>() {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const T* items, int count)
    : ArraySequence<T>(items, count) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const DynamicArray<T>& source)
    : ArraySequence<T>(source) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& other)
    : ArraySequence<T>(other) {}

template <class T>
Sequence<T>* ImmutableArraySequence<T>::Clone() const {
    return new ImmutableArraySequence<T>(*this);
}

template <class T>
ArraySequence<T>* ImmutableArraySequence<T>::Instance() {
    return new ImmutableArraySequence<T>(*this);
}

template <class T>
ArraySequence<T>* ImmutableArraySequence<T>::MakeEmpty() const {
    return new ImmutableArraySequence<T>();
}

}  // namespace lab2

#endif
