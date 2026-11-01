#include <iostream>
using namespace std;

void f(int arr[5])
{
    cout << sizeof(arr) << "\n";
}
struct Buffer
{
    int *data;
    int size;
};
int firstOccurrence(int *arr, int n, int key)
{
    int low = 0;
    int high = n - 1;
    int mid = 0;
    int answer = -1;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        std::cout << "Low " << low << " Mid: " << mid << " High: " << high << std::endl;
        if (arr[mid] == key)
        {
            answer = mid;
            high = mid - 1;
        }
        else if (arr[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return answer;
}

int main()
{
    // ---------------------------- Q1. Arrays & Pointer Arithmetic ----------------------------
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;
    int *q = &a[4];
    // a)
    cout << "\nPart(a)\n";
    cout << sizeof(a) << " " << sizeof(p) << "\n";
    // sizeof(a) == 20 bytes, 4*5 bytes, entire array size     |   sizeof(p)   == 8 bytes, a pointer size.
    f(a);
    // Due to "ARRAY DECAY", whenever datatype[] is written as a argument, internally it is just a datatype*
    // The array does not gets copied, but rather its pointer is passed, therby making it pass by refrence,
    // So, when sizeof(pointer) it gives 8 bytes.

    // b)
    cout << "\nPart(b)\n";
    cout << *p++ << "\n";   // ++ then *:   10
    cout << *p << "\n";     // *:   20
    cout << (*p)++ << "\n"; // 20
    cout << *p << "\n";     // 21
    cout << *++p << "\n";   // * then ++: 30

    // c)
    cout << "\nPart(c)\n";
    cout << q - p << "\n";                 // 2-bytes, a pointer is a 8-bytes, variable so, result is given in terms of 8 bytes diff.
    cout << (char *)q - (char *)p << "\n"; // 8-bytes, a char is a 1-bytes, variable so, result is given in terms of 1 bytes diff.

    // d)
    cout << "\nPart(d)\n";
    cout << (char *)(&a + 1) - (char *)a << "\n";
    // &a == address of entire array, &array = 20 bytes, we jump 20 bytes ahead, then turn the ptr into a char one, so result is 20 bytes
    cout << (char *)(a + 1) - (char *)a << "\n";
    // a decays into a int pointer, so we only jump by 4 bytes.

    // e)
    cout << "\nPart(e)\n";
    // a = p;         // an array pointer is a const pointer and cannot be changed
    // a++;           // again a const pointer cannot be updated
    p = a + 5;     // int pointer + 5 means internally int pointer + (5*4 bytes), landing on the unexpected behavior
    p = a + 6;     // same thing.
    cout << 2 [a]; // what the actual fck, ok got it.

    // Self Eval: Got 0 correct.
    // ---------------------------- Q2. Functions & Pointers ----------------------------
    // Dry ran, entire section was relatively much easier.

    // ---------------------------- Q3. 2D Arrays & Pointers  ----------------------------
    cout << "\n --- Q3 ---\n";
    // a)
    cout << "Part(a)\n";
    int B[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    cout << sizeof(B) << " " << sizeof(B[0]) << "\n";
    cout << sizeof(*B) << " " << sizeof(B[0][0]) << "\n";
    // B -> 3*4*4 = 48 bytes.
    // B[0] -> int array of size 4 -> 4*4 = 16 bytes
    // *B -> same as B[0]
    // B[0][0] -> simple int -> 4 bytes

    // b)
    cout << "Part(b)\n";
    cout << **(B + 1) << " " << *(*B + 5) << " "
         << *B[2] << " " << (*(B + 2))[3] << "\n";
    // B + 1 -> what is B ? B decays into a int(*)[4], + 1 to this, we move to the next row, so we are at B[1][0], double derefrence -> 5
    // B decays into a int pointer to int array, further derefrences into the int* at first value + 5 = 5th int address, derefrence -> 6
    // first B[2] -> address of int* [] of 3rd row, then deref it, we get 1st value of 3rd row -> 9
    // (B+2) == B[2], then deref we get address of int* of 1st element of 3rd row, a[3] == 3[a], so it is basically B[2][3] ==  12

    // e)
    cout << "Part(e)\n";
    int (*pa)[4] = B;
    pa++;
    cout << (*pa)[0] << " " << pa[1][1];

    // ---------------------------- Q4. Structs & Pointers ----------------------------
    cout << "\n --- Q4 ---\n";
    // a)
    cout << "Part(a)\n";
    Buffer aa;
    aa.size = 3;
    aa.data = new int[3]{1, 2, 3};
    Buffer b = aa;
    b.data[0] = 99;
    b.size = 10;
    cout << aa.data[0] << "  " << aa.size << "\n";

    // b)
    cout << "Part(b)\n";
    Buffer *pb = &aa;
    cout << *pb->data << "\n";
    cout << (*pb).data[1] << "\n";
    cout << ++pb->size << "\n";
    cout << (pb->data + 1 == &aa.data[1]) << "\n";

    // ---------------------------- Q6. Linear Search ----------------------------
    cout << "\n --- Q6 ---\n";
    // a)
    cout << "Part(a)\n";
    int hello[] = {2, 4, 4, 4, 4, 7, 9};
    std::cout << "Ans is: " << firstOccurrence(hello, 7, 4) << std::endl;
    return 0;
}

/*
=================================================================================
                    C++ OPERATOR PRECEDENCE TABLE
=================================================================================
Prec | Operator          | Description                    | Associativity
------+-------------------+--------------------------------+-------------------
1    | ::                | Scope resolution               | Left-to-right
------+-------------------+--------------------------------+-------------------
2    | a++  a--          | Postfix increment/decrement    | Left-to-right
    | ()                | Function call                  |
    | []                | Array subscripting             |
    | .  ->             | Member access                  |
------+-------------------+--------------------------------+-------------------
3    | ++a  --a          | Prefix increment/decrement     | Right-to-left
    | +a   -a           | Unary plus and minus           |
    | !    ~            | Logical NOT / Bitwise NOT      |
    | (type)            | C-style type cast              |
    | *                 | Indirection (Dereference)      |
    | &                 | Address-of                     |
    | sizeof            | Size-of                        |
    | co_await          | Await expression (C++20)       |
    | new  new[]        | Dynamic memory allocation      |
    | delete  delete[]  | Dynamic memory deallocation    |
------+-------------------+--------------------------------+-------------------
4    | .*  ->*           | Pointer-to-member              | Left-to-right
------+-------------------+--------------------------------+-------------------
5    | *  /  %           | Multiplication / Division / %  | Left-to-right
------+-------------------+--------------------------------+-------------------
6    | +  -              | Addition and Subtraction       | Left-to-right
------+-------------------+--------------------------------+-------------------
7    | <<  >>            | Bitwise shift left / right     | Left-to-right
------+-------------------+--------------------------------+-------------------
8    | <=>               | Three-way comparison (C++20)   | Left-to-right
------+-------------------+--------------------------------+-------------------
9    | <   <=            | Relational comparison          | Left-to-right
    | >   >=            | Relational comparison          |
------+-------------------+--------------------------------+-------------------
10   | ==  !=            | Relational equality            | Left-to-right
------+-------------------+--------------------------------+-------------------
11   | &                 | Bitwise AND                    | Left-to-right
------+-------------------+--------------------------------+-------------------
12   | ^                 | Bitwise XOR                    | Left-to-right
------+-------------------+--------------------------------+-------------------
13   | |                 | Bitwise OR                     | Left-to-right
------+-------------------+--------------------------------+-------------------
14   | &&                | Logical AND                    | Left-to-right
------+-------------------+--------------------------------+-------------------
15   | ||                | Logical OR                     | Left-to-right
------+-------------------+--------------------------------+-------------------
16   | ?:                | Ternary conditional            | Right-to-left
    | throw             | Throw expression               |
    | co_yield          | Yield expression (C++20)       |
    | =                 | Direct assignment              |
    | +=  -=            | Compound assignment (Sum/Diff) |
    | *=  /=  %=        | Compound assignment (Prod/Div) |
    | <<= >>=           | Compound assignment (Shift)    |
    | &=  ^=  |=        | Compound assignment (Bitwise)  |
------+-------------------+--------------------------------+-------------------
17   | ,                 | Comma operator                 | Left-to-right
=================================================================================
*/