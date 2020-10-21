#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;
const int M = 250;
const int N = 250;

struct wordfound
{
  string word;
  int x1;
  int y1;
  int x2;
  int y2;
};

bool operator <(const wordfound& w1, const wordfound& w2)
{
  return (w1.word < w2.word);
}

bool search(char puzzle [M][N], int row, int column, string word, vector<wordfound>& wordsfound);

int main()
{
  //begin by putting all valid words from dictionary into a vector.
  ifstream in;
  in.open("words.txt");
  string word;
  unordered_set<string> dict;
  while(in >> word)
  {
    if(word.length() >= 6)
    {
      dict.insert(word);
    }
  }
  in.close();
  // put the lines into a std::vector
  ifstream input;
  input.open("puzzle.txt");
  string line;

  char puzzle [M][N];

  for(int i = 0; i < M; i++)
  {
    for(int j = 0; j < N; j++)
    {
      input >> puzzle[i][j];
    //  cout << puzzle[i][j] << " ";
    }
    //cout << endl;
  }

  vector<wordfound> wordsfound;

  for(int i = 0; i < M; i++)
  {
    for(int j = 0; j < N; j++)
    {
      for(unordered_set<string>::iterator word1 = dict.begin(); word1 != dict.end(); word1++)
      {
        string val = *word1;
        search(puzzle, i, j, val, wordsfound);
      }
    }
  }

  sort(wordsfound.begin(), wordsfound.end());

  for(auto i : wordsfound)
  {
    cout << i.word << " from (" << i.x1 << "," << i.y1 << ")" <<
            " to (" << i.x2 << "," << i.y2 << ")" << endl;
  }
}

bool search(char puzzle [M][N], int row, int column, string word, vector<wordfound>& wordsfound)
{
  if(puzzle[row][column] != word[0])
  {
    return false;
  }
  int length = word.length();
  // all possible directions of words appearing
  int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
  int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

  for(int direction = 0; direction < 8; direction++)
  {
    int coldir = column + y[direction];
    int rowdir = row + x[direction];
    int i;

    for (i = 1; i < length; i++)
    {
      //out of bounds
      if(coldir >= N || coldir < 0 || rowdir >= M || rowdir < 0)
      {
        break;
      }
      //check next letter
      if(puzzle[rowdir][coldir] != word[i])
      {
        break;
      }
      coldir += y[direction];
      rowdir += x[direction];
    }

    coldir -= y[direction];
    rowdir -= x[direction];
    if(i == length)
    {
      wordfound w;
      w.word = word;
      w.x1 = row;
      w.y1 = column;
      w.x2 = rowdir;
      w.y2 = coldir;
      wordsfound.push_back(w);
      cout << "found word!" << endl;
      return true;
    }
  }
  return false;
}
