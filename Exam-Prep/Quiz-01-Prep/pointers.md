# DSA Practice Quiz 1

**Topics:** Arrays · Pointers · Arrays & Pointers · Functions & Pointers · Structs & Pointers · Linear Search · Binary Search · 2D Arrays & Pointers

**Time:** 60 minutes | **Total marks:** 60 | **Language:** C++

**Assumptions:** 64-bit machine, `sizeof(int) == 4`, `sizeof(int*) == 8`, `sizeof(char) == 1`.

| Q | Topic | Marks | Suggested time |
|---|-------|-------|----------------|
| 1 | Arrays & pointer arithmetic (predict) | 8 | 6 min |
| 2 | Functions & pointers (predict + code) | 8 | 8 min |
| 3 | 2D arrays & pointers (predict + code) | 8 | 8 min |
| 4 | Structs & pointers (predict + code) | 10 | 9 min |
| 5 | Linear search (code) | 8 | 8 min |
| 6 | Binary search (code + trace) | 12 | 12 min |
| 7 | Debugging round (mixed) | 6 | 5 min |
| | Buffer for review | | 4 min |

**Rules for yourself:** no compiler for the "predict" parts. Write the coding parts in a separate `.cpp` file (or in the blocks below), then compile and test them **after** the hour. Open the answer key only after you finish.

---

## Q1. Arrays & Pointer Arithmetic `[8 marks]`

> **Recall:** an array name *decays* to a pointer to its first element in most expressions. The exceptions are `sizeof`, `&`, and initialising from a string literal. Pointer arithmetic moves in units of the **pointee type**, not bytes.

Use this setup for all parts:

```cpp
int a[5] = {10, 20, 30, 40, 50};
int *p = a;
int *q = &a[4];
```

**(a) `[2]`** Predict the three values:

```cpp
cout << sizeof(a) << " " << sizeof(p) << "\n";

void f(int arr[5]) { cout << sizeof(arr) << "\n"; }
f(a);
```

**(b) `[2]`** Predict the five lines of output (each statement runs on the `p` left by the previous one):

```cpp
cout << *p++   << "\n";
cout << *p     << "\n";
cout << (*p)++ << "\n";
cout << *p     << "\n";
cout << *++p   << "\n";
```

**(c) `[1]`** Continuing from (b), predict:

```cpp
cout << q - p << "\n";
cout << (char*)q - (char*)p << "\n";
```

**(d) `[1]`** These two differ. Predict both:

```cpp
cout << (char*)(&a + 1) - (char*)a << "\n";
cout << (char*)(a + 1)  - (char*)a << "\n";
```

**(e) `[2]`** For each line, say: compile error / undefined behaviour / legal (and what it prints, if anything).

```cpp
a = p;
a++;
p = a + 5;
p = a + 6;
cout << 2[a];
```

---

## Q2. Functions & Pointers `[8 marks]`

> **Recall:** C++ passes **everything by value**. A pointer parameter is a *copy* of the address. You can change what it points to, but not the caller's pointer itself, unless you pass a pointer to that pointer (or a reference).

```cpp
int* make()                  { int x = 42; return &x; }
void alloc1(int *p)          { p = new int(7); }
void swapPtr(int *a, int *b) { int *t = a; a = b; b = t; }
```

**(a) `[1]`** Why is `make()` dangerous?

**(b) `[2]`** After `int *p = nullptr; alloc1(p);` what is `p`, and what has leaked? Write a working `alloc2` using a pointer-to-pointer, and show the call.

**(c) `[1]`** After `int x = 1, y = 2; swapPtr(&x, &y);`, what are `x` and `y`?

**(d) `[2]`** Write `void swapPointers(int **a, int **b)` that swaps the *pointers themselves*. Then predict what this prints:

```cpp
int x = 1, y = 2;
int *px = &x, *py = &y;
swapPointers(&px, &py);
cout << *px << " " << *py << " " << x << " " << y;
```

**(e) `[2]`** Write `int* findMax(int *arr, int n)` that returns a **pointer to** the largest element (not its value). Then, in `main`, set the largest element of an array to `0` in **one statement**, with no extra index variable.

```cpp
// your code here
```

---

## Q3. 2D Arrays & Pointers `[8 marks]`

> **Recall:** 2D arrays are stored **row-major** in one contiguous block. For `int B[3][4]`, `B` decays to `int (*)[4]`, a pointer to a *row* of 4 ints. And `B[i][j]` is exactly `*(*(B+i)+j)`.

```cpp
int B[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
```

