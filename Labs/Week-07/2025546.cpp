/*
Name:   Husnain-Afzal
Reg:    2025546
Sec:    CS(C2)
*/
#include <iostream>
using namespace std;

// --- Task:01 ---
void insertion_sort(int *array, const int size) // Since it pointer to array is passed, value will be updated directly, not limited to functions scope.
{
    // Repeat the process and insert the correct value in its place in each iteration
    for (int step = 1; step < size; step++)
    {
        int key = array[step]; // store value so it is not lost later by over writing
        int j = step - 1;
        while (j >= 0 and array[j] > key)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

// helper.
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void print_array(const int *array, const int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}
// --- Task:02 ---
void selection_sort(int *array, const int size)
{
    // Repeate the process and swap the least from step onwards in each iteration.
    for (int step = 0; step < size; step++)
    {
        // set initial lowest index(guess)
        int min_val_index = step;
        for (int i = step + 1; i < size; i++) // loop to get actual lowest value's index
        {
            if (array[i] < array[min_val_index])
                min_val_index = i;
        }
        // simply swap it in place
        swap(&array[min_val_index], &array[step]);
    }
}

int main()
{
    int a[] = {5, 2, 9, 1, 5, 6};
    int b[] = {5, 2, 9, 1, 5, 6};
    const int n = 6;
    std::cout << "Unsorted: a" << std::endl;
    print_array(a, n);
    std::cout << "Unsorted: b" << std::endl;
    print_array(b, n);

    insertion_sort(a, n);
    selection_sort(b, n);

    std::cout << "Sorted: a" << std::endl;
    print_array(a, n); // 1 2 5 5 6 9
    std::cout << "Sorted: b" << std::endl;
    print_array(b, n); // 1 2 5 5 6 9
    return 0;
}