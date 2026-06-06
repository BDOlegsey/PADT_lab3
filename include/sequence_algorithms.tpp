#ifndef LAB2_SEQUENCE_ALGORITHMS_TPP
#define LAB2_SEQUENCE_ALGORITHMS_TPP
#include "array_sequence.h"
namespace lab2 {
template <class T, class R>
R Reduce(R (*f)(R, T), const Sequence<T>* seq, R init) {
    R acc = init;
    for (int i = 0; i < seq->GetLength(); ++i) acc = f(acc, seq->Get(i));
    return acc;
}
template <class T>
Sequence<T>* Where(bool (*pred)(T), const Sequence<T>* seq) {
    MutableArraySequence<T>* r = new MutableArraySequence<T>();
    for (int i = 0; i < seq->GetLength(); ++i) {
        T v = seq->Get(i);
        if (pred(v)) r->Append(v);
    }
    return r;
}
}  // namespace lab2
#endif