**(a) `[2]`** Predict: `sizeof(B)`, `sizeof(B[0])`, `sizeof(*B)`, `sizeof(B[0][0])`.

**(b) `[2]`** Predict each value:

```cpp
**(B+1)
*(*B + 5)
*B[2]
(*(B+2))[3]
```

**(c) `[1]`** Why does `int **pp = B;` fail to compile, while `int (*pr)[4] = B;` compiles?

**(d) `[2]`** Write `long sumAll(const int *base, int rows, int cols)` that sums every element using **one pointer and one loop** (no `[ ]`, no nested loops). Show the call that passes `B` to it.

**(e) `[1]`** Predict the output:

```cpp
int (*p)[4] = B;
p++;
cout << (*p)[0] << " " << p[1][1];
```

```cpp
// your code here
```

---

## Q4. Structs & Pointers `[10 marks]`

> **Recall:** `ptr->member` is `(*ptr).member`. The `->` and `.` operators bind **tighter** than unary `*` and `++`. A struct copy copies member *values*, so a pointer member is copied as an address (a **shallow copy**).

```cpp
struct Buffer { int *data; int size; };
```

**(a) `[2]`** Predict the output:

```cpp
Buffer a;
a.size = 3;
a.data = new int[3]{1, 2, 3};
Buffer b = a;
b.data[0] = 99;
b.size = 10;
cout << a.data[0] << " " << a.size;
```

**(b) `[2]`** With `Buffer *pb = &a;` (state as left by (a)), predict each:

```cpp
*pb->data
(*pb).data[1]
++pb->size
pb->data + 1 == &a.data[1]
```

**(c) `[3]`** Write `Buffer deepCopy(const Buffer *src)` that returns an independent copy. Handle `size == 0`.

**(d) `[2]`** Write `void destroy(Buffer *b)` that frees the memory and leaves the struct in a safe state. Explain in one line why it takes a pointer and why you reset the members.

**(e) `[1]`** What is `sizeof` each struct (typical compiler)?

```cpp
struct X { char c; int x; char d; };
struct Y { int x; char c; char d; };
```

```cpp
// your code here
```

---

## Q5. Linear Search `[8 marks]`

> **Recall:** O(n) time, works on unsorted data. Real libraries (e.g. `std::find`) search a half-open range `[first, last)` and return `last` when nothing is found. That works for any subrange and avoids a "magic" sentinel like `-1`.

**(a) `[3]`** Write `int* linearSearch(int *first, int *last, int key)` that searches `[first, last)` and returns a pointer to the **first** match, or `last` if not found. Use pointer iteration only.

**(b) `[2]`** Using **only calls to `linearSearch`** (no index loops), write `int countAll(int *arr, int n, int key)` that counts every occurrence of `key`.

**(c) `[3]`** **Sentinel linear search.** Write `int sentinelSearch(int arr[], int n, int key)` that returns the index of the first match or `-1`. Place `key` at the last position as a sentinel so the loop needs only **one** comparison per element. The array must be **restored** afterwards, and the case where `key` was originally at `arr[n-1]` must still work.

```cpp
// your code here
```

---

## Q6. Binary Search `[12 marks]`

> **Recall:** requires a **sorted** array. Each step halves the range, so it takes about log₂(n) steps. Most bugs are boundary bugs: `lo <= hi` vs `lo < hi`, `mid±1`, and overflow in `mid`.

**(a) `[4]`** Write `int firstOccurrence(const int *arr, int n, int key)` that returns the index of the **first** occurrence of `key` in a sorted array that may contain duplicates, or `-1`. It must run in O(log n) (no linear scan after finding one match) and compute `mid` safely.

**(b) `[2]`** Trace your function on `{2, 4, 4, 4, 4, 7, 9}` with `key = 4`. Show `lo`, `hi`, `mid` for every iteration and the final answer.

**(c) `[4]`** A matrix is stored row-major in one block. Rows are sorted left to right, and the first element of each row is greater than the last element of the previous row. Write:

```cpp
bool searchMatrix(const int *base, int rows, int cols, int key, int *r, int *c);
```

It must binary-search the matrix as if it were **one flat sorted array**. Use `*(base + mid)` for access (no `[ ][ ]`). On success, store the row and column in `*r` and `*c` and return `true`.

**(d) `[2]`** Two short answers:
1. Why can `mid = (lo + hi) / 2` be a bug, and what is the safe form?
2. A student writes `int lo = 0, hi = n - 1; while (lo < hi) { ... }`. Give a concrete input where this fails.

