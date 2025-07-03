#pragma once
#include "time.h"
#include <iosfwd>
#include <string>

struct Line {
  Time t;
  std::string name;
  Line(Time t, std::string name) : t(t), name(name) {}
};

std::ostream &operator<<(std::ostream &os, const Line &l);
std::istream &operator>>(std::istream &is, Line &l);