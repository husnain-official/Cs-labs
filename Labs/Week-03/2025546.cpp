/*
--- DSA LAB WEEK 2 ---
Name:      M.Husnain Afzal
Reg:       2025-546
Faculty:   CS-H2
*/
#include <iostream>
// Node-struct
struct Node
{
    Node *next = nullptr;
    int data;
};

// -------------------- LAB-ACTIVITIES --------------------------
// --- Task-01 ---
int countNodes(Node *head)
{
    int count = 0;
    Node *traversing_ptr = head;
    // Loop through each node, until the last one, and add to count in all.
    while (traversing_ptr != nullptr)
    {
        count++;
        traversing_ptr = traversing_ptr->next;
    }
    // Note: I am adding this cout as, it will be easy to show the ouput of function, in the docx submission file.
    std::cout << "[In function] Count: " << count << std::endl;
    return count;
}

// --- Task-02 ---
bool isListEmpty(Node *head)
{
    // Note: I am adding this cout as, it will be easy to show the ouput of function, in the docx submission file.
    std::cout << "[In function] List is: " << (head == nullptr ? "empty" : "NOT empty") << std::endl;
    return head == nullptr;
}

// --- Task-03 ---
void delete_value(Node *&head, int value)
{
    // Note: I am adding this cout as, it will be easy to show the ouput of function, in the docx submission file.
    std::cout << "Delete function called " << std::endl;

    // if Lineked list is empty
    if (head == nullptr)
        return;

    // if value is at head
    if (head->data == value)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // General case: delete middle or last node
    Node *last_node = nullptr;
    Node *traversing_node = head;

    while (traversing_node != nullptr)
    {
        if (traversing_node->data == value)
            break;

        last_node = traversing_node;
        traversing_node = traversing_node->next;
    }

    // Value not found
    if (traversing_node == nullptr)
        return;

    // Unlink and delete
    last_node->next = traversing_node->next;
    delete traversing_node;
}

int main()
{
    // Demo-Main.
    Node *head = new Node;
    Node *sec = new Node;
    Node *third = new Node;
    Node *forth = new Node;
    head->data = 2;
    sec->data = 1;
    third->data = 4;
    forth->data = 4;
    // Link them.
    head->next = sec;
    sec->next = third;
    third->next = forth;

    // Output showed in docx file for function/task-01
    std::cout << "--Task-01--" << std::endl;
    int _count = countNodes(head);
    std::cout << "[Main] Count: " << _count << std::endl
              << std::endl;

    // Output showed in docx file for function/task-02
    std::cout << "--Task-02--" << std::endl;
    int _result = isListEmpty(head);
    std::cout << "[Main] List is: " << (_result ? "Empty" : "NOT-empty") << std::endl
              << std::endl;

    // Output showed in docx file for function/task-03
    // Deletes first node with value 4 (2 -> 1 -> 4 -> 4)
    std::cout << "--Task-03--" << std::endl;
    delete_value(head, 4);
    _count = countNodes(head);
    std::cout << "After delete of node with value 4: " << _count << "\n";

    // Fee up the dynamic allocated memory.
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}