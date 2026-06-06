#ifndef LAB2_LIST_SEQUENCE_TPP
#define LAB2_LIST_SEQUENCE_TPP
namespace lab2 {
template <class T> ListSequence<T>::ListSequence() {}
template <class T>
ListSequence<T>::ListSequence(const T* items, int count) : list_(items, count) {}
template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) : list_(other.list_) {}
template <class T> int ListSequence<T>::GetLength() const { return list_.GetLength(); }
template <class T> T   ListSequence<T>::GetFirst()  const { return list_.GetFirst(); }
template <class T> T   ListSequence<T>::GetLast()   const { return list_.GetLast(); }
template <class T> T   ListSequence<T>::Get(int i)  const { return list_.Get(i); }
template <class T>
Sequence<T>* ListSequence<T>::Append(const T& item) { list_.Append(item); return this; }
template <class T>
Sequence<T>* ListSequence<T>::Prepend(const T& item) { list_.Prepend(item); return this; }
template <class T>
Sequence<T>* ListSequence<T>::InsertAt(const T& item, int i) { list_.InsertAt(item, i); return this; }
template <class T>
Sequence<T>* ListSequence<T>::Set(int i, const T& v) { list_.Set(i, v); return this; }
template <class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int s, int e) const {
    LinkedList<T>* sub = list_.GetSublist(s, e);
    ListSequence<T>* r = new ListSequence<T>();
    for (int i = 0; i < sub->GetLength(); ++i) r->list_.Append(sub->Get(i));
    delete sub;
    return r;
}
template <class T>
Sequence<T>* ListSequence<T>::Concat(const Sequence<T>* other) {
    ListSequence<T>* r = new ListSequence<T>(*this);
    for (int i = 0; i < other->GetLength(); ++i) r->list_.Append(other->Get(i));
    return r;
}
template <class T>
Sequence<T>* ListSequence<T>::Clone() const { return new ListSequence<T>(*this); }
template <class T>
IEnumerator<T>* ListSequence<T>::GetEnumerator() const { return new ListEnumerator(this); }
}  // namespace lab2
#endif
