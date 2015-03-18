_Pragma("once")
class Simple {
  public:
    Simple() : i_(10) {
    }
    void setI(int i) {
      i_ = i;
    }
    int getI() const;
  private:
    int i_;
};
