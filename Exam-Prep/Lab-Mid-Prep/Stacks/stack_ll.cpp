#include <iostream>
#include <string>
#include <stack>
using namespace std;
struct Node
{
    Node *next = nullptr;
    int data{};

    Node(int value)
    {
        data = value;
    }
};
class Stack_LL
{
private:
    int size = 0;
    Node *top = nullptr;

public:
    // Constructor/Destructor
    ~Stack_LL()
    {
        while (top != nullptr)
        {
            Node *next = top->next;
            delete top;
            top = next;
        }
    }
    // Common operations
    void push(int value)
    {
        // Case: Empty
        if (top == nullptr)
            top = new Node(value);
        else // Case: Nodes already exist
        {
            Node *temp = new Node(value);
            temp->next = top;
            top = temp;
        }
        size++;
        return;
    }

    int pop()
    {
        // Case: Empty
        if (top == nullptr)
        {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        //
        Node *next_top = top->next;
        int value = top->data;
        delete top;
        top = next_top;
        size--;
        return value;
    }

    int peek()
    {
        // Case: Empty
        if (top == nullptr)
        {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        std::cout << "Peek: " << top->data << endl;
        return top->data;
    }

    bool is_empty()
    {
        return top == nullptr;
    }

    int _size()
    {
        std::cout << "Size: " << size << endl;
        return this->size;
    }
    // Random questions
    void display_stack()
    {
        Node *curr = top;
        int count = 0;
        while (curr != nullptr)
        {
            std::cout << ++count << "  " << curr->data << std::endl;
            curr = curr->next;
        }
    }
};


int main()
{
    Stack_LL stack;
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