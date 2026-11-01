#include <iostream>
using namespace std;

struct Node
{
    Node *next = nullptr;
    int value{};
};

class Singly
{
    size_t size = 0;
    Node *head = nullptr;

public:
    void add_before(const int &before, const int &value)
    {
        if (head == nullptr)
            return;

        // 1. If value is at head
        if (head->value == before)
        {
            push_front(value);
            return;
        }

        // 2. If value is somewhere in between
        Node *traversing_ptr = head;
        while (traversing_ptr->next != nullptr)
        {
            if (traversing_ptr->next->value == before)
                break;
            traversing_ptr = traversing_ptr->next;
        }

        // If we reached the end and didn't find the value
        if (traversing_ptr->next == nullptr)
            return;

        Node *temp = new Node;
        temp->value = value;

        // Link up the new node
        temp->next = traversing_ptr->next;
        traversing_ptr->next = temp;

        size++;
    }

    void add_after(const int &after, const int &value)
    {
        if (head == nullptr)
            return;

        Node *traversing_ptr = head;
        while (traversing_ptr != nullptr)
        {
            if (traversing_ptr->value == after)
                break;
            traversing_ptr = traversing_ptr->next;
        }

        if (traversing_ptr == nullptr)
            return;

        Node *temp = new Node;
        temp->value = value;

        temp->next = traversing_ptr->next;
        traversing_ptr->next = temp;

        size++;
    }

    void push_front(const int &value)
    {
        Node *temp = new Node;
        temp->value = value;

        temp->next = head;
        head = temp;

        size++;
    }

    void push_back(const int &value)
    {
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

        size--;
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

        // Traverse until traversing_ptr is the 2nd to last node
        Node *traversing_ptr = head;
        while (traversing_ptr->next->next != nullptr)
        {
            traversing_ptr = traversing_ptr->next;
        }

        // Delete the last node and set the new last node's next to nullptr
        delete traversing_ptr->next;
        traversing_ptr->next = nullptr;

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

        Node *temp = new Node;
        temp->value = value;

        // Link the new node in
        temp->next = traversing_ptr->next;
        traversing_ptr->next = temp;

        size++;
    }
};

int main()
{
    Singly list;
    list.push_back(10);
    list.push_front(5);
    list.add_after(10, 15);
    list.add_before(10, 7);

    return 0;
}