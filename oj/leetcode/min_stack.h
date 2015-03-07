_Pragma("once")

#include <set>
#include <vector>
namespace min_stack {


class MinStack {
  struct Node {
    int data;
    Node* next;
    Node(int x=0, Node* p=nullptr) : data(x), next(p) {}
  };

  int min_ {0};
  Node* top_ {nullptr};

  int calculateMin() {
    if (top_ == nullptr) {
      return 0;
    }

    int m(top_->data);
    auto p(top_->next);
    while (p != nullptr) {
      if (p->data < m) {
        m = p->data;
      }
      p = p->next;
    }

    return m;
  }

  void clear() {
    auto p(top_);
    auto q(top_);
    while (p != nullptr) {
      q = p->next;
      // LOGD("deleting %d\n", p->data);
      delete p;
      p = q;
    }
  }
  public:
    void push(int x) {
      if (nullptr == top_ || min_ > x) {
        min_ = x;
      }
      if (nullptr == top_ ) {
        top_ = new Node(x, nullptr);
      }
      else {
        auto temp = new Node(x, top_);
        top_ = temp;
      }
    }

    void pop() {
      if (top_ != nullptr) {
        // delete top.
        // if min is delete, recalculate min.
        int data = top_->data;
        auto temp = top_;
        top_ = top_->next;
        delete temp;

        if (nullptr == top_)  {
          min_ = 0;
        }
        else if (min_ == data){
          min_ = calculateMin();
        }
      }
    }

    int top() {
      if (top_ != nullptr) {
        return top_->data;
      }
      else {
        throw 1;
      }
    }

    int getMin() {
      return min_;
    }

    ~MinStack() {
      clear();
    }
};

class MinStack2 {
  int min_ {0};
  int top_ {-1};
  int *elems_ {nullptr};
  int capacity_ {0};

  int calculateMin() {
    if (top_ == 0) {
      return elems_[0];
    }

    int m(elems_[0]);
    for (int i=0; i<=top_; ++i) {
      if (m < elems_[i]) {
        m = elems_[i];
      }
    }
    return m;
  }

  void clear() {
    delete [] elems_;
  }

  public:
    void push(int x) {
      if (-1 == top_) {
        capacity_ = 10;
        elems_ = new int[capacity_];
      }
      else if (top_ == capacity_) {
        if (capacity_ < 10000) {
          capacity_ *= 2;
        }
        else {
          capacity_ += 10;
        }
       
      }
      if (min_ < x){
        min_ = x;
      }
      elems_[++top_] = x;
    }

    void pop() {
      if (top_ != nullptr) {
        // delete top.
        // if min is delete, recalculate min.
        int data = top_->data;
        auto temp = top_;
        top_ = top_->next;
        delete temp;

        if (nullptr == top_)  {
          min_ = 0;
        }
        else if (min_ == data){
          min_ = calculateMin();
        }
      }
    }

    int top() {
      if (top_ != nullptr) {
        return top_->data;
      }
      else {
        throw 1;
      }
    }

    int getMin() {
      return min_;
    }

    ~MinStack() {
      clear();
    }
};
}
