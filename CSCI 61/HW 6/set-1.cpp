#include <iostream>
#include <algorithm>

namespace main_savitch_11
{
  template <class Item>
  set<Item>::set( )
  {
    data_count = 0;
    child_count = 0;
    for(int i = 0; i < MAXIMUM + 2; i++)
    {
      subset[i] = nullptr;
    }
  }

  template <class Item>
  set<Item>::set(const set& source)
  {
    data_count = source.data_count;
    child_count = source.child_count;

    //Copies the data through a deep copy
  //  ****************************
    Item * data1 = new Item [MAXIMUM + 1];
    for(int i = 0; i < MAXIMUM + 1; i++)
    {
      data1[i] = source.data[i];
    }

    //Copies the subsets through a deep copy
    //  ****************************
    set *subset1 = new set [MAXIMUM + 2];
    for(int i = 0; i < MAXIMUM + 2; i++)
    {
      subset1->subset[i] = source.subset[i];
    }
  }

  template <class Item>
  void set<Item>::operator =(const set& source)
  {
    //shallow copy of the source
    data_count = source.data_count;
    child_count = source.child_count;

    for(int i = 0; i < MAXIMUM + 1; i++)
    {
      data[i] = source.data[i];
    }

    for(int i = 0; i < MAXIMUM + 2; i++)
    {
      subset[i] = source.subset[i];
    }
  }

  template <class Item>
  bool set<Item>::loose_insert(const Item& entry)
  {
    int i = 0;
    for(int j = 0; j < data_count; j++)
    {
      if(data[j - 1] < entry && entry < data[j + 1])
      {
        i = j;
      }
    }
    if(entry > data[data_count])
    {
      i = data_count;
    }
    if(data[i] == entry)
    {
      return false;
    }
    else if(is_leaf())
    {
      data[i] = entry;
      for(int x = data_count; x >= i; x--)
      {
        //I think the seg fault is here
        data[x + 1] = data[x];
      }
      data_count++;
      return true;
    }
    else
    {
      bool inserted = subset[i]->loose_insert(entry);
      if(inserted)
      {
        data_count++;
        if(data_count > MAXIMUM)
        {
          fix_excess(i);
        }
        return true;
      }

    }
  }

  template <class Item>
  void set<Item>::fix_excess(std::size_t i)
  {
    set<Item> *left = new set<Item>;
    set<Item> *right = new set<Item>;

    //**************************
    //fix bounds
    //left
    std::copy(data + 0, data + MINIMUM - 1, left->data + 0);
    std::copy(subset + 0, subset + MINIMUM - 1, left->subset + 0);

    //right
    std::copy(data + MINIMUM + 1, data + MAXIMUM, left->data + MINIMUM + 1);
    std::copy(subset + MINIMUM + 1, subset + MAXIMUM, left->subset + MINIMUM + 1);

    data[data_count] = subset[i]->data[MINIMUM];
    subset[data_count] = left;
    subset[data_count + 1] = right;
  }

  //may need to work on edge cases for less than or greater than strictly(end or beginning of the array)
  template <class Item>
  bool set<Item>::insert(const Item& entry)
  {
    if(!loose_insert(entry))
    {
      return false;
    }
    if(data_count > MAXIMUM)
    {
      set<Item> *left = new set<Item>;
      set<Item> *right = new set<Item>;

      std::copy(data + 0, data + MINIMUM - 1, left->data + 0);
      std::copy(subset + 0, subset + MINIMUM - 1, left->subset + 0);

      //right
      std::copy(data + MINIMUM + 1, data + MAXIMUM, left->data + MINIMUM + 1);
      std::copy(subset + MINIMUM + 1, subset + MAXIMUM, left->subset + MINIMUM + 1);

      set<Item> * new_top = new set<Item>;
      new_top->data[new_top->data_count] = subset[MINIMUM]->data[MINIMUM];
      data_count++;
      new_top->subset[new_top->child_count] = left;
      child_count++;
      new_top->subset[new_top->child_count + 1] = right;
      child_count++;
      return true;
    }
  }
  template <class Item>
  void set<Item>::print(int indent) const
  {
    const int EXTRA_INDENTATION = 4;    size_t i;
    //std::cout << std::setw(indent) << ""; // Print the indentation.
    // Print the data from the root.
    for (i = 0; i < data_count; ++i)
      std::cout << data[i] << " "; std::cout << std::endl;
    // Print the subtrees.
    for (i = 0; i < child_count; ++i)
      subset[i]->print(indent+EXTRA_INDENTATION);

  }

  template <class Item>
  bool set<Item>::loose_erase(const Item& target)
  {
    int i = 0;
    for(int j = 0; j < data_count; j++)
    {
      if(data[j - 1] < target && target < data[j + 1] || data[j] == target)
      {
        i = j;
        std::cout << "t";
      }
    }

    if(is_leaf() && data[i] != target)
    {
      std::cout << data[i] << data_count << std::endl;
      //not found
      return false;
    }
    else if(is_leaf() && data[i] == target)
    {
      for(int x = i; x < data_count; x++)
      {
        data[x] = data[x + 1];
      }
      data_count--;
    }
    //segmentation fault
    if(!is_leaf() && data[i] != target)
    {
      bool check_subset = subset[i]->loose_erase(target);
      if(check_subset && subset[i]->data_count == MINIMUM - 1)
      {
        fix_shortage(i);
      }
    }
    //not sure if this would be the correct if statement
    if(data_count < child_count + 1)
    {
      subset[i]->remove_biggest(data[i]);
      if(subset[i]->data_count < MINIMUM)
      {
        fix_shortage(i);
      }
      return true;
    }
    return true;
  }

