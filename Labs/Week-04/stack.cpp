#include <iostream>

using namespace std;

class Stack
{
    size_t top = 0;
    size_t size = 0; // Represents the maximum capacity
    int *stack = nullptr;

public:
    // Constructor
    Stack(size_t max_size)
    {
        this->size = max_size;             // Set the capacity
        this->stack = new int[this->size]; // Allocate based on capacity
    }

    // Destructor
    ~Stack()
    {
        delete[] this->stack;
    }

    // Is-Full ?
    bool is_full()
    {
        return this->top >= this->size;
    }

    // Is-Empty ?
    bool is_empty()
    {
        return this->top == 0;
    }

    // Push
    void push(int value)
    {
        if (this->is_full())
        {
            cout << "Failed to push " << value << ": Stack Overflow!" << endl;
            return;
        }

        this->stack[top] = value;
        this->top++;
    }

    // Pop
    void pop()
    {
        if (this->is_empty())
        {
            cout << "Failed to pop: Stack Underflow!" << endl;
            return;
        }

        this->top--;
    }

    // Print all
    void print_all()
    {
        if (this->is_empty())
        {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "---- Printing all Stack ----" << std::endl;
        for (size_t i = this->top; i > 0; i--)
        {
            cout << "Position: " << i << "   |   Value: " << this->stack[i - 1] << std::endl;
        }
    }
};

int main()
{
    cout << "1. Creating a stack of size 3..." << endl;
    Stack myStack(3);

    cout << "\n2. Pushing elements into the stack..." << endl;
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    myStack.print_all();

    cout << "\n3. Attempting to push into a full stack (Overflow test)..." << endl;
    myStack.push(40);

    cout << "\n4. Popping one element..." << endl;
    myStack.pop();
    myStack.print_all();

    cout << "\n5. Popping remaining elements..." << endl;
    myStack.pop();
    myStack.pop();
    myStack.print_all();

    cout << "\n6. Attempting to pop from an empty stack (Underflow test)..." << endl;
    myStack.pop();

    return 0;
}