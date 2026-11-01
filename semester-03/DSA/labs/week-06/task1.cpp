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
    std::string name;
    int pages{};
};

class Printer
{
private:
    Node *front = nullptr;
    Node *rear = nullptr;
    int capacity = 5;
    int size{};

public:
    // Constructor/Destructor
    Printer()
    {
        std::cout << "--- Queue Created ---\n";
    }
    ~Printer()
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
    bool enqueue(std::string name, int pages)
    {
        // First we check if there is size to add a new node or not ?
        if (size >= capacity)
        {
            std::cout << "ERROR: Can not enqueue while size is full\n";
            return false;
        }
        Node *entry = new Node;
        entry->name = name;
        entry->pages = pages;
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

    void peek()
    {
        if (size <= 0)
            return;
        // Print data
        std::cout << "\n--- Node in front --- " << std::endl;
        std::cout << "Name: " << front->name << std::endl;
        std::cout << "Pages: " << front->pages << std::endl;
        return;
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
            std::cout << "Name: " << traversing_ptr->name << std::endl;
            std::cout << "Pages: " << traversing_ptr->pages << std::endl;
            // Update the pointer
            traversing_ptr = traversing_ptr->next;
        }
        return;
    }

    void being_processed()
    {
        peek();
    }
};

void show_menu()
{
    std::cout << "\n\n===== UNIVERSITY PRINT QUEUE =====" << std::endl;
    std::cout << "1. Add Print Request: " << std::endl;
    std::cout << "2. Process/Print Request: " << std::endl;
    std::cout << "3. View Next Request: " << std::endl;
    std::cout << "4. Display Waiting Request: " << std::endl;
    std::cout << "5. Quit" << std::endl;
}
int main()
{
    Printer p;
    int option{};
    std::string name;
    int pages{};
    while (true)
    {
        show_menu();
        // Get Option and Validate it
        std::cin >> option;
        name.clear();
        pages = 0;
        if (option > 5 and option < 1)
            continue;
        switch (option)
        {
        case (1):
        {
            std::cout << "Adding Print Requested: " << std::endl;
            std::cout << "Add Name: " << std::endl;
            std::getline(std::cin >> std::ws, name);
            std::cout << "Add Pages: " << std::endl;
            std::cin >> pages;
            p.enqueue(name, pages);
            break;
        }
        case (2):
        {
            std::cout << "Processing Print Requested: " << std::endl;
            p.dequeue();
            break;
        }
        case (3):
        {
            std::cout << "Next Print Request: " << std::endl;
            p.peek();
            break;
        }
        case (4):
        {
            p.display();
            break;
        }
        case (5):
        {
            return 0;
        }
        }
    }
}