```cpp
// your code here
```

---

## Q7. Debugging Round `[6 marks]`

> **Recall:** every bug here is a classic. Find **six** bugs (1 mark each) and write a one-line fix for each.

```cpp
#include <iostream>
using namespace std;

int* readScores(int n) {
    int scores[100];
    for (int i = 0; i <= n; i++)
        cin >> scores[i];
    return scores;
}

double average(int arr[]) {
    int sum = 0;
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

int main() {
    int *s = readScores(5);
    cout << average(s) << endl;
    int *t = new int[5];
    t = s;
    delete t;
}
```

---
---

# Answer Key (open after the hour)

<details>
<summary><b>Q1 answers</b></summary>

**(a)** `20 8` and then `8`.
`sizeof(a)` is the whole array (5 × 4). `sizeof(p)` is a pointer. In `f`, `int arr[5]` is silently `int *arr`, so the `5` is ignored and `sizeof(arr)` is 8.

**(b)** `10`, `20`, `20`, `21`, `30`
- `*p++` is `*(p++)`: yields 10, then `p` moves to `a[1]`.
- `*p` is 20.
- `(*p)++` yields 20, then `a[1]` becomes 21. `p` does **not** move.
- `*p` is 21.
- `*++p` moves `p` to `a[2]`, then yields 30.

**(c)** `2` and `8`. `p` is at `a[2]`, `q` at `a[4]`. Pointer subtraction counts **elements**; after casting to `char*` it counts **bytes**.

**(d)** `20` and `4`. `&a` has type `int (*)[5]`, so `+1` skips the **whole array**. `a` decays to `int*`, so `+1` skips one int. Same starting address, different types.

**(e)**
- `a = p;` **compile error**: an array name is not an assignable lvalue.
- `a++;` **compile error**: same reason.
- `p = a + 5;` **legal**: one-past-the-end may be formed and compared, but **never dereferenced**.
- `p = a + 6;` **undefined behaviour**: forming a pointer beyond one-past-the-end is already UB, even without dereferencing.
- `cout << 2[a];` **legal**, prints `30`, because `a[i]` is defined as `*(a + i)` and addition is commutative.

</details>

<details>
<summary><b>Q2 answers</b></summary>

**(a)** `x` lives on the stack frame of `make()` and dies on return. The returned pointer is **dangling**; using it is undefined behaviour. Compilers warn "address of local variable returned".

**(b)** `p` is still `nullptr`, because `alloc1` modified its own **copy** of the pointer. The `new int(7)` is **leaked**: nobody holds its address.

```cpp
void alloc2(int **p) { *p = new int(7); }

int *p = nullptr;
alloc2(&p);        // p now points to the new int
// ... use *p ...
delete p;
```
(C++ alternative: `void alloc3(int *&p) { p = new int(7); }`.)

**(c)** `x = 1`, `y = 2`. Only the local copies of the pointers were swapped.

**(d)**
```cpp
void swapPointers(int **a, int **b) {
    int *t = *a;
    *a = *b;
    *b = t;
}
```
Output: `2 1 1 2`. The pointers swapped targets (`px` → `y`, `py` → `x`), but `x` and `y` themselves are untouched.

**(e)**
```cpp
int* findMax(int *arr, int n) {         // assumes n > 0
    int *best = arr;
    for (int *it = arr + 1; it < arr + n; ++it)
        if (*it > *best) best = it;
    return best;
}

*findMax(arr, n) = 0;                   // returning a pointer into the caller's array is safe
```

</details>

<details>
<summary><b>Q3 answers</b></summary>

**(a)** `48`, `16`, `16`, `4`. `B` is 3 rows × 16 bytes. `B[0]` and `*B` are both "row 0", an `int[4]`.

**(b)** `5`, `6`, `9`, `12`
- `**(B+1)` is `B[1][0]`.
- `*(*B+5)` is flat index 5, which is `B[1][1]`.
- `*B[2]` is `*(B[2])`, which is `B[2][0]`.
- `(*(B+2))[3]` is `B[2][3]`.

**(c)** `B` decays to `int (*)[4]` (pointer to an array of 4 ints). `int **` expects a pointer to an `int*`, but a true 2D array contains **no `int*` objects**, only contiguous ints. Likewise, `int *arr[4]` is an **array of 4 pointers**, while `int (*arr)[4]` is a **pointer to an array of 4 ints**.

