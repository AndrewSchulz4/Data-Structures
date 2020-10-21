/*
With two nodes there can only be two binary trees made as the root can only go right or left leaving two options.
Using recursion you can see how amny possible outcomes there are for three and four nodes. Going down the left side first
and testing possible left and right branches to leaves will result in two different trees. With this there will also be
two trees on the right side and then there will be one remaining tree that includes the root and its two children. With 4 nodes
amount of trees expands even further as each leaf will now have two more possibilities for the branch to go as well as before where the
tree may not reach a leaf but only to a branch. Each leaf will become a new tree as you use recursion through the tree, resulting in 4 new routes.
Along with this there will be two trees coming from the root and its left side child and grandchildren. This process will be repeated for the left side
There will also be 4 new trees coming from a stem off of the 3 node tree with 4 possible trees coming from the root's children.
This will result in 14 possible trees with 4 nodes.

As you make your way in any traversal, every time you go down to a node, backtract and go down the other child, and so on, will be a new possible path for the
possible routes for n nodes. This is the simplified answer because my previous one layed out the exact strps I took to come to this conclusuin.
*/

#include <iostream>
#include "bintree.h"

using namespace main_savitch_10;
using namespace std;

binary_tree_node<string>* prefixtree(string value[], int& i);

int main()
{
  int i = 0;
  string value[] = {"-", "+", "1", "2", "/",  "1", "3"};
  binary_tree_node<string>* tree = prefixtree(value, i);
  cout << tree->data();
  return 0;
}

binary_tree_node<string>* prefixtree(string value[], int& i)
{
  string val = value[i];
  i++;
  if(isdigit(val[i]))
  {
    binary_tree_node<string>* opp = new binary_tree_node<string>;
    opp->set_data(val);
    return opp;
  }
  else
  {
    binary_tree_node<string>* opp = new binary_tree_node<string>;
    opp->set_data(val);
    opp->set_left(prefixtree(value, i));
    opp->set_right(prefixtree(value, i));
    return opp;
  }
}
