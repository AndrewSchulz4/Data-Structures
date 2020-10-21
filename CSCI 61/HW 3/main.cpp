#include "bintree.h"
#include "bag6.h"
#include <iostream>

using namespace std;

int main(){
  main_savitch_10::bag<int> b;
  b.insert(45);
  b.insert(45);
  b.insert(20);
  b.insert(70);
  b.insert(47);
  b.insert(26);
  b.insert(45);
  //lvalue required as unary ‘&’ operand error when running line below to remove
  //cout << b.bst_remove_all(*&b.getRoot(),20);


  cout << b.count(45) << endl;
  print(b.getRoot(), 4);

}
