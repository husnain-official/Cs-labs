# DSA Practice Quiz: Linked Lists

**Topics:** Singly · Doubly · Circular linked lists · pointer rewiring · edge cases · cycle detection · memory safety

**Time:** 30 minutes | **Total marks:** 30 | **Language:** C++

**Node definitions used throughout:**

```cpp
struct Node  { int data; Node *next; };            // singly / circular
struct DNode { int data; DNode *prev, *next; };    // doubly
```

| Q | Topic | Marks | Suggested time |
|---|-------|-------|----------------|
| 1 | Pointer tracing, pass-by-value, memory bugs, complexity | 5 | 4 min |
| 2 | Singly list: reverse + delete-all (code) | 6 | 6 min |
| 3 | Cycle detection (Floyd) + proof | 6 | 5 min |
| 4 | Doubly list: insert/remove in O(1) | 6 | 6 min |
| 5 | Circular list: tail pointer + Josephus | 7 | 7 min |
| | Buffer | | 2 min |

**Rules for yourself:** write the code on paper or in a separate `.cpp` file. After the 30 minutes, **compile and test every function on lists of length 0, 1, 2 and many.** That is how most real bugs get caught. Open the answer key only after you finish.

---

## Q1. Tracing, Pass-by-Value & Memory Bugs `[5 marks]`

> **Recall:** a list is just a `head` pointer plus a chain of `next` pointers. Losing the only pointer to a node means losing it **and everything after it**. A function that receives `Node *head` receives a **copy** of the pointer.

```cpp
Node *head = new Node{1, nullptr};
head->next = new Node{2, nullptr};
head->next->next = new Node{3, nullptr};
```

**(a) `[1]`** Run this on the list above. Draw or write the resulting list from `head`:

```cpp
Node *p = head;
Node *q = head->next;
p->next = q->next;
q->next = p;
head = q;
```

**(b) `[1]`** Right after (a), what happens when this runs?

```cpp
cout << head->next->next->next->data;
```

**(c) `[1]`** This function is meant to insert at the front. The list never changes. Why? Give **two** different fixes.

```cpp
void pushFront(Node *head, int v) {
    Node *n = new Node{v, head};
    head = n;
}
```

**(d) `[1]`** This function is meant to free the whole list. What is the bug and how do you fix it?

```cpp
void freeList(Node *head) {
    for (Node *p = head; p != nullptr; p = p->next)
        delete p;
}
```

**(e) `[1]`** Give the time complexity of each (list of n nodes):
1. Access the i-th element
2. Insert at the front (singly)
3. Insert at the back of a singly list with **only a head pointer**
4. Delete the **last** node of a singly list, **even with a tail pointer**
5. Delete a node in a doubly list, **given a pointer to that node**

---

## Q2. Singly List: Reverse & Delete-All `[6 marks]`

> **Recall:** most singly-list bugs come from (1) updating pointers in the wrong order and (2) forgetting that the **head** is a special case.

**(a) `[3]`** Write `Node* reverse(Node *head)` that reverses the list **in place, iteratively**, and returns the new head. No new nodes, no recursion, O(n) time, O(1) extra space. It must work for 0, 1 and many nodes.

**(b) `[3]`** Write `void removeAll(Node **head, int key)` that deletes **every** node with `data == key`. It must:
- free the removed nodes,
- handle consecutive matches and a match at the head,
- use **one loop and no special case for the head** (hint: think about a pointer to the *link* that points to the current node).

```cpp
// your code here
```

---

## Q3. Cycle Detection `[6 marks]`

> **Recall:** a list is **cyclic** if some node's `next` points back to an earlier node. Plain traversal then never terminates. Floyd's algorithm uses two pointers moving at different speeds, with O(1) extra space.

**(a) `[2]`** Write `bool hasCycle(Node *head)` using the slow/fast pointer technique.

**(b) `[2]`** Write `Node* cycleStart(Node *head)` that returns the node where the cycle begins, or `nullptr` if there is no cycle.

