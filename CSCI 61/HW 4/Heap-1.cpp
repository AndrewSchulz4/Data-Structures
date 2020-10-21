#include <iostream>
#include "bintree.h"
#include <bits/stdc++.h>
#include <vector>

using namespace main_savitch_10;
using namespace std;

//max heap
void reheapification(binary_tree_node<int>* node, vector<int>& node_vector);
void make_tree(binary_tree_node<int>* node, vector<int>& node_vector, int &i);
void create_heap(binary_tree_node<int>* node);

int main()
{
  binary_tree_node<int> *root = new binary_tree_node<int>(5);
  root->set_left(new binary_tree_node<int>(2));
  root->set_right(new binary_tree_node<int>(6));
  root->left()->set_left(new binary_tree_node<int>(1));
  root->left()->set_right(new binary_tree_node<int>(3));
  root->right()->set_left(new binary_tree_node<int>(4));
  root->right()->set_right(new binary_tree_node<int>(7));

  print(root,0);
  //correct
  create_heap(root);
  //prints the regular tree
//  print(&a,2);
  //should print the reheapification
  print(root,0);
}

void reheapification(binary_tree_node<int>* node, vector<int>& node_vector)
{
  if(node != NULL)
  {
    reheapification(node->left(), node_vector);
    node_vector.push_back(node->data());
    reheapification(node->right(), node_vector);
  }
  else
  {
    sort(node_vector.begin(), node_vector.end(), greater<int>());
  }
}

void make_tree(binary_tree_node<int> *node, vector<int>& node_vector, int &i)
{
  if(node == nullptr) return;
  node->set_data(node_vector[i++]);
  make_tree(node->left(), node_vector, i);
  make_tree(node->right(), node_vector, i);

}

void create_heap(binary_tree_node<int>* node)
{
  vector<int> node_vector;
  int i = 0;

  reheapification(node, node_vector);
  make_tree(node, node_vector, i);
}
