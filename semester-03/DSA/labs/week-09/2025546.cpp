#include <iostream>
using namespace std;

// Define the Node struct, which will be used to generate the Doubly linked list, which we have to sort later on.
struct Node
{
    int value{};
    Node *next = nullptr;
    Node *prev = nullptr;
    // Parameterized constructor for convenience
    Node(int value, Node *prev = nullptr, Node *next = nullptr)
    {
        this->value = value;
        this->prev = prev;
        this->next = next;
    }
};

// Helper functions:
// Function to split the list in 2 separate lists.
Node *split(Node *head)
{
    if (head == nullptr or head->next == nullptr)
        return head;

    Node *slow = head;
    Node *fast = head;

    // Find the middle using fast/slow pointers
    while (fast != nullptr and fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 'slow' is now at the start of the right sublist.
    Node *right_list = slow;
    Node *left_tail = slow->prev; // The node right before the split

    // Break the connection between left and right lists
    left_tail->next = nullptr;
    right_list->prev = nullptr;

    // Return the head of the right sublist
    return right_list;
}

// Function to merge 2 sorted lists, in 1 bigger sorted list.
Node *merge(Node *first, Node *second)
{
    //  Base-Cases
    // If either list is empty, return the other list
    if (first == nullptr)
        return second;
    if (second == nullptr)
        return first;
    // we will pick the smaller value between both
    if (first->value < second->value)
    {
        // recursively merge the lists and add the sorted list to curr node.
        Node *merged = merge(first->next, second);
        first->next = merged;
        if (merged != nullptr)
            merged->prev = first;
        first->prev = nullptr;
        return first;
    }
    else
    {
        // recursively merge the lists and add the sorted list to curr node.
        Node *merged = merge(first, second->next);
        second->next = merged;
        if (merged != nullptr)
            merged->prev = second;
        second->prev = nullptr;
        return second;
    }
}

// The main sorting function / to be called in main
Node *merge_sort(Node *head)
{
    // Since, merge sort is recursive, first we define the base case.
    if (head == nullptr or head->next == nullptr)
        return head;

    //  The divide part of the algorithm:
    Node *second = split(head);

    // The Sorting part of the algorithm:
    head = merge_sort(head);
    second = merge_sort(second);

    // Finally merge the two sorted haves and return the final list
    return merge(head, second);
}

// Function to print a linked list
void print(Node *head)
{
    Node *curr = head;
    while (curr != nullptr)
    {
        cout << curr->value;
        if (curr->next != nullptr)
            cout << "  ->  ";
        curr = curr->next;
    }
    std::cout << std::endl
              << std::endl;
}

int main()
{
    // 1. Create a hard-coded doubly linked list: 10 -> 20 -> 8 -> 17 -> 5 -> 13 -> 4
    Node *head = new Node(10);
    Node *second = new Node(20);
    Node *third = new Node(8);
    Node *fourth = new Node(17);
    Node *fifth = new Node(5);
    Node *sixth = new Node(13);
    Node *seventh = new Node(4);

    // 2. Wire the pointers (both next and prev)
    head->next = second;
    second->prev = head;

    second->next = third;
    third->prev = second;

    third->next = fourth;
    fourth->prev = third;

    fourth->next = fifth;
    fifth->prev = fourth;

    fifth->next = sixth;
    sixth->prev = fifth;

    sixth->next = seventh;
    seventh->prev = sixth;

    std::cout << "Before Sorting: ";
    print(head);

    // 3. Test the sorting function
    Node *sorted = merge_sort(head);

    std::cout << "After Sorting: ";
    print(sorted);

    // 4. Free memory
    while (sorted != nullptr)
    {
        Node *temp = sorted;
        sorted = sorted->next;
        delete temp;
    }
    return 0;
}