#ifndef LAB2_SEQUENCE_ALGORITHMS_H
#define LAB2_SEQUENCE_ALGORITHMS_H
#include "sequence.h"
namespace lab2 {
template <class T, class R>
R Reduce(R (*f)(R, T), const Sequence<T>* seq, R init);
template <class T>
Sequence<T>* Where(bool (*pred)(T), const Sequence<T>* seq);
}
#include "sequence_algorithms.tpp"
#endif
