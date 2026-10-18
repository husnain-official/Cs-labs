#include <iostream>
using namespace std;

struct Node
{
    Node *next = nullptr;
    int data{};
};

class Singly
{
private:
    Node *head = nullptr;
    int size = 0;

public:
    // Push functions
    void push(int data)
    {
        Node *temp = new Node();
        temp->data = data;

        // Incase of head:
        if (head == nullptr)
        {
            head = temp;
            size++;
            return;
        }
        // In any other case
        Node *traversing_ptr = head;
        while (traversing_ptr->next != nullptr)
        {
            traversing_ptr = traversing_ptr->next;
        }
        traversing_ptr->next = temp;
        size++;
        return;
    }
    bool push_after(int data, int after)
    {
        Node *temp = new Node();
        temp->data = data;

        // Incase of head or 1st node in list
        if (head == nullptr)
        {
            return false;
        }

        Node *traversing_ptr = head;
        while (traversing_ptr != nullptr)
        {
            if (traversing_ptr->data == after)
                break;
            traversing_ptr = traversing_ptr->next;
        }
        if (traversing_ptr == nullptr)
            return false;

        temp->next = traversing_ptr->next;
        traversing_ptr->next = temp;
        size++;
        return true;
    }
    bool push_before(int data, int before)
    {
        Node *temp = new Node();
        temp->data = data;

        // Incase of head
        if (head == nullptr)
            return false;

        // Else
        Node *traversing_ptr = head;
        Node *prev = nullptr;
        while (traversing_ptr != nullptr)
        {
            if (traversing_ptr->data == before)
                break;
            prev = traversing_ptr;
            traversing_ptr = traversing_ptr->next;
        }
        // Incase the head is the node to push before
        if (prev == nullptr)
        {
            temp->next = head;
            head = temp;
            size++;
            return true;
        }
        else
        {
            temp->next = prev->next;
            prev->next = temp;
            size++;
            return true;
        }
        return false;
    }

    // Pop functions
    void pop()
    {
        if (head == nullptr)
            return;

        Node *traversing_ptr = head;
        Node *prev = nullptr;
        while (traversing_ptr->next != nullptr)
        {
            prev = traversing_ptr;
            traversing_ptr = traversing_ptr->next;
        }
        if (prev == nullptr)
        {
            delete head;
            head = nullptr;
            size--;
            return;
        }
        else
        {
            delete prev->next;
            prev->next = nullptr;
            size--;
            return;
        }
    }
    bool pop_value(int value)
    {
        if (head == nullptr)
            return false;

        Node *traversing_ptr = head;
        Node *prev = nullptr;
        while (traversing_ptr != nullptr and traversing_ptr->data != value)
        {
            prev = traversing_ptr;
            traversing_ptr = traversing_ptr->next;
        }
        if (traversing_ptr == nullptr)
            return false;

        if (prev == nullptr)
        {
            head = head->next;
        }
        else
        {
            prev->next = traversing_ptr->next;
        }
        delete traversing_ptr;
        size--;
        return true;
    }

    // Display functions
    void display_all()
    {
        Node *traversing_ptr = head;
        int count = 0;
        std::cout << endl
                  << endl;
        while (traversing_ptr != nullptr)
        {
            std::cout << "   [Node: " << ++count << " | Value: " << traversing_ptr->data << " ]";
            if (traversing_ptr->next != nullptr)
                std::cout << " -> ";
            traversing_ptr = traversing_ptr->next;
        }
    }
};

int main()
{
    Singly list = Singly();
    list.push(10);
    list.push(20);
    list.push_after(15, 10);
    list.push_before(5, 10);
    list.display_all();
    list.pop();
    list.pop_value(5);
    list.pop_value(2);
    list.pop_value(3);
    list.display_all();
    return 0;
}