**(d)**
```cpp
long sumAll(const int *base, int rows, int cols) {
    long s = 0;
    for (const int *p = base; p < base + rows * cols; ++p) s += *p;
    return s;
}

sumAll(&B[0][0], 3, 4);   // or sumAll(*B, 3, 4); result is 78
```
`sumAll(B, 3, 4)` does not compile, because `int (*)[4]` does not convert to `const int *`. (Walking across rows through a pointer derived from row 0 is technically a grey area in the standard, but it is the universal idiom and works everywhere.)

**(e)** `5 10`. After `p++`, `p` points to row 1. `(*p)[0]` is `B[1][0]`. `p[1]` is the row after that, row 2, so `p[1][1]` is `B[2][1]`.

</details>

<details>
<summary><b>Q4 answers</b></summary>

**(a)** `99 3`. `b = a` copies the **pointer value**, so both structs share the same heap block (shallow copy). `size` is a plain int, so it stays independent.

**(b)** `99`, `2`, `4`, `1`
- `*pb->data` is `*(pb->data)`, i.e. `a.data[0]`, which is 99.
- `(*pb).data[1]` is 2.
- `++pb->size` increments the **member** `size` (3 → 4), not `pb`.
- The comparison is true, so it prints `1`.

**(c)**
```cpp
Buffer deepCopy(const Buffer *src) {
    Buffer copy;
    copy.size = src->size;
    copy.data = (src->size > 0) ? new int[src->size] : nullptr;
    for (int i = 0; i < src->size; i++)
        copy.data[i] = src->data[i];
    return copy;
}
```

**(d)**
```cpp
void destroy(Buffer *b) {
    delete[] b->data;
    b->data = nullptr;
    b->size = 0;
}
```
It takes a **pointer** so it can modify the caller's struct. Passing by value would leave the caller's `data` dangling. Resetting to `nullptr` makes an accidental second `destroy` harmless (`delete[] nullptr` is a no-op) and makes misuse easier to detect.

**(e)** `12` and `8`. In `X`, padding goes after `c` (3 bytes) and after `d` (3 bytes). Ordering members from largest to smallest alignment removes most padding.

</details>

<details>
<summary><b>Q5 answers</b></summary>

**(a)**
```cpp
int* linearSearch(int *first, int *last, int key) {
    for (int *p = first; p != last; ++p)
        if (*p == key) return p;
    return last;
}
```
Returning `last` rather than `nullptr` or `-1` means the same function works on any subrange and the "not found" result is still a valid, comparable pointer.

**(b)**
```cpp
int countAll(int *arr, int n, int key) {
    int count = 0;
    int *end = arr + n;
    int *p = linearSearch(arr, end, key);
    while (p != end) {
        count++;
        p = linearSearch(p + 1, end, key);   // resume AFTER the match
    }
    return count;
}
```

**(c)**
```cpp
int sentinelSearch(int arr[], int n, int key) {
    if (n == 0) return -1;
    int last = arr[n - 1];
    arr[n - 1] = key;              // sentinel guarantees the loop stops
    int i = 0;
    while (arr[i] != key) i++;     // one comparison per element, no bounds check
    arr[n - 1] = last;             // restore
    if (i < n - 1 || last == key) return i;
    return -1;                     // we only "found" the sentinel itself
}
```
The final check is needed because stopping at index `n-1` could mean either "real match" or "only the sentinel matched". Comparisons drop from about 2n (value check plus bounds check) to about n. The array is temporarily modified, so this is not safe on read-only data or when other threads read the array.

</details>

<details>
<summary><b>Q6 answers</b></summary>

**(a)**
```cpp
int firstOccurrence(const int *arr, int n, int key) {
    int lo = 0, hi = n - 1, ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == key)      { ans = mid; hi = mid - 1; }   // keep looking LEFT
        else if (arr[mid] < key)  lo = mid + 1;
        else                      hi = mid - 1;
    }
    return ans;
}
```

**(b)** Array `{2,4,4,4,4,7,9}`, `n = 7`, `key = 4`:

| iter | lo | hi | mid | arr[mid] | action |
|------|----|----|-----|----------|--------|
| 1 | 0 | 6 | 3 | 4 | match, `ans = 3`, `hi = 2` |
| 2 | 0 | 2 | 1 | 4 | match, `ans = 1`, `hi = 0` |
| 3 | 0 | 0 | 0 | 2 | `2 < 4`, `lo = 1` |

Now `lo = 1 > hi = 0`, so the loop ends. **Answer: 1.**

