#include <iostream>
#include <queue>
#include <cstdlib>
#include <cmath>
#include "classes.h"

using namespace std;

//for priority priority_queue
bool operator <(const Student& s1, const Student& s2)
{
  return s1.getPriority() < s2.getPriority();
}

void line_simulation(Average& avg);

int main()
{
  //keeping average in main allows for easier access when looping through 100 times
  Average avg;
  srand(time(0));
  //100 simulated days
  for(int i = 0; i < 100; i++)
  {
    line_simulation(avg);
  }
  //averages and number of students
  cout << "The average time in the office is " << avg.average_office() << " minutes" << endl;
  cout << "Students: " << avg.getNumber() << endl;
  cout << "The average wait time is " << avg.average_wait() << " minutes" << endl;
  cout << "The average time spent over their hour by the Professor: " << avg.average_over_time() << " minutes" << endl;
}

void line_simulation(Average& avg)
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
    //will create a reverse bell curve, with most arrivals at the beginning and end
    int val;
    if(i != 0)
    {
      int x = rand() % i;
      val = (x-30);
    }
    else if(i == 0)
      val = 1;

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
      Student stud(wait,time_in_office, priority);
      //increases wait with every new arrival but subtracts the time that has
      //passed in the simulation
      over += time_in_office;
      wait += (time_in_office - i);
      line.push(stud);
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
    Off.one_minute();
  }
  avg.over_time(over);
}
