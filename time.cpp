#include "time.h"
#include "line.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

std::ostream &operator<<(std::ostream &os, Time t) {
  if (t.hasHours() || t.m >= 60) {
    os << std::setfill('0') << std::setw(2) << t.h << ':' << std::setfill('0')
       << std::setw(2) << t.m << ':' << std::setfill('0') << std::setw(2)
       << t.s;
  } else {
    os << std::setfill('0') << std::setw(2) << t.m << ':' << std::setfill('0')
       << std::setw(2) << t.s;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Time &t) {
  char symb;
  int h = 0, m = 0, s = 0;
  std::string timeStr;

  is >> timeStr;

  std::vector<int> parts;
  std::stringstream ss(timeStr);
  std::string part;
  while (std::getline(ss, part, ':')) {
    parts.push_back(std::stoi(part));
  }

  if (parts.size() == 2) {
    m = parts[0];
    s = parts[1];
  } else if (parts.size() == 3) {
    h = parts[0];
    m = parts[1];
    s = parts[2];
  } else {
    is.setstate(std::ios::failbit);
    return is;
  }

  t.h = h;
  t.m = m;
  t.s = s;
  return is;
}

int timeToSec(Time t) { return t.h * 3600 + t.m * 60 + t.s; }

Time secToTime(int sec) {
  int h = sec / 3600;
  int m = (sec % 3600) / 60;
  int s = sec % 60;

  return Time(h, m, s);
}

Time stringToTime(std::string ss) {
  int h = (ss[0] - '0') * 10 + (ss[1] - '0');
  int m = (ss[3] - '0') * 10 + (ss[4] - '0');
  int s = (ss[6] - '0') * 10 + (ss[7] - '0');

  return Time(h, m, s);
}

bool hasHour(const std::vector<Line> &lines) {
  for (const auto &line : lines) {
    if (line.t.h != 0) {
      return true;
    }
  }
  return false;
}