#pragma once
#include <istream>
#include <ostream>

struct Time {
  int h = 0, m = 0, s = 0;
  Time(int h = 0, int m = 0, int s = 0) : h(h), m(m), s(s) {}
  bool hasHours() const { return h != 0; }
};

std::ostream &operator<<(std::ostream &, Time);
std::istream &operator>>(std::istream &, Time &);
int timeToSec(Time);
Time secToTime(int);
Time stringToTime(std::string);