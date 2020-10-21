#include <iostream>
#include "set.h"

using namespace std;
using namespace main_savitch_11;

int main(){
  set<int> a;
  set<int> b(a);
  a = b;
  for(size_t i = 0; i < 402; i++)
    a.insert(i);
  cout << "Erased: " << a.erase(2) << endl;
  a.print(1);
  cout << endl << a.count(1) << endl;
  cout << endl << a.count(2) << endl;
}
