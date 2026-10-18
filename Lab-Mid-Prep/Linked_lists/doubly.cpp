#include <iostream>
using namespace std;
struct Node
{
    Node *next = nullptr;
    Node *prev = nullptr;
    int value{};
};

class Doubly
{
private:
    int size = 0;
    Node *head = nullptr;

public:
    // Destructor
    ~Doubly()
    {
        while (head != nullptr)
        {
            Node *next = head->next;
            delete head;
            head = next;
        }
    }
    // Push operations
    void pushback(int value)
    {
        Node *temp = new Node();
        temp->value = value;
        // Case: No Node
        if (head == nullptr)
        {
            head = temp;
            size++;
            return;
        }
        // Else at the end
        Node *curr = head;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = temp;
        temp->prev = curr;
        size++;
        return;
    }
    void pushfront(int value)
    {
        Node *temp = new Node();
        temp->value = value;
        // Case: No Node
        if (head == nullptr)
        {
            head = temp;
            size++;
            return;
        }
        // Case: Other nodes exist or just head exists
        head->prev = temp;
        temp->next = head;
        head = temp;
        size++;
        return;
    }
    void pushbefore(int value, int before)
    {
        // Case:01 Empty
        if (head == nullptr)
            return;

        Node *curr = head;
        while (curr != nullptr and curr->value != before)
            curr = curr->next;

        // Case: "Before" doesnt exist
        if (curr == nullptr)
            return;

        Node *temp = new Node();
        temp->value = value;
        temp->next = curr;

        // Case: "Before" at head
        if (curr == head)
        {
            head->prev = temp;
            head = temp;
        }
        else // Case: "Before" somewhere in between
        {
            temp->prev = curr->prev;
            curr->prev->next = temp;
            curr->prev = temp;
        }
        size++;
        return;
    }
    // Pop operations
    void popback()
    {
        // Case: No node
        if (head == nullptr)
            return;
        // Case: End of list
        Node *curr = head;
        while (curr->next != nullptr)
            curr = curr->next;
        if (curr == head) // Case: Head Only
        {
            delete head;
            head = nullptr;
            size--;
        }
        else
        {
            Node *new_last = curr->prev;
            delete curr;
            new_last->next = nullptr;
            size--;
        }
        return;
    }
    void popfront()
    {
        // Case: No node
        if (head == nullptr)
            return;

        // Every other case
        Node *to_delete = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        size--;
        delete to_delete;
        return;
    }
    void pop_value(int value)
    {
        if (head == nullptr)
            return;

        Node *curr = head;
        while (curr != nullptr and curr->value != value)
            curr = curr->next;

        if (curr == nullptr)
            return;

        if (curr == head)
        {
            head = curr->next;
            if (head != nullptr)
                head->prev = nullptr;
        }
        else
        {
            curr->prev->next = curr->next;
            if (curr->next != nullptr)
                curr->next->prev = curr->prev;
        }
        size--;
        delete curr;
    }
    // Display function
    void display()
    {
        Node *traversing_ptr = head;
        int count = 0;
        std::cout << endl
                  << endl;
        while (traversing_ptr != nullptr)
        {
            std::cout << "   [Node: " << ++count << " | Value: " << traversing_ptr->value << " ]";
            if (traversing_ptr->next != nullptr)
                std::cout << " -> ";
            traversing_ptr = traversing_ptr->next;
        }
    }
};
int main()
{
    Doubly list;
    list.pushfront(10);
    list.pushfront(5);
    list.pushback(20);
    list.pushfront(3);
    list.pushbefore(1, 5);
    list.pop_value(1);
    list.pop_value(1000);
    list.pushbefore(100, 200);
    list.display();
    list.popback();
    list.popfront();
    list.pushback(120);
    list.pop_value(10);
    list.display();

    return 0;
}