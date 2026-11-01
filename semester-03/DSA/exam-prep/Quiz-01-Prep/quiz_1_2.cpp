#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
}; // singly / circular
struct DNode
{
    int data;
    DNode *prev, *next;
}; // doubly

void pushFront(Node *head, int v)
{
    Node *n = new Node{v, head};
    head = n;
    // since, we are updating a local variable it has no effect on the global one
}
void pushFrontFixed(Node *&head, int v)
{
    Node *n = new Node{v, head};
    head = n;
}
void freeList(Node *head)
{
    for (Node *p = head; p != nullptr; p = p->next)
        delete p;
    // in each iterarion first we are freeing the memory then accessing a memeber of it resulting in UB
}
void freeListFixed(Node *head)
{
    Node *travsersing = head;
    Node *next = nullptr;
    while (travsersing != nullptr)
    {
        next = travsersing->next;
        delete travsersing;
        travsersing = next;
    }
}
Node *reverse_list(Node *head)
{
    Node *prev = nullptr;
    Node *next = nullptr;
    while (head)
    {
        next = head->next; // Save the next node
        // Update the links
        head->next = prev;
        // Move the nodes
        prev = head;
        head = next;
    }
    return prev;
}

bool has_cycle(Node *head)
{
    Node *slow = head;
    Node *fast = head;
    while (fast != nullptr and fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
    return false;
}
Node *cycleStarts(Node *head)
{
    Node *slow = head;
    Node *fast = head;
    // Phase:01
    while (fast != nullptr and fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            // Phase 02: Only runs if a cycle is guaranteed to exist!
            slow = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // Loop exited because slow == fast at the cycle start
        }
    }
    return nullptr;
}

int main()
{
    Node *head = new Node{1, nullptr};
    head->next = new Node{2, nullptr};
    head->next->next = new Node{3, nullptr};
    cout << "--- Q1 --- \n\n";
    // a)
    cout << "a) \n";
    Node *p = head;
    Node *q = head->next;
    p->next = q->next;
    q->next = p;
    head = q;
    // result is a circular list in order of II -> III -> I

    // b)
    cout << " b) \n";
    cout << head->next->next->next->data;
    // UB

    // c)
    cout << " c) \n";

    return 0;
}
