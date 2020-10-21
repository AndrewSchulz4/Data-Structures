#include "table2.h"
#include <iostream>

using namespace std;
using namespace main_savitch_12B;

int main()
{
  table<int> tab;
  for(int i = 0; i < 1001; i++)
  {
    tab.insert(i);
  }
  cout << tab.size() << endl;
  tab.remove(2);
  cout << tab.is_present(1) << endl;
  cout << tab.size() << endl;

  table<int> tab2(tab);
  cout << tab2.size() << endl;
}
