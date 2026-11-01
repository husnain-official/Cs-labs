#include <iostream>
using namespace std;

class Queue_ar
{
private:
    int capacity = 0;
    int front = 0;
    int size = 0;
    int *queue = nullptr;

public:
    // Constructor/Destructors
    Queue_ar(int capacity) : capacity(capacity > 0 ? capacity : 1)
    {
        queue = new int[this->capacity];
    }
    ~Queue_ar()
    {
        delete[] queue;
    }
    // Basic Operations
    bool is_empty()
    {
        return size == 0;
    }
    bool is_full()
    {
        return size == capacity;
    }
    void enqueue(int data)
    {
        // Case: No Entries
        if (is_empty())
        {
            queue[front] = data;
            size++;
            return;
        }
        // Case: Full capacity
        if (is_full())
        {
            std::cout << "Overflow Condition" << endl;
            return;
        }
        // Case: Valid Addition
        int index = (size + front) % capacity;
        queue[index] = data;

        size++;
        return;
    }
    int dequeue()
    {
        // Case: Empty
        if (is_empty())
        {
            std::cout << "Underflow Condition" << endl;
            return -1;
        }
        // Only 1 entry
        int to_return = queue[front];
        queue[front] = -1;
        int new_index = front + 1;
        front = new_index >= capacity ? 0 : new_index;
        size--;
        return to_return;
    }
    void display_queue()
    {
        int _size = this->size;
        int index = front;
        std::cout << "\n\n";
        while (_size > 0)
        {
            std::cout << "[ " << queue[index] << " ]";
            int temp = --_size;
            if (temp > 0)
                std::cout << " -> ";
            int new_index = index + 1;
            index = new_index >= capacity ? 0 : new_index;
        }
    }
    int get_size()
    {
        return size;
    }
    int get_front()
    {
        if (is_empty())
        {
            std::cout << "Underflow Condition" << endl;
            return -1;
        }
        return queue[front];
    }
    // Problems to solve later
};

int main()
{
    Queue_ar q(3);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display_queue();

    cout << q.dequeue() << "\n";
    q.display_queue();

    q.enqueue(50);
    q.display_queue();

    cout << q.get_front() << endl;
    cout << q.get_size() << endl;
    return 0;
}