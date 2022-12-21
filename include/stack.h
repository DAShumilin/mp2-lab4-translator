#include <vector>

template <typename T>

class Stack {

    std::vector<T> data;
    size_t sz;

public:
    Stack() {
        sz = 0;
    }

    size_t size() {
        return sz;
    }

    bool empty() {
        return sz == 0;
    }

    void push(const T& x) {
        data.push_back(x);
        sz++;
    }

    T top() {
        if (empty()) {
            throw "Error";
        }
        return data[sz - 1];
    }

    void pop() {
        if (empty()) {
            throw "Error";
        }
        data.pop_back();
        sz--;
    }
};