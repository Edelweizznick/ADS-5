// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int kSize>
class TStack {
 private:
  T arr[kSize];
  int top_idx;

 public:
  TStack() : top_idx(-1) {}

  void Push(const T& value) {
    if (top_idx < kSize - 1) {
      arr[++top_idx] = value;
    }
  }

  T Pop() {
    if (top_idx >= 0) {
      return arr[top_idx--];
    }
    return T{};
  }

  T Top() const {
    if (top_idx >= 0) {
      return arr[top_idx];
    }
    return T{};
  }

  bool IsEmpty() const {
    return top_idx == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