**(c) `[2]`** Explain why this works: after the two pointers meet, resetting **one** pointer to `head` and then moving **both** one step at a time makes them meet exactly at the cycle's start. Use: μ = steps from head to the cycle start, λ = cycle length, k = steps from the cycle start to the first meeting point.

```cpp
// your code here
```

---

## Q4. Doubly Linked List `[6 marks]`

> **Recall:** every interior node must satisfy `n->next->prev == n` and `n->prev->next == n`. Insertion touches up to **four** pointers. Removal touches up to **two** neighbours plus possibly `head`/`tail`.

Assume the list keeps only a `head` pointer.

**(a) `[2]`** Write `void insertAfter(DNode *pos, int v)` that inserts a new node right after `pos`. It must be correct when `pos` is the last node.

**(b) `[3]`** Write `void removeNode(DNode **head, DNode *node)` that unlinks and frees `node` in **O(1)**, given a pointer to it. It must be correct when `node` is the head, the tail, or the only node.

**(c) `[1]`** A buggy insert fixes all the `next` pointers but forgets one of the `prev` pointers. Forward traversal still looks perfect. Describe a concrete symptom that would later expose the bug.

```cpp
// your code here
```

---

## Q5. Circular List, Tail Pointer & Josephus `[7 marks]`

> **Recall:** in a circular singly list the last node points back to the first. Storing a pointer to the **tail** (not the head) gives O(1) access to **both** ends, because `head == tail->next`. An empty list is `tail == nullptr`. Normal traversal with `while (p != nullptr)` loops forever.

**(a) `[2]`** Write `void pushBack(Node **tail, int v)` for this representation. It must handle the empty list.

**(b) `[1]`** Write `void printAll(Node *tail)` that prints every element **once**. Use a `do-while`, and say in one line why a plain `while (p != head)` loop would be wrong when starting at `head`.

**(c) `[4]`** **Josephus problem.** `n` people numbered `1..n` stand in a circle. Starting from person 1, count `k` people and eliminate the k-th, then continue counting from the next person. Repeat until one person remains. Write `int josephus(int n, int k)` that builds a circular linked list and returns the survivor's number. Free every node. (`josephus(7, 3)` should return `4`.)

```cpp
// your code here
```

---
---

# Answer Key (open after the 30 minutes)

<details>
<summary><b>Q1 answers</b></summary>

**(a)** `2 → 1 → 3 → nullptr`.
`p` is node 1, `q` is node 2. `p->next = q->next` makes 1 point to 3. `q->next = p` makes 2 point to 1. `head = q` makes 2 the new head. (The order matters: if you do `q->next = p` first, you lose node 3.)

**(b)** `head->next->next->next` is `nullptr`, so `->data` **dereferences a null pointer**: undefined behaviour, usually a crash (segmentation fault).

**(c)** `head` inside `pushFront` is a **copy** of the caller's pointer. Reassigning it changes only the copy, and the new node is **leaked**. Fixes:
```cpp
void pushFront(Node **head, int v) { *head = new Node{v, *head}; }   // pointer to pointer
void pushFront(Node *&head, int v) { head = new Node{v, head}; }     // reference
Node* pushFront(Node *head, int v) { return new Node{v, head}; }     // return the new head
```

**(d)** `p->next` is evaluated **after** `delete p`, which is use-after-free (undefined behaviour). Save the next pointer first:
```cpp
void freeList(Node *head) {
    while (head) {
        Node *next = head->next;
        delete head;
        head = next;
    }
}
```

**(e)**
1. O(n)
2. O(1)
3. O(n), because you must walk to the last node
4. O(n): you need the **second-to-last** node to set its `next = nullptr`, and a singly list can't go backwards. The tail pointer doesn't help.
5. O(1), because `prev` and `next` give both neighbours directly.

</details>

<details>
<summary><b>Q2 answers</b></summary>

**(a)**
```cpp
Node* reverse(Node *head) {
    Node *prev = nullptr;
    while (head) {
        Node *next = head->next;   // 1. save the rest BEFORE overwriting
        head->next = prev;         // 2. flip the link
        prev = head;               // 3. advance both pointers
        head = next;
    }
    return prev;                   // prev is the old tail = new head
}
```
Empty list returns `nullptr`; one node returns itself. If you flip the link before saving `next`, the rest of the list is lost.

