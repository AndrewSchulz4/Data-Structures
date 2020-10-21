#include <iostream>
#include <array>
using namespace std;

template <class Item>
void sort(Item arr [], size_t size);

int main()
{
  int a [] = {1, 4, 2, 7, 7, 9, 3, 6, 8, 0, 1};
  size_t n = sizeof(a)/sizeof(*a);
  sort(a, n);
  for(size_t i = 0; i < n; i++)
  {
    cout << a[i] << " ";
  }
}

template <class Item>
void sort(Item arr [], size_t size)
{
  int key, j;
  //insertion sort
  for(int i = 1; i < size; i++)
  {
    key = arr[i];
    j = i - 1;
    while(j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j -= 1;
    }
    arr[j + 1] = key;
  }
}
