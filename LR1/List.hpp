#pragma once
#include <cstdlib>
#include <stdexcept>

template <class T> class List {
   private:
    struct ListNode {
        T info_;
        ListNode* next_;
        ListNode ();
    };
    ListNode* first_;
    ListNode* current_;
    ListNode* last_;

   public:
    List ();
    ~List ();
    void push_back (T&);
    T& current ();
    bool isLast ();
    void go_next ();
    void go_first ();
    size_t get_size ();

    List& operator= (List&);
};

template <class T> List<T>::List () {
    first_= 0;
    current_= 0;
    last_= 0;
}

template <class T> List<T>& List<T>::operator= (List<T>& other) {
    while (first_) {
        ListNode* temp= first_->next_;
        delete first_;
        first_= temp;
    }
    first_= 0;
    current_= first_;
    last_= first_;

    other.go_first ();
    do {
        push_back (other.current ());
        other.go_next ();
    } while (!other.isLast());
    push_back (other.current ());
    other.go_first ();
    return *this;
}

template <class T> List<T>::~List () {
    while (first_) {
        ListNode* temp= first_->next_;
        delete first_;
        first_= temp;
    }
}

template <class T> List<T>::ListNode::ListNode () : next_ (0) {}

template <class T> size_t List<T>::get_size () {
    if (!first_)
        return 0;
    else {
        size_t count= 1;
        ListNode* current= first_;
        while (current->next_) {
            ++count;
            current= current->next_;
        }
        return count;
    }
}

template <class T> bool List<T>::isLast () { return (current_ == last_ ? true : false); }

template <class T> T& List<T>::current () {
    if (current_)
        return current_->info_;
    else
        throw std::out_of_range ("That's troubling.");
}

template <class T> void List<T>::go_first () { current_= first_; }

template <class T> void List<T>::go_next () {
    if (current_->next_) {
        current_= current_->next_;
    }
}

template <class T> void List<T>::push_back (T& info) {
    if (last_) {
        last_->next_= new ListNode;
        last_->next_->info_= info;
        last_= last_->next_;
    } else {
        first_= new ListNode;
        first_->info_= info;
        current_= first_;
        last_= first_;
    }
}
