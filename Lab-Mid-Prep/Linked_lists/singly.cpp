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
    // Destructor
    ~Singly()
    {
        while (head != nullptr)
        {
            Node *next = head->next;
            delete head;
            head = next;
        }
    }
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

        Node *temp = new Node();
        temp->data = data;
        temp->next = traversing_ptr->next;

        traversing_ptr->next = temp;
        size++;
        return true;
    }
    bool push_before(int data, int before)
    {
        // Incase of head
        if (head == nullptr)
            return false;

        // Else
        Node *traversing_ptr = head;
        Node *prev = nullptr;
        while (traversing_ptr != nullptr and traversing_ptr->data != before)
        {
            prev = traversing_ptr;
            traversing_ptr = traversing_ptr->next;
        }
        if (traversing_ptr == nullptr)
            return false;

        Node *temp = new Node();
        temp->data = data;
        temp->next = traversing_ptr;

        // Incase the head is the node to push before
        if (prev == nullptr)
        {
            head = temp;
        }
        else
        {
            prev->next = temp;
        }
        size++;
        return true;
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
    // Simple LeetCodde Problems
    // 1. Reverse a Singly Linked List, Only given the head.
    void reverse()
    {
        Node *prev = nullptr;
        Node *curr = head;
        Node *next = nullptr;
        if (head != nullptr)
            next = head->next;
        // Now Traverse the list
        while (curr != nullptr)
        {
            curr->next = prev;
            prev = curr;
            curr = next;
            if (curr != nullptr)
                next = next->next;
        }
        head = prev;
        return;
    }
    // 2. Remove nth Node from the End, Only given the head.
    bool remove_nth_from_end(int n)
    {
        if (n <= 0 or head == nullptr)
            return false;

        Node *fast = head;
        for (int i = 0; i < n; i++)
        {
            if (fast == nullptr)
                return false;
            fast = fast->next;
        }

        Node *curr = head;
        Node *prev = nullptr;

        while (fast != nullptr)
        {
            fast = fast->next;
            prev = curr;
            curr = curr->next;
        }

        if (prev == nullptr) // Curr is the head
        {
            head = curr->next;
        }
        else
        {
            prev->next = curr->next;
        }
        std::cout << "\nRemoving " << n << " node from end with value: " << curr->data << endl;
        delete curr;
        size--;
        return true;
    }
    // 3. Removing every kth node
    bool remove_every_kth(int k)
    {
        if (k <= 1 or head == nullptr)
        {
            return true;
        }
        // We are supposing in this function that the list is indexed from 1 not from 0
        Node *curr = head;
        int count = 1;
        while (curr != nullptr)
        {
            if ((count + 1) % k == 0)
            {
                // Check if we can safely delete the next node
                if (curr->next == nullptr)
                    break;
                Node *to_delete = curr->next;
                curr->next = to_delete->next;
                delete to_delete;
            }
            else
                curr = curr->next;
            count++;
        }
        return true;
    }
    // 4. Get the middle value
    int middle()
    {
        if (head == nullptr)
            return -1;
        Node *slow = head;
        Node *fast = head;
        while (fast != nullptr and fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        std::cout << "\nMiddle Value is: " << slow->data << endl;
        return slow->data;
    }
    // 5. Check if a loop exists or not
    bool loop_exists()
    {
        if (head == nullptr)
            return false;
        Node *slow = head;
        Node *fast = head;
        while (fast != nullptr and fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
    // 6. Give size of the loop
    int size_of_loop()
    {
        if (head == nullptr)
            return -1;
        Node *slow = head;
        Node *fast = head;
        while (fast != nullptr and fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
            {
                int count = 0;
                for (Node *p = slow; p != fast; p = p = p->next)
                    count++;
                return count;
            }
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
    list.push(30);
    list.middle();
    list.display_all();

    return 0;
}