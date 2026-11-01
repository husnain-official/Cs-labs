#include <iostream>
#include <stdexcept>

struct Node
{
    int data{};
    Node *next = nullptr;
    Node *prev = nullptr;
};

class Queue_ll
{
private:
    size_t count{};
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    Queue_ll() = default;
    // Non-copyable (or implement deep copy if you need it)
    Queue_ll(const Queue_ll &) = delete;
    Queue_ll &operator=(const Queue_ll &) = delete;
    ~Queue_ll()
    {
        while (!empty())
            dequeue();
    }
    // ---
    void enqueue(int value)
    {
        Node *temp = new Node{value, nullptr, nullptr};
        if (tail == nullptr) // empty queue
        {
            head = tail = temp;
        }
        else
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
        ++count;
    }

    void dequeue()
    {
        if (head == nullptr)
            return;

        Node *old = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr; // queue became empty

        delete old;
        --count;
    }

    int front() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return head->data;
    }

    bool empty() const { return count == 0; }
    size_t size() const { return count; }
};

class Queue_arr
{
private:
    size_t capacity;
    size_t count{};
    size_t head_index{};
    size_t tail_index{};
    int *arr = nullptr;

public:
    explicit Queue_arr(size_t max_capacity) : capacity(max_capacity), arr(new int[max_capacity])
    {
        if (max_capacity == 0)
            throw std::invalid_argument("Capacity must be greater than 0");
    }
    Queue_arr(const Queue_arr &) = delete;
    Queue_arr &operator=(const Queue_arr &) = delete;
    ~Queue_arr()
    {
        delete[] arr;
    }

    // ---
    void enqueue(int value)
    {
        if (count == capacity)
            throw std::overflow_error("Queue is full");

        arr[tail_index] = value;
        tail_index = (tail_index + 1) % capacity; // Wrap around if needed
        ++count;
    }

    void dequeue()
    {
        if (empty())
            return;

        head_index = (head_index + 1) % capacity; // Wrap around if needed
        --count;
    }

    int front() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return arr[head_index];
    }

    bool empty() const { return count == 0; }

    bool full() const { return count == capacity; }

    size_t size() const { return count; }

    size_t max_size() const { return capacity; }
};

int main()
{
    // --- queue implementation using linked lists.
    Queue_ll q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    while (!q.empty())
    {
        std::cout << q.front() << ' '; // prints 1 2 3
        q.dequeue();
    }
    std::cout << '\n';

    // --- queue implementation using linked arrays.
}