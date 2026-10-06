/*
Name:   Husnain-Afzal
Reg:    2025546
Sec:    CS(C2)
*/
#include <iostream>
#include <string>
using namespace std;

struct Node
{
    Node *next = nullptr;
    Node *prev = nullptr;
    std::string data;
};

class Queue
{
private:
    Node *front = nullptr;
    Node *rear = nullptr;
    int capacity{};
    int size{};

public:
    // Constructor/Destructor
    Queue(int capacity) : capacity(capacity)
    {
        std::cout << "--- Queue Created ---\n";
    }
    ~Queue()
    {
        Node *traversing_ptr = this->front;
        while (traversing_ptr)
        {
            Node *to_delete = traversing_ptr;
            traversing_ptr = traversing_ptr->next;
            delete to_delete;
            this->size--;
        }
        std::cout << "--- Queue Emptied ---\n";
    }
    // All 3 functions requried in task to do.
    bool enqueue(std::string data)
    {
        // First we check if there is size to add a new node or not ?
        if (size >= capacity)
        {
            std::cout << "ERROR: Can not enqueue while size is full\n";
            return false;
        }
        Node *entry = new Node;
        entry->data = data;
        // Check if this is the first entry
        if (this->front == nullptr)
        {
            this->front = entry;
            this->rear = entry;
            size++;
            return true;
        }
        // else add a new node in the list
        entry->prev = this->rear;

        // Update the pointer of the rear to this new entry
        this->rear->next = entry;
        this->rear = entry;

        // Update the size
        this->size++;
        // Finally return success
        return true;
    }

    bool dequeue()
    {
        // First check if a node exists in the list or not
        if (size <= 0)
        {
            std::cout << "ERROR: Can not dequeue on a empty queue\n";
            return false;
        }
        // Else first save the pointer to the next node, then delete the old head
        Node *new_front = this->front->next;
        delete this->front;

        // Update members
        this->front = new_front;
        if (this->front)
            this->front->prev = nullptr;
        else
            this->rear = nullptr; // Queue is empty
        this->size--;

        // Return success
        return true;
    }

    void display()
    {
        // Initial Check
        if (size <= 0)
            return;

        // Make a pointer that will traverse the list
        Node *traversing_ptr = this->front;
        int count = 0;
        while (traversing_ptr)
        {
            // Print data
            std::cout << "\n--- Node: " << ++count << std::endl;
            std::cout << "Data: " << traversing_ptr->data << std::endl;
            // Update the pointer
            traversing_ptr = traversing_ptr->next;
        }
        return;
    }

    int length_of_string()
    {
        Node *traversing_ptr = this->front;
        int count = 0;
        int char_count = 0;
        // Traverse the front
        while (traversing_ptr)
        {
            // Print data
            std::cout << "\nNode: " << ++count << std::endl;
            std::cout << "Data: " << traversing_ptr->data << std::endl;
            std::cout << "No-of-characters: " << traversing_ptr->data.size() << std::endl;
            // Update count and move pointer forward
            char_count += traversing_ptr->data.size();
            traversing_ptr = traversing_ptr->next;
            // delete the current front
            this->dequeue();
        }
        std::cout << "\n --- The total characters in " << count << " Nodes are " << char_count << std::endl;
        return char_count;
    }
};

int main()
{
    // NOTE: The DEMO main is AI generated.
    Queue q(3);

    q.enqueue("Hello");
    q.enqueue("Data");
    q.enqueue("Structures");
    q.enqueue("Overflow"); // fails: capacity is 3

    q.display();
    q.dequeue(); // removes "Hello"
    q.display();

    int total = q.length_of_string();              // prints each node, dequeues all
    cout << "Total characters: " << total << endl; // 4 + 10 = 14

    q.display(); // (queue is empty)
    q.dequeue(); // error message
    return 0;
}
