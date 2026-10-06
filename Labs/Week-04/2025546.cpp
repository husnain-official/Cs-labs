/*
--- DSA LAB WEEK 3 ---
Name:      M.Husnain Afzal
Reg:       2025-546
Faculty:   CS-H2
*/
#include <iostream>
#include <string>
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
    // Constructor/Destructor
    Doubly() = default;
    ~Doubly()
    {
        while (head != nullptr)
            pop_front();
    }
    // Raw owning pointers: copying would make two lists delete the same nodes.
    Doubly(const Doubly &) = delete;
    Doubly &operator=(const Doubly &) = delete;

    // --------------------------------------------------------------------------------------------------------
    // TASK:1 (i) Add/Delete at front/back.
    void push_front(const int &value)
    {
        Node *temp = new Node;
        temp->value = value;
        temp->next = head;
        // Update the pointer of the old head.
        if (head != nullptr)
            head->prev = temp;
        // If list is empty, assign temp to head.
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
        // Else move to the last node
        Node *traversing_ptr = head;
        while (traversing_ptr->next != nullptr)
        {
            traversing_ptr = traversing_ptr->next;
        }

        Node *temp = new Node;
        // Update poiters of both node-updated. Last and old-Last.
        temp->value = value;
        temp->prev = traversing_ptr;
        traversing_ptr->next = temp;

        size++;
    }

    void pop_front()
    {
        if (head == nullptr)
            return;
        // Save ptr to the 2nd node, so later it can become the head
        Node *head_ptr = head->next;
        delete head;
        head = head_ptr;
        // If valid node, then update the inner pointers
        if (head != nullptr)
            head->prev = nullptr;

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
        // Else travel to the last node
        Node *traversing_ptr = head;
        while (traversing_ptr->next != nullptr)
        {
            traversing_ptr = traversing_ptr->next;
        }
        // Save the pointer to last node, so its 'next' ptr can be updated.
        Node *new_last = traversing_ptr->prev;
        new_last->next = nullptr;
        delete traversing_ptr;

        size--;
    }

    // TASK:1 (ii) Print all nodes.
    void print_all()
    {
        if (head == nullptr)
            return;

        Node *traversing_ptr = head;
        int count = 0;
        std::cout << "\n\n---------------------------------\n";
        std::cout << "--- ALL NODES PRINTED ---\n\n";
        while (traversing_ptr != nullptr)
        {
            cout << "[Node: " << ++count << " ]\n";
            cout << "Value: " << traversing_ptr->value << std::endl;
            cout << "Node's Address: " << traversing_ptr << std::endl;
            cout << "Prev Node: " << traversing_ptr->prev << std::endl;
            cout << "Next Node: " << traversing_ptr->next << std::endl
                 << std::endl;

            // Move the pointer to the next node
            traversing_ptr = traversing_ptr->next;
        }
        return;
    }
    void print_values()
    {
        if (head == nullptr)
            return;

        Node *traversing_ptr = head;
        int count = 0;
        std::cout << "\n\n---------------------------------\n";
        std::cout << "--- ALL NODES PRINTED [values only] ---\n\n";
        while (traversing_ptr != nullptr)
        {
            cout << "\n[Node: " << ++count << " ]\n";
            cout << "Value: " << traversing_ptr->value << std::endl;
            // Move the pointer to the next node
            traversing_ptr = traversing_ptr->next;
        }
        return;
    }

    // TASK:1 (iii) Delete node with value 'value'
    bool delete_node(const int &value, Node *start_from = nullptr)
    {
        /*
        The argument 'strat_from' is added as this function can be reused in TASK3, as we can start from any node,
        and delete the first occurance, of the value node, from that startnig node, not from the actual head.
        HOW THIS WILL WORK ?
        So, if start_from is not nullptr the traversing ptr will start from this rather than from head.
        WHY ? THis will follow the reusibility of code and dont repeat yourself rules, and are good practices, maybe.
        */
        // 1. If list is empty
        if (head == nullptr)
            return false;

        // 2. If value is somewhere in between the list
        Node *traversing_ptr = (start_from != nullptr) ? start_from : head;

        while (traversing_ptr != nullptr)
        {
            if (traversing_ptr->value == value)
                break;
            traversing_ptr = traversing_ptr->next;
        }
        // 3. If we reached the end without finding the value node
        if (traversing_ptr == nullptr)
            return false;

        // 4. Found the node to delete, unlink it.
        unlink(traversing_ptr);
        return true;
    }

    // --------------------------------------------------------------------------------------------------------
    // TASK:2 Check palindromes using the prev pointer in doubly
    bool is_palindrome()
    {
        /*
      Concept:
      Set 1 pointer to head, 1 pointer to tail.
      Now check if both values mathch, if they do, move the head pointer to next, and tail pointer to prev.
      If at any point they do not match, return false.
      Now: How do we determine the mid way point ?
      In each iteration:
      CHECK:1, If head-> next == tail->prev, This means the list was of odd nodes and we have reached the mid node, return true.
      CHECK:2, If head-> next == tail OR tail-> prev == head, this means the list is of even nodes, and return true.
      */
        // CHECK:0
        if (head == nullptr)
            return true;

        Node *front = head;
        Node *back = head;

        // First we get the correct value/last node's address in 'back' ptr;
        while (back->next != nullptr)
            back = back->next;

        // Now the iteration step
        while (front != back && back->next != front)
        {
            // Value check
            if (front->value != back->value)
                return false;

            // Move the pointers
            front = front->next;
            back = back->prev;
        }
        return true;
    }

    // --------------------------------------------------------------------------------------------------------
    // TASK:3 Delete all occurances in the list
    void remove_duplicates()
    {
        if (head == nullptr)
            return;
        // The outer loop/ The nodes movement, from 1st to 2nd etc
        for (Node *current = head; current != nullptr; current = current->next)
        {
            Node *running = current->next;
            // The inner loop/ Check for all duplicates and unlinks/deletes them.
            while (running != nullptr)
            {
                Node *next = running->next; // save before a possible delete
                if (running->value == current->value)
                    unlink(running);
                running = next;
            }
        }
    }

