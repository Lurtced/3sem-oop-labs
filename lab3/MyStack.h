#include <iostream>

class StackOverflow {};
class StackUnderflow {};
class StackOutOfRange {
private:
	size_t index;
public:
	StackOutOfRange(size_t idx) : index(idx) {}
	void Out() const {
		std::cout << "\nStack out of range: " << index;
	}
};

template <typename T, size_t size> 
class MyStack {
private:
	size_t capacity_ = size;  // Maximum capacity of the stack
	size_t size_ = 0;      // Current size of the stack
	T* data_ = new T[capacity_];;          // Array to hold stack elements

public:
	// Destructor
	~MyStack() {
		delete[] data_;
	}
	// Push an element onto the stack
	void Push(const T& value) {
		if (size_ >= capacity_) {
			throw StackOverflow();
		}
		data_[size_++] = value;
	}
	// Pop an element from the stack
	T Pop();
	// Get current size of the stack
	size_t GetSize() const {
		return size_;
	}
	// Get maximum capacity of the stack
	size_t Capacity() const {
		return capacity_;
	}
	// Access element by index
	T& operator[](size_t index) {
		if (index >= size_) {
			throw StackOutOfRange(index);
		}
		return data_[index];
	}
};

// just for practice here, not in class
template <typename T, size_t size> T MyStack<T, size>::Pop() {
	if (size_ == 0) {
		throw StackUnderflow();
	}
	return data_[--size_];
}