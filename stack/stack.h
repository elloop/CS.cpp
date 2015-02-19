_Pragma("once")

#include "inc.h"

namespace elloop {

template <typename T> class stack;

template <typename T>
class list_node {
    list_node(const T & data = nullptr, list_node<T> * next = nullptr) : data_(data), next_(next) { }
    ~list_node() { }
    T data_;
    list_node * next_;
    friend stack<T>;
};

template <typename T>
class stack {
    public:
        typedef list_node<T> node_type;

        stack() : head_(nullptr) {}

        // disallow copy.
        stack(const stack & rhs) = delete;
        // disallow move.
        // stack(const stack && rhs) = delete;

        T top() noexcept(false) {
            assert(head_ != nullptr);
            if (head_ != nullptr) {
                return head_->data_;
            }
        }

        void pop() {
            if (head_ != nullptr) {
                auto old_top = head_;
                head_ = head_->next_;
                delete old_top;
                old_top = nullptr;
            }
        }

        bool push(const T & elem) {
            head_ = new node_type(elem, head_);
        }

        ~stack() {
            // DEBUG_LOG("deleting stack ...");
            clear();
        }

        void clear() {
            // DEBUG_LOG("clearig stack ...");
            auto temp = head_;
            while (temp != nullptr) {
                head_ = temp->next_;
                delete temp;
                temp = head_;
            }
        }

        bool empty() const {
            return (head_ == nullptr);
        }

        // testing how to define a template member function outside of a class.
        void test();
    private:
        node_type* head_;
}; // end class stack;

template <typename T>
void stack<T>::test() {
    pcln("this is in stack<T> test().");
}


} // end namespace elloop;
