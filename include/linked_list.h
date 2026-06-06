#ifndef LAB2_LINKED_LIST_H
#define LAB2_LINKED_LIST_H
#include "errors.h"
namespace lab2 {
template <class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(const T* items, int count);
    LinkedList(const LinkedList<T>& other);
    LinkedList<T>& operator=(const LinkedList<T>& other);
    ~LinkedList();
    int  GetLength() const;
    T    GetFirst() const;
    T    GetLast() const;
    T    Get(int index) const;
    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(const T& item, int index);
    void Set(int index, const T& value);
    LinkedList<T>* GetSublist(int start, int end) const;
    LinkedList<T>* Concat(const LinkedList<T>* other) const;
private:
    struct Node { T data; Node* next; };
    Node* head_;
    int   size_;
    void  Clear();
};
}  // namespace lab2
#include "linked_list.tpp"
#endif
