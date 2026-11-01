#include <iostream>
using namespace std;

class Stack_ar
{
private:
    int top = 0;
    int capacity = 0;
    int *stack = nullptr;

public:
    // Constuctor/Destructor
    Stack_ar(int cap) : capacity(cap > 0 ? cap : 1)
    {
        stack = new int[capacity];
    }
    ~Stack_ar()
    {
        delete[] stack;
    }
    // Basic Operations
    void push(int value)
    {
        if (top >= capacity)
        {
            cout << "Overflow Condition. " << endl;
            return;
        }
        stack[top++] = value;
    }
    void pop()
    {
        if (top <= 0)
        {
            cout << "Underflow Condition. " << endl;
            return;
        }
        top--;
        return;
    }
    int peek()
    {
        if (top <= 0)
        {
            cout << "Underflow Condition. " << endl;
            return -1;
        }
        int peek_index = top - 1;
        std::cout << "Peek: " << stack[peek_index] << endl;
        return stack[peek_index];
    }
    int _size()
    {
        std::cout << "Size: " << top << endl;
        return top;
    }
    bool is_empty()
    {
        return top == 0;
    }
    //
    void display_stack()
    {
        int count = 0;

        for (int i = top - 1; i >= 0; i--)
        {
            std::cout << ++count << " . " << stack[i] << endl;
        }
    }
};

int main()
{
    Stack_ar stack(3);
    // Testing
    stack.pop();
    stack.peek();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.peek();
    stack.display_stack();
    stack._size();
    stack.pop();
    stack.pop();
    stack.pop();
    stack._size();
    return 0;
}