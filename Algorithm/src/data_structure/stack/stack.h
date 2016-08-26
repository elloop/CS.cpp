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

	ListNode(const T &data, ListNode<T> *next = nullptr) 
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
    Stack(const Stack && rhs) = delete;

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

    void dump(const std::string& info) const {
        elloop::p(info);
        auto temp = top_;
        while (temp) {
            auto val = temp->data_;
            // if (std::is_same<decltype(val), char>::value) {
                // pv("%c -> ", val);
            // }
            // else {
                elloop::p(temp->data_); elloop::p(" -> ");
            // }
            temp = temp->next_;
        }
        cr;
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

private:
	NodeType        *top_;
}; // end class stack;

NS_END(elloop)

