#include <cstdlib>

using namespace std;

class Student
{
public:
  Student(string name, string topic, double stuwait, double stutime, int priority) : name(name), topic(topic), waittime(stuwait), timeWithProf(stutime), priority(priority) {}
  double getWait() {return waittime;}
  double getTime() {return timeWithProf;}
  int getPriority() const {return priority;}
private:
  string name;
  string topic;
  int priority;
  double waittime;
  double timeWithProf;
};

class Office
{
public:
  Office();
  void one_minute();
  void start(double timeWP);
  bool office_busy() {return (minutes_left_student > 0);}
private:
  int minutes_left_student;
  int minutes_left_office;
};

class Average
{
public:
  Average();
  void next(Student s);
  double average_wait() const;
  double average_office() const;
  int over_time(int y);
  double average_over_time();
  int getNumber() {return number;}
private:
  int number;
  double sum_wait;
  double sum_office;
  int sum_over;
};
