#ifdef _MSC_VER
__pragma("once")
#else
_Pragma("once")
#endif

#include "inc.h"

NS_BEGIN(elloop)

template <typename T> class Stack;

template <typename T>
class ListNode {
	ListNode(const T& data, ListNode<T>* next = nullptr) 
        : data_(data), next_(next)
    { }

	~ListNode() { }
	T           data_;
	ListNode*   next_;
	friend      Stack<T>;
};

template <typename T>
class Stack {
public:
	typedef ListNode<T> NodeType;

	Stack() : head_(nullptr) {}

	// disallow copy.
	Stack(const Stack& rhs) = delete;
	// disallow move.
	// stack(const stack && rhs) = delete;

	T top() noexcept {
		assert(head_ != nullptr);
		return head_->data_;
	}

	void pop() {
		if (head_ != nullptr) {
			auto oldTop = head_;
			head_ = head_->next_;
            EL_SAFE_DELETE(oldTop);
		}
	}

	void push(const T& elem) {
		head_ = new NodeType(elem, head_);
	}

	~Stack() {
		clear();
	}

	void clear() {
		auto temp = head_;
		while (temp) {
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
	NodeType* head_;
}; // end class stack;

NS_END(elloop)