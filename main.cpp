#define _POSIX_C_SOURCE 200809L
#include "line.h"
#include "time.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

void readFile(vector<Line> &allLines, string filename) {
  ifstream in(filename);
  if (in.is_open()) {
    Time t(0, 0, 0);
    string line;
    while (in >> t) {
      in.ignore();
      std::string line;
      std::getline(in, line);
      allLines.push_back(Line{t, line});
    }
  }
  in.close();
}

void generateNew(vector<Line> &v, vector<Line> &ans, Time x) {
  int move = timeToSec(v[0].t) - timeToSec(x);
  for (int i = 0; i < v.size(); ++i) {
    ans.push_back(Line{secToTime(timeToSec(v[i].t) - move), v[i].name});
  }
}

bool check(vector<Line> &a) {
  if (a[a.size() - 1].t.hasHours())
    return true;
  return false;
}

void writeFile(vector<Line> &a1, vector<Line> &a2, vector<Line> &a3) {
  std::ofstream out("out.txt");

  bool hasHours;

  if (out.is_open()) {
    for (auto i : {a1, a2, a3}) {
      out << '\n';
      hasHours = check(i);
      for (const Line &timecode : i) {
        if (hasHours) {
          out << std::setfill('0') << std::setw(2) << timecode.t.h << ':'
              << std::setfill('0') << std::setw(2) << timecode.t.m << ':'
              << std::setfill('0') << std::setw(2) << timecode.t.s << " "
              << timecode.name << std::endl;
        } else {
          out << std::setfill('0') << std::setw(2) << timecode.t.m << ':'
              << std::setfill('0') << std::setw(2) << timecode.t.s << " "
              << timecode.name << std::endl;
        }
      }
    }
  }
  out.close();
}

int main() {
  std::vector<Line> allLines;
  std::vector<Line> vkLines;
  std::vector<Line> youLines;
  readFile(allLines, "1.txt");

  Time newTime1(0, 0, 0);
  Time newTime2(0, 0, 0);
  std::cin >> newTime1 >> newTime2;
  generateNew(allLines, vkLines, newTime1);
  generateNew(allLines, youLines, newTime2);

  writeFile(allLines, vkLines, youLines);
}