  template <class Item>
  void set<Item>::clear()
  {
    //recursively delete each set from the subset and then the root set
    if(is_leaf())
    {
      data_count = 0;
      child_count = 0;
    }
    else if(!is_leaf())
    {
      for(int i = 0; i < child_count - 1; i++)
      {
        subset[i]->clear();
      }
    }
  }

  template <class Item>
  std::size_t set<Item>::count(const Item& target) const
  {
    int i = 0;
    for(int j = 0; j < data_count; j++)
    {
      if(data[j] == target)
      {
        return 1;
      }
      else if(data[j - 1] < target && target < data[j])
      {
        i = j;
      }
    }
    if(!is_leaf())
      subset[i]->count(target);
    //returns 0 if not found in the recursion
    return 0;
  }

  template <class Item>
  void set<Item>::fix_shortage(std::size_t i)
  {
    if(subset[i - 1]->data_count > MINIMUM)
    {
      //case 1
      for(int x = data_count; x >= 0; x--)
      {
        subset[i]->data[x + 1] = subset[i]->data[x];
      }
      subset[i]->data[0] = data[i - 1];
      subset[i]->data_count++;

      data[i - 1] = subset[i - 1]->data[data_count];
      subset[i - 1]->data_count--;

      if(!subset[i - 1]->is_leaf())
      {
        for(int x = data_count; x >= 0; x--)
        {
          subset[i]->subset[x + 1] = subset[i]->subset[x];
        }
        subset[i]->subset[0] = subset[i - 1]-> subset[child_count];
        subset[i]->child_count++;
        subset[i - 1]->child_count--;
      }
    }

    //case 2
    //may need to modify for loops
    else if(subset[i + 1]->data_count > MINIMUM)
    {
      subset[i]->data[data_count] = data[i + 1];
      subset[i]->data_count++;

      data[i + 1] = subset[i + 1]->data[0];
      for(int x = 0; x < child_count; x++)
      {
        subset[i + 1]->data[x] = subset[i + 1]->data[x + 1];
      }

      subset[i + 1]->data_count--;
      for(int x = 0; x < subset[i + 1]->data_count; x++)
      {
        subset[i + 1]->data[x] = subset[i + 1]->data[x + 1];
      }

      if(!subset[i + 1]->is_leaf())
      {
        subset[i]->subset[child_count] = subset[i + 1]-> subset[0];

        for(int x = 0; x < child_count; x++)
        {
          subset[i + 1]->data[x] = subset[i + 1]->data[x + 1];
        }

        for(int x = 0; x < subset[i + 1]->child_count; x++)
        {
          subset[i + 1]->subset[x] = subset[i + 1]->subset[x + 1];
        }

        subset[i]->child_count++;
        subset[i + 1]->child_count--;
      }
    }

    //case 3
    else if(subset[i - 1]->data_count == MINIMUM)
    {
      subset[i - 1]->data[data_count] = data[i - 1];
      for(int x = i; x < data_count; x++)
      {
        data[x] = data[x + 1];
      }
      data_count--;
      subset[i - 1]->data_count++;

      //copy subset i to the end of subset[i-1]
      std::copy(subset[i]->data + 0, subset[i]->data + data_count, subset[i - 1]->data + data_count);
      std::copy(subset[i]->subset + 0,subset[i]->subset + child_count, subset[i - 1]->subset + child_count);

      subset[i - 1]->data_count += subset[i]->data_count;
      subset[i - 1]->child_count += subset[i]->child_count;

      delete subset[i];
      for(int x = i; x < child_count; x++)
      {
        subset[i] = subset[i + 1];
      }
    }

    //case 4
    else if(subset[i + 1]->data_count == MINIMUM)
    {
      //shifts data array to hold data[i] at the beginning
      for(int x = i; x < data_count; x++)
      {
        subset[i + 1]->data[x] = subset[i + 1]->data[x + 1];
      }

      subset[i + 1]->data[0] = data[i];

      for(int x = i; x < data_count; x++)
      {
        data[x] = data[x + 1];
      }

      data_count--;
      subset[i + 1]->data_count++;

      //copy subset i to the end of subset[i-1]
      std::copy(subset[i + 1]->data + 0, subset[i + 1]->data + data_count, subset[i]->data + data_count);
      std::copy(subset[i + 1]->subset + 0,subset[i + 1]->subset + child_count, subset[i]->subset + child_count);

      subset[i]->data_count += subset[i + 1]->data_count;
      subset[i]->child_count += subset[i + 1]->child_count;

      delete subset[i];
      for(int x = i; x < child_count; x++)
      {
        subset[i] = subset[i + 1];
      }
    }
  }

  template <class Item>
  void set<Item>::remove_biggest(Item& removed_entry)
  {
    if(is_leaf())
    {
      removed_entry = data[data_count];
      data_count--;
    }

    else
    {
      subset[child_count-1]->remove_biggest(removed_entry);
    }
    if(subset[child_count - 1]->data_count < MINIMUM)
    {
      fix_shortage(child_count - 1);
    }
  }

  template <class Item>
  std::size_t set<Item>::erase(const Item& target)
  {
    if(!loose_erase(target))
    {
      return 0;
    }
    if(data_count == 0 && child_count == 1)
    {
      //fix root so it no longer has no value
      set<Item> * temp = new  set<Item>;
      temp = subset[0];
      for(int i = 0; i < data_count; i++)
      {
        data[i] = subset[0]->data[i];
      }
      for(int i = 0; i < child_count; i++)
      {
        subset[i] = subset[0]->subset[i];
      }
      delete temp;
    }
    return 1;
  }
}
