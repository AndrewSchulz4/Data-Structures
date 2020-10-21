#include <iostream>
#include <queue>
#include <cstdlib>
#include <cmath>
#include "classes.h"
#include <map>
#include <fstream>

using namespace std;

//for priority priority_queue
bool operator <(const Student& s1, const Student& s2)
{
  return s1.getPriority() < s2.getPriority();
}

void line_simulation(Average& avg, multimap<string, string>& map);
void create_files(multimap<string, string>& map);
string topic();

int main()
{
  //keeping average in main allows for easier access when looping through 100 times
  Average avg;
  srand(time(0));
  multimap<string, string> map;
  //100 simulated days
  for(int i = 0; i < 100; i++)
  {
    line_simulation(avg, map);
  }
  create_files(map);
  //averages and number of students
  cout << "The average time in the office is " << avg.average_office() << " minutes" << endl;
  cout << "Students: " << avg.getNumber() << endl;
  cout << "The average wait time is " << avg.average_wait() << " minutes" << endl;
  cout << "The average time spent over their hour by the Professor: " << avg.average_over_time() << " minutes" << endl;
}

void line_simulation(Average& avg, multimap<string, string>& map)
{
  //creating the simulated office and lines
  Office Off;
  priority_queue<Student> line;
  int wait = 0;
  int over = -60;
  int time_in_office = 0;
  int priority = 0;

  //this for loop will create the line and then we can pop values after created
  for(int i = 1; i <= 60; i++)
  {
    //will create a curve, with most arrivals at the beginning and  a smaller but increasing number after half way through
    int val;
    if(i != 0)
    {
      int x = rand() % i;
      val = (x-30);
    }
    else if(i == 0)
      val = 1;

    //will give student name of Studentx where x is a number
    //small chance of repeat student visits during one time but number is so small, it is reasonable
    // could input the selected numbers into a vector and search through vector to only get students
    //who have not been in hours yet but repeat visits could be possible
    string name = "Student" + to_string(rand() % 60 + 1);
    string top = topic();

    //X^2 function will make probability at beginning and end higher
    //dividing by 900 gives a probability less than one, gtreater than 0
    double prob_at_time = pow(val, 2)/900;
    //if probability is higher than 50% add new student to line
    //can adjust probability to influence total arrivals
    if(prob_at_time > .8)
    {
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
      map.insert(pair<string, string> (name, top));
    }
    //checking if a student is being simulated in the office and if there is a student in line
    if(!Off.office_busy() && !line.empty())
    {
      Student stu = line.top();
      //starts how long the office will be busy for
      Off.start(stu.getTime());
      //adds values to respected variables for later averaging
      avg.next(stu);
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
    return "Vector Fields";
  else if (top == 2)
    return "Spherical Coordinates";
  else if (top == 3)
    return "Cylindrical Coordinates";
  else if (top == 4)
    return "Arc Length in Space";
  else
    return "Curvature";
}
//creates a file for each student
void create_files(multimap<string, string>& map)
{
  ofstream output;
  string name;
  bool next = false;

//For every student from the first to the last in the map
  for (auto i : map)
  {
    if(i.first != name && next == true)
    {
      //closes old file and goes through the map until new student is found
      output.close();
    }
    if(i.first != name)
    {
      //creates template for the file
      output.open(i.first);
      output << "File for: " << i.first << endl;
      output << "Came to " << map.count(i.first) << " office hours, out of 100." << endl << endl;
      output << "For: " << endl;
      name = i.first;
      next = true;
    }
    output << "\t" << i.second << endl;
  }
}
