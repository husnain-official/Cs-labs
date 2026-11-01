#include <iostream>
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

class Queue_ll
{
private:
    int size = 0;
    Node *front = nullptr;
    Node *back = nullptr;

public:
    ~Queue_ll()
    {
        Node *current = front;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
    // Simple operations
    void enqueue(int value)
    {
        Node *temp = new Node(value);
        // Case: No node
        if (is_empty())
        {
            front = temp;
            back = temp;
            size++;
            return;
        }
        // Case: Nodes Exist Already
        back->next = temp;
        back = temp;
        size++;
        return;
    }
    int dequeue()
    {
        // Case: Empty
        if (is_empty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        int to_return = -1;
        // Case: Head Only, Only 1 node
        if (front == back)
        {
            to_return = front->data;
            delete front;
            front = nullptr;
            back = nullptr;
        }
        else
        {
            Node *to_delete = front;
            to_return = front->data;
            front = front->next;
            delete to_delete;
        }
        size--;
        return to_return;
    }
    bool is_empty()
    {
        return front == nullptr;
        // Same thing if, return size == 0;
    }
    int get_front()
    {
        if (is_empty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return front->data;
    }
    int get_size()
    {
        return size;
    }
    void display_queue()
    {
        Node *curr = front;
        std::cout << "\n\n";
        while (curr != nullptr)
        {
            cout << "[ " << curr->data << " ]";
            if (curr->next != nullptr)
                std::cout << " -> ";
            curr = curr->next;
        }
    }
    // Later Add all possible leet code problems that might be possible in lab mid.
};
int main()
{
    Queue_ll q;

    q.enqueue(10);
    q.enqueue(20);
    q.display_queue();

    cout << q.dequeue() << "\n";
    q.display_queue();

    q.enqueue(30);
    q.display_queue();

    cout << q.get_front() << endl;
    cout << q.get_size() << endl;
    return 0;
}