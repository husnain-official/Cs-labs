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
    size_t size = 0;
    Node *head = nullptr;
    Node *tail = nullptr; // not to be used.

public:
    void add_before(const int &add_before, const int &value)
    {
        // 1. If list is empty
        if (head == nullptr)
            return;

        // 2. If value is at head
        if (head->value == add_before)
        {
            push_front(value);
            return;
        }

        // 3. If value is somewhere in between the list
        Node *traversing_ptr = head;
        while (traversing_ptr != nullptr)
        {
            if (traversing_ptr->value == add_before)
                break;
            traversing_ptr = traversing_ptr->next;
        }
        // Check, if we reached the end of the list without finding the add_before value.
        if (traversing_ptr == nullptr)
            return;

        // Update all pointers.
        Node *one_before = traversing_ptr->prev;
        Node *temp = new Node;
        temp->value = value;

        // Update pointers fro the new node to be added in between
        temp->prev = one_before;
        temp->next = traversing_ptr;

        // Update pointer for the node befor the new addition
        one_before->next = temp;

        // Update pointer for the node after the new addition
        traversing_ptr->prev = temp;

        size++;
    }

    void add_after(const int &add_after, const int &value)
    {
        // 1. If list is empty
        if (head == nullptr)
            return;

        // 2. If value is at head or inbetween the list
        Node *traversing_ptr = head;
        while (traversing_ptr != nullptr)
        {
            if (traversing_ptr->value == add_after)
                break;
            traversing_ptr = traversing_ptr->next;
        }
        // If we reached the end without finding add_after value
        if (traversing_ptr == nullptr)
            return;

        // Update all pointers
        Node *one_next = traversing_ptr->next;
        Node *temp = new Node;
        temp->value = value;
        // Update pointer of new node to be added
        temp->prev = traversing_ptr;
        temp->next = one_next;

        // Update the node ahead of the new addition, IF it exists
        if (one_next != nullptr)
            one_next->prev = temp;
        // Update the node behind of the new addition
        traversing_ptr->next = temp;
        size++;
    }

    void push_front(const int &value)
    {
        Node *temp = new Node;
        temp->value = value;
        temp->next = head;

        if (head != nullptr)
            head->prev = temp;

        head = temp;
        size++;
    }

    void push_back(const int &value)
    {
        // If empty, just push_front
        if (head == nullptr)
        {
            push_front(value);
            return;
        }

        Node *traversing_ptr = head;
        while (traversing_ptr->next != nullptr)
        {
            traversing_ptr = traversing_ptr->next;
        }

        Node *temp = new Node;
        temp->value = value;
        temp->prev = traversing_ptr;
        traversing_ptr->next = temp;

        size++;
    }

    void pop_front()
    {
        if (head == nullptr)
            return;

        Node *head_ptr = head->next;
        delete head;
        head = head_ptr;

        if (head != nullptr)
            head->prev = nullptr;

        size--; // Safely reached every time now
    }

    void pop_back()
    {
        if (head == nullptr)
            return;

        // Special case: Only 1 element in the list
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            size--;
            return;
        }

        Node *traversing_ptr = head;
        while (traversing_ptr->next != nullptr)
        {
            traversing_ptr = traversing_ptr->next;
        }

        Node *new_last = traversing_ptr->prev;
        new_last->next = nullptr;
        delete traversing_ptr;

        size--;
    }

    void insert_at(size_t index, const int &value)
    {
        // 1. Check for invalid index
        if (index > size)
            return;

        // 2. If inserting at the very beginning
        if (index == 0)
        {
            push_front(value);
            return;
        }

        // 3. If inserting at the very end
        if (index == size)
        {
            push_back(value);
            return;
        }

        // 4. Inserting somewhere in the middle
        Node *traversing_ptr = head;

        // Traverse to the node before the insertion point (index - 1)
        for (size_t i = 0; i < index - 1; i++)
        {
            traversing_ptr = traversing_ptr->next;
        }

        Node *one_next = traversing_ptr->next;
        Node *temp = new Node;
        temp->value = value;

        // Update all pointers
        temp->prev = traversing_ptr;
        temp->next = one_next;

        traversing_ptr->next = temp;
        one_next->prev = temp;

        size++;
    }
};

int main()
{
    Doubly list;
    list.push_back(10);
    list.push_front(5);
    list.add_after(10, 15);
    return 0;
}