#include "line.h"
#include <iomanip>

std::ostream &operator<<(std::ostream &os, const Line &l) {
  return os << l.t << ' ' << l.name;
}

std::istream &operator>>(std::istream &is, Line &l) {
  char symb;
  return is >> l.t >> symb >> l.name;
}