**(c)**
```cpp
bool searchMatrix(const int *base, int rows, int cols, int key, int *r, int *c) {
    int lo = 0, hi = rows * cols - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = *(base + mid);
        if (val == key) {
            *r = mid / cols;
            *c = mid % cols;
            return true;
        }
        if (val < key) lo = mid + 1;
        else           hi = mid - 1;
    }
    return false;
}
```
Flat index `k` maps to row `k / cols` and column `k % cols`. That is exactly why row-major layout matters.

**(d)**
1. `lo + hi` can exceed `INT_MAX` for very large arrays and wrap to a negative number. Safe form: `mid = lo + (hi - lo) / 2`.
2. Any input with one element, e.g. `{5}` with `key = 5`: `lo = 0, hi = 0`, so `lo < hi` is false and the loop never runs, returning "not found". `lo < hi` is only correct with the half-open convention (`hi = n`, `hi = mid`), and mixing the two conventions is the classic bug.

</details>

<details>
<summary><b>Q7 answers</b></summary>

1. `i <= n` reads **n+1** values. Fix: `i < n`.
2. `readScores` returns the address of a **local array** (dangling pointer). Fix: `int *scores = new int[n];` (caller must `delete[]`), or let the caller own the array.
3. `sizeof(arr)` inside `average` is the **pointer size** (8), so `n` becomes 2, not 5. Fix: pass `n` as a parameter.
4. `sum / n` is **integer division** before conversion to `double`. Fix: `(double)sum / n`.
5. `t = s;` overwrites the only pointer to the `new int[5]` block, causing a **memory leak**. Fix: `delete[] t;` before reassigning, or don't allocate at all.
6. `delete t;` has two problems. It uses `delete` instead of `delete[]` for an array, and after `t = s` it would free memory that was **never allocated with `new`** (a dead stack array). Fix: only `delete[]` pointers that came from `new[]`.

</details>

---

# Tricky Things Cheat-Sheet (even experienced people trip on these)

**Arrays & pointers**
- `a`, `&a`, `&a[0]` all hold the same address, but have different types: `int*`, `int(*)[5]`, `int*`. So `&a + 1` jumps the whole array, `a + 1` jumps one element.
- `void f(int arr[5])` and `void f(int arr[])` are both `void f(int *arr)`. The size is discarded, and `sizeof(arr)` is the pointer size.
- `a[i] == *(a+i) == *(i+a) == i[a]`.
- Pointer difference counts elements and is only valid inside the **same array**. Forming `a + n` (one past the end) is legal, but dereferencing it is not. Forming `a + n + 1` is already UB.
- Precedence: `*p++` (use then advance), `(*p)++` (increment the **value**), `*++p` (advance then use), `++*p` (increment the value, use new).
- `const int *p` (can't change `*p`) vs `int *const p` (can't change `p`) vs `const int *const p` (neither).

**Functions & pointers**
- Never return the address of a local. Returning pointers to heap memory, `static` locals, or the **caller's own array** is fine.
- To change a caller's pointer, you need `T**` (or `T*&`). To change a caller's value, `T*` is enough.
- Each `new` needs exactly one `delete`, each `new[]` exactly one `delete[]`. Deleting twice, mismatching them, or deleting stack memory is UB.

**2D arrays**
- `int *a[4]` is an array of 4 pointers. `int (*a)[4]` is a pointer to a row of 4 ints. Parentheses matter.
- A true 2D array is **not** convertible to `int**`. Only the first dimension may be omitted in a parameter: `int m[][4]`.
- `B[i][j]` is `*(*(B+i)+j)` and sits at flat index `i*cols + j`.

**Structs**
- `ptr->member` equals `(*ptr).member`. In `*pb->data`, `->` binds first, so it means `*(pb->data)`.
- Copying a struct with a pointer member is a **shallow copy**: two owners, one block, and a double free waiting to happen.
- Member order changes `sizeof` because of padding and alignment.

**Searching**
- Linear search needs no sorting. Binary search is **meaningless on unsorted data** and silently returns wrong answers.
- Pick **one** binary search convention and stick to it: closed `[lo, hi]` with `lo <= hi` and `mid±1`, or half-open `[lo, hi)` with `lo < hi` and `hi = mid`.
- Compute `mid = lo + (hi - lo) / 2`.
- With duplicates, a plain binary search returns *some* match. For the first or last one, keep searching after a hit.
- ~20 steps are enough for 1,000,000 elements and ~30 for 1,000,000,000.

**Good luck! After finishing, compile and test every function you wrote, since running your own code catches boundary bugs faster than any answer key.**