private:
    void unlink(Node *node)
    {
        /*
        Updates all pointers and delete the 'node' sent through the argument.
        */
        if (node->prev != nullptr)
            node->prev->next = node->next;
        else
            head = node->next; // node was the head
        if (node->next != nullptr)
            node->next->prev = node->prev;
        delete node;
        size--;
    }
};
int main()
{
    // NOTE: Demo in main function is AI generated.
    //  EXERCISE 1: add / delete / display
    cout << "\n---- EXERCISE 1 ----\n";
    Doubly list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    cout << "After push_back 10, 20, 30, 40:\n";
    list.print_values();

    list.delete_node(20);
    cout << "\nAfter delete_node(20):\n";
    list.print_values();

    cout << "\nprint_all():";
    list.print_all();

    //  EXERCISE 2: palindrome check
    cout << "\n---- EXERCISE 2 ----\n";

    Doubly p1; // 1 2 3 4 5
    for (int v : {1, 2, 3, 4, 5})
        p1.push_back(v);
    cout << "Original List:\n";
    p1.print_values();
    cout << (p1.is_palindrome() ? "Linked list is a palindrome.\n" : "Linked list is not a palindrome.\n");

    Doubly p2; // 1 2 2 1
    for (int v : {1, 2, 2, 1})
        p2.push_back(v);
    cout << "\nOriginal List:\n";
    p2.print_values();
    cout << (p2.is_palindrome() ? "Linked list is a palindrome.\n" : "Linked list is not a palindrome.\n");

    //  EXERCISE 3: remove duplicates
    cout << "\n---- EXERCISE 3 ----\n";

    Doubly d1; // 1 2 3 3 4
    for (int v : {1, 2, 3, 3, 4})
        d1.push_back(v);
    cout << "Original List:\n";
    d1.print_values();
    d1.remove_duplicates();
    cout << "After removing duplicate elements from the said doubly list:\n";
    d1.print_values();

    return 0;
}