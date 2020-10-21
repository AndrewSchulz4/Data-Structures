#include "graph2.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//used for comparison between words
bool compare(string& x1, string& x2);
//creates the graph and vector
void create(graph & dictionary, vector<string>& words);
//finds the paths to x from y
void find(string x, string y, graph & dictionary, vector<string>& words);

int main()
{

  graph dictionary;
  vector<string> words;
  create(dictionary, words);

  find("black", "white", dictionary, words);
  find("tears", "smile", dictionary, words);
  find("small", "giant", dictionary, words);
  find("stone", "money", dictionary, words);
  find("angel", "devil", dictionary, words);
  find("amino", "right", dictionary, words);
  find("amigo", "right", dictionary, words);

  return 0;
}

//beginning of functions
bool compare(string& x1, string& x2)
{
  int incommon = 0;
  for(int i = 0; i < 5; i++)
  {
    if(x1[i] == x2[i])
    {
      incommon++;
    }
  }
  return (incommon >= 4);
}

void create(graph& dictionary, vector<string>& words)
{
  ifstream input("knuth.txt");
  string newword;

  //adds each word as a new vertex in the form of an int
  while(input >> newword)
  {
    words.push_back(newword);
    dictionary.add_vertex();
  }

  //add edge for every word that has 4 letters in common
  for(int i = 0; i < dictionary.n(); i++)
  {
    for(int j = i; j < dictionary.n(); j++)
    {
      string first = words[i];
      string second = words[j];
      //add compare function
      if(compare(first, second))
      {
        dictionary.add_edge(i,j);
      }
    }
  }
}

void find(string x, string y, graph& dictionary, vector<string>& words)
{
  size_t firststring = 0;
  size_t secondstring = 0;


  for(size_t i = 0; i < dictionary.n(); i++)
  {
    if(x == words[i])
    {
      firststring = i;
    }
  }

  for(size_t j = 0; j < dictionary.n(); j++)
  {
    if(y == words[j])
    {
      secondstring = j;
    }
  }

  vector<int> path = dictionary.shortest_path(firststring, secondstring);
  for(auto x = path.begin(); x != path.end() ; x++)
  {
    cout << words[*x] << " ";
  }
  cout << endl;

}
