#include <iostream>
#include "graph.h"

using namespace main_savitch_15;
using namespace std;

int main()
{
  graph<int> a;
  a.add_vertex(0);
  a.add_vertex(1);
  a.add_vertex(2);
  a.add_vertex(3);
  a.add_vertex(4);

  a.add_edge(0,1);
  a.add_edge(1,2);
  a.add_edge(1,3);
  a.add_edge(3,2);
  a.add_edge(3,4);
  a.add_edge(1,4);

  int length = a.longest_path(0, 0);
  cout << "There are a maximum of " << length << " edges in the graph" << endl;

  return 0;
}
