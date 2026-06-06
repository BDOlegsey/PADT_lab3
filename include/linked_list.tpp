#ifndef LAB2_LINKED_LIST_TPP
#define LAB2_LINKED_LIST_TPP
namespace lab2 {
template <class T> LinkedList<T>::LinkedList() : head_(nullptr), size_(0) {}
template <class T>
LinkedList<T>::LinkedList(const T* items, int count) : head_(nullptr), size_(0) {
    for (int i = 0; i < count; ++i) Append(items[i]);
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head_(nullptr), size_(0) {
    Node* cur = other.head_;
    while (cur) { Append(cur->data); cur = cur->next; }
}
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this == &other) return *this;
    Clear();
    Node* cur = other.head_;
    while (cur) { Append(cur->data); cur = cur->next; }
    return *this;
}
template <class T>
LinkedList<T>::~LinkedList() { Clear(); }
template <class T>
void LinkedList<T>::Clear() {
    while (head_) { Node* n = head_->next; delete head_; head_ = n; }
    size_ = 0;
}
template <class T>
int LinkedList<T>::GetLength() const { return size_; }
template <class T>
T LinkedList<T>::GetFirst() const {
    if (!head_) throw EmptyContainer("list is empty");
    return head_->data;
}
template <class T>
T LinkedList<T>::GetLast() const {
    if (!head_) throw EmptyContainer("list is empty");
    Node* cur = head_;
    while (cur->next) cur = cur->next;
    return cur->data;
}
template <class T>
T LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= size_) throw IndexOutOfRange("list index");
    Node* cur = head_;
    for (int i = 0; i < index; ++i) cur = cur->next;
    return cur->data;
}
template <class T>
void LinkedList<T>::Append(const T& item) {
    Node* n = new Node{item, nullptr};
    if (!head_) { head_ = n; } else {
        Node* cur = head_;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }
    ++size_;
}
template <class T>
void LinkedList<T>::Prepend(const T& item) {
    head_ = new Node{item, head_};
    ++size_;
}
template <class T>
void LinkedList<T>::InsertAt(const T& item, int index) {
    if (index < 0 || index > size_) throw IndexOutOfRange("insert index");
    if (index == 0) { Prepend(item); return; }
    Node* cur = head_;
    for (int i = 0; i < index - 1; ++i) cur = cur->next;
    cur->next = new Node{item, cur->next};
    ++size_;
}
template <class T>
void LinkedList<T>::Set(int index, const T& value) {
    if (index < 0 || index >= size_) throw IndexOutOfRange("set index");
    Node* cur = head_;
    for (int i = 0; i < index; ++i) cur = cur->next;
    cur->data = value;
}
template <class T>
LinkedList<T>* LinkedList<T>::GetSublist(int start, int end) const {
    if (start < 0 || end >= size_ || start > end) throw IndexOutOfRange("sublist range");
    LinkedList<T>* result = new LinkedList<T>();
    for (int i = start; i <= end; ++i) result->Append(Get(i));
    return result;
}
template <class T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T>* other) const {
    LinkedList<T>* result = new LinkedList<T>(*this);
    for (int i = 0; i < other->GetLength(); ++i) result->Append(other->Get(i));
    return result;
}
}  // namespace lab2
#endif
