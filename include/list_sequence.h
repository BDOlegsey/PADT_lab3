#ifndef LAB2_LIST_SEQUENCE_H
#define LAB2_LIST_SEQUENCE_H
#include "linked_list.h"
#include "sequence.h"
namespace lab2 {
template <class T>
class ListSequence : public Sequence<T> {
public:
    ListSequence();
    ListSequence(const T* items, int count);
    ListSequence(const ListSequence<T>& other);
    int  GetLength() const override;
    T    GetFirst() const override;
    T    GetLast() const override;
    T    Get(int index) const override;
    Sequence<T>* GetSubsequence(int, int) const override;
    Sequence<T>* Append(const T&) override;
    Sequence<T>* Prepend(const T&) override;
    Sequence<T>* InsertAt(const T&, int) override;
    Sequence<T>* Set(int, const T&) override;
    Sequence<T>* Concat(const Sequence<T>*) override;
    Sequence<T>* Clone() const override;
    IEnumerator<T>* GetEnumerator() const override;
private:
    LinkedList<T> list_;
    class ListEnumerator : public IEnumerator<T> {
    public:
        ListEnumerator(const ListSequence<T>* s) : seq_(s), idx_(-1) {}
        bool MoveNext() override { return ++idx_ < seq_->GetLength(); }
        T    Current() const override { return seq_->Get(idx_); }
        void Reset() override { idx_ = -1; }
    private:
        const ListSequence<T>* seq_; int idx_;
    };
};
}  // namespace lab2
#include "list_sequence.tpp"
#endif
