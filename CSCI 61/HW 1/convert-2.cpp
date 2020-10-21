#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

string prefixToInfix(string& input);
string infixToPrefix(string& input);
int getPriority(char C);

int main()
{
  char type;
  string value;
  cout << "Will you enter an Infix(I) or a Prefix(P)?:" << endl;
  cin >> type;
  if(type == 'P' || type == 'p')
  {
    cout << "Enter your Prefix: " << endl;
    cin >> value;
    cout << "The infix is : " << prefixToInfix(value) << endl;
  }
  else if(type == 'I' || type == 'i')
  {
    cout << "Enter your Infix: " << endl;
    cin >> value;
    cout << "The Prefix is : " << infixToPrefix(value);
  }
  return 0;
}

string infixToPrefix(string& input)
{
  stack<char> s;
  reverse(input.begin(), input.end());
  string output;

  for(int i = 0; i < input.length(); i++)
  {
    if(input[i] == '(')
      input[i] = ')';
    else if(input[i] == ')')
      input[i] = '(';
  }

  for(int i = 0; i < input.length(); i++)
  {
    if(isdigit(input[i]) || isalpha(input[i]))
    {
      output += input[i];
    }
    else if(input[i] == '(')
      s.push(input[i]);
    else if(input[i] == ')')
    {
      if(input[i] != '(' && (!s.empty()))
      {
        output += s.top();
        s.pop();
      }
      if(s.top() == '(')
      {
        s.pop();
      }
    }
    else if(input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*' || input[i] == '^')
    {
      if(s.empty())
      {
        s.push(input[i]);
      }
      else
      {
        if(getPriority(input[i]) > getPriority(s.top()))
        {
          s.push(input[i]);
        }
        else if(getPriority(input[i]) == getPriority(s.top()) && input[i] == '^')
        {
          while(getPriority(input[i]) == getPriority(s.top()))
          {
            output += s.top();
            s.pop();
            s.push(input[i]);
          }
        }
        else if(getPriority(input[i]) == getPriority(s.top()))
        {
          s.push(input[i]);
        }
        else if(getPriority(input[i]) < getPriority(s.top()))
        {
          while(!s.empty() && getPriority(input[i]) < getPriority(s.top()))
          {
            output += s.top();
            s.pop();
          }
          s.push(input[i]);
        }
      }
    }
  }
  while(!s.empty())
  {
    output += s.top();
    s.pop();
  }
  reverse(output.begin(), output.end());
  return output;
}

string prefixToInfix(string& input)
{
  stack<string> s;
  string output;
  string first;
  string second;

  for(int i = (input.length() - 1); i >= 0; i--)
  {
    if(isdigit(input[i]) || isalpha(input[i]))
    {
      s.push(string(1,input[i]));
    }
    else if(input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*' || input[i] == '^')
    {
      first = s.top();
      s.pop();
      second = s.top();
      s.pop();
      s.push("(" + first + input[i] + second + ")");
    }
  }
  output = s.top();
  s.pop();
  return output;
}

int getPriority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}
