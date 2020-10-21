#include <iostream>
#include <queue>
#include <cstdlib>
#include <cmath>
#include "classes.h"
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

bool operator <(const Student& s1, const Student& s2)
{
  return s1.getPriority() < s2.getPriority();
}

void line_simulation(Average& avg, ofstream& output, int& count);
string topic();
string nombre();
void sortfile(ifstream& in, string column, string direction, int count);

int main()
{
  //keeping average in main allows for easier access when looping through 100 times
  Average avg;
  srand(time(0));
  int count = 0;

  ofstream output;
  output.open("OfficeHours.txt");

  //100 simulated days
  for(int i = 0; i < 100; i++)
  {
    line_simulation(avg, output, count);
  }
  output.close();

  ifstream in;
  in.open("OfficeHours.txt");
  string column;
  string direction;

  cout << "Sort by name or topic? " << endl;
  cin >> column;

  cout << "Sort by ascending or descending? " << endl;
  cin >> direction;

  sortfile(in, column, direction, count);
  //averages and number of students
  // cout << "The average time in the office is " << avg.average_office() << " minutes" << endl;
  // cout << "Students: " << avg.getNumber() << endl;
  // cout << "The average wait time is " << avg.average_wait() << " minutes" << endl;
  // cout << "The average time spent over their hour by the Professor: " << avg.average_over_time() << " minutes" << endl;
}

void line_simulation(Average& avg, ofstream& output, int& count)
{
  //creating the simulated office and lines
  Office Off;
  priority_queue<Student> line;
  int wait = 0;
  int over = 0;
  int time_in_office = 0;
  int priority = 0;

  //this for loop will create the line and then we can pop values after created
  for(int i = 1; i <= 60; i++)
  {
    //will create a curve, with most arrivals at the beginning and  a smaller but increasing number after half way through
    int val;

    int x = rand() % i;
    val = (x-30);

    //will give student name of Studentx where x is a number
    //small chance of repeat student visits during one time but number is so small, it is reasonable
    // could input the selected numbers into a vector and search through vector to only get students
    //who have not been in hours yet but repeat visits could be possible
    string name = nombre();
    string top = topic();

    //X^2 function will make probability at beginning and end higher
    //dividing by 900 gives a probability less than one, gtreater than 0
    double prob_at_time = pow(val, 2)/900;
    //if probability is higher than 50% add new student to line
    //can adjust probability to influence total arrivals
    if(prob_at_time > .9)
    {
      output << name << "\t" << top << endl;
      count++;
      //saying average time in office will be 5 to 30 minutes
      time_in_office = (rand() % 25 + 5);
      //priority from 1-10
      priority = (rand() % 10 + 1);
      Student stud(name, top, wait,time_in_office, priority);

      //increases wait with every new arrival but subtracts the time that has
      //passed in the simulation
      over += time_in_office;
      wait += (time_in_office);
      line.push(stud);
      avg.increase();

      //adds values to respected variables for later averaging
      avg.next(stud);
    }
    //checking if a student is being simulated in the office and if there is a student in line
    if(!Off.office_busy() && !line.empty())
    {
      Student stu = line.top();
      //starts how long the office will be busy for
      Off.start(stu.getTime());
      //pops the queue so the next student can go in next iteration of the loop
      line.pop();
    }
    //simulates one minute passing
    //takes one minute off of waiting per minute waited
    if(Off.office_busy())
      wait--;
    Off.one_minute();
  }
  avg.over_time(over);
}

//selects random topic for student to have
string topic()
{
  int top = rand() % 5 + 1;
  if (top == 1)
    return "Vectors";
  else if (top == 2)
    return "Spherical";
  else if (top == 3)
    return "Cylindrical";
  else if (top == 4)
    return "ArcLength";
  else
    return "Curvature";
}

string nombre()
{
  string names [60] = {"Wilda", "Jere", "Dannielle", "Karry", "Kym", "Whitley", "Efren", "Gladis", "Letty", "Marylyn", "Raul", "Tyree", "Jule", "Jenna", "Antwan", "Catheryn", "Rolland", "Magali", "Ossie",
                        "Tawny", "Delilah", "Sun", "Lucretia", "Eduardo", "Nicola", "Erminia", "Stasia", "Ethan", "Kerstin", "Hildegarde", "Rigoberto", "Humberto", "Rosio", "Victor", "Joye", "Virgina",
                        "Kathe", "Mac", "Avery", "Earline", "Milo", "Eleonore", "Joline", "Phyliss", "Bee", "Eldora", "Flossie", "Jocelyn", "Russell", "Kymberly", "Armando", "Phylis", "Andria", "Anglea",
                        "Frederic", "Jenell", "Apolonia", "Arron", "Christina", "Linnea"};
  int i = rand() % 59;
  return names[i];
}

void sortfile(ifstream& in, string column, string direction, int count)
{
//read in values to an ARRAY
  string namearr [count];
  string topicarr [count];

  int i = 0;

  while(!in.eof())
  {
    in >> namearr[i];
    in >> topicarr[i];
    i++;
  }

  //output new sorted array either to same file and override or create new file to output
  ofstream newout;
  newout.open("SortedOfficeHours.txt");

  if(column == "name")
  {
  //sort array through a sort fuinction
  for (int i = 0; i < count-1; i++)

  // Last i elements are already in place
  for (int j = 0; j < count-i-1; j++)
  {
      if (namearr[j] > namearr[j+1])
      {
          swap(topicarr[j], topicarr[j+1]);
          swap(namearr[j], namearr[j+1]);
      }
  }
  if(direction == "ascending")
  {
    for(int i = 0; i < count; i++)
    {
      newout << namearr[i] << "\t" << topicarr[i] << endl;
    }
  }
  else
  {
    for(int i = count - 1; i >= 0; i--)
    {
      newout << namearr[i] << "\t" << topicarr[i] << endl;
    }
  }
  }

  else
  {
  //sort array through a sort fuinction
  for (int i = 0; i < count-1; i++)

  // Last i elements are already in place
  for (int j = 0; j < count-i-1; j++)
  {
      if (topicarr[j] > topicarr[j+1])
      {
          swap(topicarr[j], topicarr[j+1]);
          swap(namearr[j], namearr[j+1]);
      }
  }
    if(direction == "ascending")
    {
      for(int i = 0; i < count; i++)
      {
        newout << topicarr[i] << "\t" << namearr[i] << endl;
      }
    }
    else
    {
      for(int i = count - 1; i >= 0; i--)
      {
        newout << topicarr[i] << "\t" << namearr[i] << endl;      }
    }
  }

}
