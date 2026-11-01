#include <iostream>
using namespace std;

void Bubble_sort(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);
        }
    }
    return;
}

void Selection_sort(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int min_idx = i;
        for (int j = i; j < size; j++)
        {
            if (array[min_idx] > array[j])
                min_idx = j;
        }
        swap(array[i], array[min_idx]);
    }
    return;
}

void Insertion_sort(int *array, int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 and array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
    return;
}

int main()
{
    int array[] = {7, 3, 4, 5, 8};
    // Bubble_sort(array, 5);
    // Selection_sort(array, 5);
    Insertion_sort(array, 5);
    for (auto x : array)
    {
        std::cout << x;
    }
    return 0;
}