**(b)**
```cpp
void removeAll(Node **head, int key) {
    Node **link = head;                    // address of the pointer that points at the current node
    while (*link) {
        if ((*link)->data == key) {
            Node *dead = *link;
            *link = dead->next;            // bypass the node (works for head too)
            delete dead;                   // do NOT advance: *link is now a new, unchecked node
        } else {
            link = &(*link)->next;         // advance only on a non-match
        }
    }
}
```
`link` first points to `head` itself, then to the `next` field of each kept node. So "removing the head" and "removing a middle node" are the same operation, with no special case.

</details>

<details>
<summary><b>Q3 answers</b></summary>

**(a)**
```cpp
bool hasCycle(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {       // order matters: check fast before fast->next
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;                      // fast reached nullptr: the list ends
}
```

**(b)**
```cpp
Node* cycleStart(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {            // phase 1: they met inside the cycle
            slow = head;               // phase 2: restart one pointer from head
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;     // both now move 1 step at a time
            }
            return slow;               // the cycle's first node
        }
    }
    return nullptr;
}
```

**(c)** When they first meet:
- slow has travelled `μ + k` steps (it never completes a full lap before the meeting).
- fast has travelled `2(μ + k)` steps, which is also `μ + k + mλ` for some whole number `m ≥ 1` of extra laps.

Setting these equal gives `μ + k = mλ`, so **`μ = mλ − k`**.

From the meeting point (which is `k` steps into the cycle), walking `μ = mλ − k` more steps lands at position `k + mλ − k = mλ`, which is the cycle start (a whole number of laps from the start). The pointer from `head` also reaches the cycle start after exactly `μ` steps. Both arrive there at the same time, so they meet at the start.

Why do they meet at all? Once both are in the cycle, fast gains exactly **one node per step** on slow, so the gap shrinks by 1 each step and can't be jumped over.

</details>

<details>
<summary><b>Q4 answers</b></summary>

**(a)**
```cpp
void insertAfter(DNode *pos, int v) {
    DNode *n = new DNode{v, pos, pos->next};   // new->prev = pos, new->next = old next
    if (pos->next) pos->next->prev = n;        // only if there IS a next node
    pos->next = n;
}
```
Fill in `n`'s pointers first, then fix the neighbours, so you never lose a node. The `if` is the "pos is the tail" edge case.

**(b)**
```cpp
void removeNode(DNode **head, DNode *node) {
    if (node->prev) node->prev->next = node->next;
    else            *head = node->next;            // node was the head
    if (node->next) node->next->prev = node->prev; // node was NOT the tail
    delete node;
}
```
If the list also stores a `tail`, update it too when `node->next == nullptr`. For a single-node list, both `if`s take the "no neighbour" branch, so `*head` becomes `nullptr`.

**(c)** Any of these expose it: a **backward traversal** from the tail skips nodes or stops early; a later `removeNode` on the affected node unlinks the wrong neighbour; or `node->prev->next != node`, so deletion corrupts the list or crashes. The list is consistent forward and **silently broken backward**.

</details>

<details>
<summary><b>Q5 answers</b></summary>

**(a)**
```cpp
void pushBack(Node **tail, int v) {
    Node *n = new Node{v, nullptr};
    if (*tail == nullptr) {            // empty: node points to itself
        n->next = n;
        *tail = n;
        return;
    }
    n->next = (*tail)->next;           // new node points to head
    (*tail)->next = n;                 // old tail points to new node
    *tail = n;                         // new node becomes tail
}
```
`pushFront` is identical **except you don't move `*tail`** (except when the list was empty). That's why one tail pointer gives O(1) at both ends.

**(b)**
```cpp
void printAll(Node *tail) {
    if (!tail) return;
    Node *head = tail->next;
    Node *p = head;
    do {
        cout << p->data << " ";
        p = p->next;
    } while (p != head);
}
```
Starting at `p = head`, the condition `p != head` is **already false** at the start, so a plain `while` loop would print nothing. `do-while` runs the body once first.

