#ifdef _MSC_VER
__pragma("once")
#else
_Pragma("once")
#endif

#include "inc.h"

NS_BEGIN(elloop)

template <typename T> class Stack;

template <typename T>
struct ListNode {

	ListNode(const T & data, ListNode<T> * next = nullptr) 
        : data_(data), next_(next) { }

	~ListNode() { }

	T           data_;
	ListNode   *next_;
};

template <typename T>
class Stack {
public:
	typedef ListNode<T> NodeType;

	Stack() : top_(nullptr) {}

	// disallow copy.
	Stack(const Stack & rhs) = delete;

	// disallow move.
	// stack(const stack && rhs) = delete;

	T top() noexcept {
		assert(top_ != nullptr);
		return top_->data_;
	}

	void pop() {
		if (top_ != nullptr) {
			auto oldTop = top_;
			top_ = top_->next_;
            EL_SAFE_DELETE(oldTop);
		}
	}

	void push(const T & elem) {
		top_ = new NodeType(elem, top_);
	}

	~Stack() {
		clear();
	}

	void clear() {
		auto temp = top_;
		while (temp) {
			top_ = temp->next_;
			delete temp;
			temp = top_;
		}
	}

	bool empty() const {
		return (top_ == nullptr);
	}

	// testing how to define a template member function outside of a class.
	void test();
private:
	NodeType* top_;
}; // end class stack;

NS_END(elloop)

