// FILE: select.cxx
// An interactive test program for the selectionsort function

#include <algorithm>  // Provides swap
#include <cstdlib>    // Provides EXIT_SUCCESS, size_t
#include <iostream>   // Provides cout and cin
#include <bits/stdc++.h>
using namespace std;

// PROTOTYPE of the function used in this test program:
void selectionsort(int data[ ], size_t n);
// Precondition: data is an array with at least n components.
// Postcondition: The elements are rearranged so that
// data[0] <= data[1] <= ... <= data[n-1].
template <class Item>
void quicksort(Item arr[], size_t start, size_t end);
template <class Item>
size_t partition(Item arr[], size_t start, size_t end);

int main( )
{
    const char BLANK = ' ';
    const size_t ARRAY_SIZE = 10;  // Number of elements in the array to be sorted
    int data[ARRAY_SIZE];          // Array of integers to be sorted
    int user_input;                // Number typed by the user
    size_t number_of_elements;     // How much of the array is used
    size_t i;                      // Array index

    // Provide some instructions.
    cout << "Please type up to " << ARRAY_SIZE << " positive integers. ";
    cout << "Indicate the list's end with a zero." << endl;

    // Read the input numbers.
    number_of_elements = 0;
    cin >> user_input;
    while ((user_input != 0) && (number_of_elements < ARRAY_SIZE))
    {
        data[number_of_elements] = user_input;
        number_of_elements++;
        cin >> user_input;
    }

    // Sort the numbers, and print the result with two blanks after each number.
  //  selectionsort(data, number_of_elements);
    quicksort(data, 0, number_of_elements - 1);
    cout << "In sorted order, your numbers are: "<< endl;
    for (i = 0; i < number_of_elements; i++)
        cout << data[i] << BLANK << BLANK;
    cout << endl;

    return EXIT_SUCCESS;
}

void selectionsort(int data[ ], size_t n)
// Library facilities used: algorithm, cstdlib
{
    size_t i, j, index_of_largest;
    int largest;

    if (n == 0)
        return; // No work for an empty array.

    for (i = n-1; i > 0; --i)
    {
        largest = data[0];
        index_of_largest = 0;
        for (j = 1; j <= i; ++j)
        {
            if (data[j] > largest)
            {
                largest = data[j];
                index_of_largest = j;
            }
        }
        swap(data[i], data[index_of_largest]);
    }
}

template <class Item>
void quicksort(Item arr[], size_t start, size_t end)
{
  if(start < end)
  {
    size_t index = partition(arr, start, end);

    quicksort(arr, start, index - 1);
    quicksort(arr, index + 1, end);

  }
}


template <class Item>
size_t partition(Item arr[], size_t start, size_t end)
{
  //can choose any item for pivot, chose the end
  Item pivot = arr[end];

  size_t i = start - 1;

  for(size_t j = start; j <= end - 1; j++)
  {
    if(arr[j] < pivot)
    {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[end]);
  return (i + 1);
}