**(c)**
```cpp
int josephus(int n, int k) {
    Node *head = new Node{1, nullptr};
    Node *tail = head;
    for (int i = 2; i <= n; i++) {
        tail->next = new Node{i, nullptr};
        tail = tail->next;
    }
    tail->next = head;                       // close the circle

    Node *prev = tail;                       // node BEFORE the current counting start
    while (prev->next != prev) {             // more than one node left
        for (int i = 1; i < k; i++)
            prev = prev->next;               // stop on the node just before the k-th
        Node *victim = prev->next;
        prev->next = victim->next;           // unlink
        delete victim;
    }
    int survivor = prev->data;
    delete prev;
    return survivor;
}
```
Tracking the node **before** the victim is what makes the deletion possible in a singly list. For `(7, 3)` the elimination order is 3, 6, 2, 7, 5, 1, leaving **4**. For `k = 1` people are eliminated in order and `n` survives.

</details>

---

# Tricky Things Cheat-Sheet (people still trip on these a year later)

**Pointer mechanics**
- `Node *head` as a function parameter is a **copy**. To change the caller's head, use `Node**`, `Node*&`, or return the new head.
- Order of updates decides whether you **lose the rest of the list**. Wire the new node *first* (`n->next = ...`), then change existing nodes.
- `p == q` compares **addresses**, not values. `p->data == q->data` compares values.
- `head = head->next` without `delete` is a **memory leak**. `delete p; p = p->next;` is a **use-after-free**. Always save `next` first.
- `Node **link` (pointer to the link) removes the "is it the head?" special case from insert and delete.
- A **dummy/sentinel head node** removes the same special case in a different way, at the cost of one extra node.

**Edge cases to test every time**
- Empty list, 1 node, 2 nodes, deleting head, deleting tail, deleting the only node, key not present, all nodes equal to the key.
- `while (fast && fast->next)`: the order matters, because `&&` short-circuits and prevents dereferencing `nullptr`.

**Singly list**
- With a tail pointer: insert back is O(1), but **delete back is still O(n)**, since you need the predecessor.
- Reverse needs **three** roles: `prev`, `curr`, `next`.
- Deleting a node when you only have a pointer to it (and it is **not** the tail): copy `next`'s data into it and delete `next`. This fails for the tail node and invalidates any other pointer to the deleted `next` node.

**Doubly list**
- Insert touches up to **4** pointers, remove up to **2** neighbours plus `head`/`tail`.
- Invariant for every interior node: `n->next->prev == n` and `n->prev->next == n`. A bug that breaks only one direction stays hidden until you traverse backwards.
- Costs: 2 pointers per node (more memory, more updates) in exchange for O(1) delete-by-pointer and backward traversal.

**Circular list**
- Traversal needs `do-while` (or an explicit count). `while (p != nullptr)` never ends.
- Keep a **tail** pointer: `head = tail->next`, so you get O(1) at both ends.
- A single node points to **itself**, and removing it must reset the list to empty (`tail = nullptr`).
- To "break" the circle before using normal singly-list code, set `tail->next = nullptr` (and restore it later).

**Cycle detection**
- Fast moving 2 steps never "jumps over" slow: the gap closes by exactly 1 per step.
- Phase 2 works because `μ = mλ − k` (see Q3c). Cycle **length** is found by walking from the meeting point until you return to it.

**Linked list vs array (conceptual traps)**
- No random access: `a[i]` is O(1), the list equivalent is O(n).
- Insert/delete is O(1) **only once you already have the position**. Finding it is usually O(n).
- Poor cache locality and per-node allocation overhead (pointer + allocator metadata) often make arrays faster in practice, even for "insert-heavy" workloads.
- Binary search on a linked list gains **nothing**, because reaching the middle is O(n).

**Good luck! After finishing, run your own versions on tiny lists (0, 1, 2 nodes) first: most linked-list bugs show up there.**
