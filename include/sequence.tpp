#ifndef LAB2_SEQUENCE_TPP
#define LAB2_SEQUENCE_TPP

namespace lab2 {

template <class T>
Option<T> Sequence<T>::TryGetFirst(Predicate predicate) const {
    for (int i = 0; i < GetLength(); ++i) {
        T item = Get(i);
        if (predicate == nullptr || predicate(item)) {
            return Option<T>(item);
        }
    }
    return Option<T>();
}

template <class T>
Option<T> Sequence<T>::TryGetLast(Predicate predicate) const {
    for (int i = GetLength() - 1; i >= 0; --i) {
        T item = Get(i);
        if (predicate == nullptr || predicate(item)) {
            return Option<T>(item);
        }
    }
    return Option<T>();
}

}  // namespace lab2

#endif
