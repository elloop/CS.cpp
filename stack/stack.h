_Pragma("once")

#include "inc.h"

template <typename T> class stack;

template <typename T>
class stack_node {
    stack_node(const T * data = nullptr, stack_node<T> * next = nullptr) : data_(data), next_(next) {
        elloop_test::p("create stack node: ");
        elloop_test::pln(data_);
    }
    ~stack_node() {
        elloop_test::p("delete stack node: ");
        elloop_test::pln(data_);
    }
    T* data_;
    stack_node * next_;
    friend stack<T>;
};

template <typename T>
class stack {
    public:
        typedef stack_node<T> node_type;

        stack() : head_(nullptr) {}
        T* peek() {
            if (head_ != nullptr) {
                return head_->data_;
            }
            else {
                return nullptr;
            }
        }

        T* pop() {
            if (head_ != nullptr) {
                auto old_top = head_;
                auto old_data = head_->data_;
                head_ = head_->next_;
                delete old_top;
                old_top = nullptr;
                return old_data;
            }
            else {
                return nullptr;
            }
        }

        bool push(const T * elem) {
            if (elem != nullptr) {
                auto * new_top = new node_type(elem, head_);
                head_ = new_top;
                return true;
            }
            return false;
        }

        ~stack() {
            clear();
        }

        void clear() {
            auto temp = head_;
            while (temp != nullptr) {
                head_ = temp->next_;
                delete temp;
                temp = head_;
            }
        }
    private:
        node_type* head_;
};
