// FILE: table1.template
// TEMPLATE CLASS IMPLEMENTED: table (see table1.h for documentation)
// INVARIANT for the table ADT:
//   1. The number of records in the table is in the member variable used.
//   2. The actual records of the table are stored in the array data, with
//      a maximum of CAPACITY entries. Each used spot in the array has a
//      non-negative key. Any unused record in the array has a key field of
//      NEVER_USED (if it has never been used) or PREVIOUSLY_USED (if it once
//      was used, but is  now vacant).


#include <cassert>  // Provides assert
#include <cstdlib>  // Provides size_t
#include <iostream>

namespace main_savitch_12B
{
    template <class RecordType>
    table<RecordType>::table( )
    {
        std::size_t i;

        total_records = 0;
        for (i = 0; i < TABLE_SIZE; ++i)
            data[i] = NULL;  // Indicates a spot that's never been used.
    }

    template<class RecordType>
    table<RecordType>::table(const table& source) {
        std::size_t i;

        total_records = source.total_records;
        for (i = 0; i < TABLE_SIZE; i++)
        {
          if(is_present(i))
            data[i] = source.data[i];
          else
            data[i] = NULL;
        }
    }

    template<class RecordType>
    table<RecordType>::~table() {
        std::size_t i;

        for (i = 0; i < TABLE_SIZE; ++i) {
            while (data[i] != NULL) {
                main_savitch_6B::node <RecordType>* remove_ptr;

                remove_ptr = data[i];
                data[i] = data[i]->link();
                delete remove_ptr;
            }
            total_records = 0;
        }
    }

    template <class RecordType>
    void table<RecordType>::insert(const RecordType& entry)
    // Library facilities used: cassert
    {
        bool already_present;   // True if entry.key is already in the table
       // data[index] is location for the new entry

        assert(entry >= 0);

        // If the key wasn't already there, then find the location for the new entry.
        //could use inster function in the node class

        //chain will use the same index
        int index = hash(entry);

        main_savitch_6B::node<RecordType>* find = data[index];

        if (data[index] == NULL)
        {
            data[index] = new main_savitch_6B::node<RecordType>(entry, NULL);
            total_records++;
        }
        else
        {
          while(find->link() != nullptr)
          {
            find = find->link();
          }
          main_savitch_6B::node<RecordType>* newdata = new main_savitch_6B::node<RecordType>;
          find->set_link(newdata);
          newdata->set_data(entry);
          total_records++;

        }
    }

    template <class RecordType>
    void table<RecordType>::remove(int key)
    // Library facilities used: cassert
    {
        size_t index = hash(key);   // Spot where data[index].key == key

        assert(key >= 0);

        if (is_present(key))
        //will try to use remove function from node class
        {   // The key was found, so remove this record and reduce used by 1.
          main_savitch_6B::node<RecordType>* head = data[index];
          while (head != NULL)
          {
              main_savitch_6B::list_head_remove(head);
              total_records--;
          }
          data[index] = NULL;
        }
    }

    template <class RecordType>
    bool table<RecordType>::is_present(int key) const
    // Library facilities used: assert.h
    {
        std::size_t index = hash(key);

        assert(key >= 0);

        main_savitch_6B::node<RecordType>* temp = data[index];
        if (temp != NULL)
        {
            return true;
        }
        return false;
    }

    template <class RecordType>
    void table<RecordType>::find(int key, bool& found, RecordType& result) const
    // Library facilities used: cassert.h
    {
        assert(key >= 0);


        if (is_present(key))
        {
          std::size_t index = hash(key);
          main_savitch_6B::node<RecordType>* find = data[index];
          while(find->data() != result)
          {
            find = find->link();
          }
          if(find->data() == result)
          {
            found = true;
            result = find->data();
          }
          else
          {
            found = false;
            result = NULL;
          }
        }
    }

    template<class RecordType>
    void table<RecordType>::operator =(const table& source) {
        std::size_t i;

        total_records = source.total_records;
        for (i = 0; i < TABLE_SIZE; ++i)
            data[i] = source.data[i];
    }

    template <class RecordType>
    inline std::size_t table<RecordType>::hash(int key) const
    {
        return (key % TABLE_SIZE);
    }
}
