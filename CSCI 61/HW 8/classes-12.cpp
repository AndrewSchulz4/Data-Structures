#include <iostream>
#include <queue>
#include <cstdlib>
#include <cassert>
#include "classes.h"

//student defined in the header file
//Office
Office::Office()
{
  minutes_left_office = 60;
  minutes_left_student = 0;
}
void Office::one_minute()
{
  minutes_left_student--;
}
void Office::start(double timeWP)
{
  minutes_left_student = timeWP;
}

//Average
Average::Average()
{
  number = 0;
  sum_wait = 0;
  sum_office = 0;
}
void Average::increase()
{
  number++;
}
void Average::next(Student s)
{
  sum_wait += s.getWait();
  sum_office += s.getTime();
}
double Average::average_wait() const
{
  assert(number > 0);
  return sum_wait/number;
}
double Average::average_office() const
{
  assert(number > 0);
  return sum_office/number;
}
int Average::over_time(int y)
{
  sum_over += y;
}
double Average::average_over_time()
{
  return sum_over/100;
}
