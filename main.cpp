#define _POSIX_C_SOURCE 200809L
#include "line.h"
#include "time.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;


void readFile(std::vector<Line>& allLines, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        return;

    std::string line;
    Time t(0, 0, 0);
    bool hasTime = false;
    
    while (std::getline(in, line)) {
        if (line.empty() || line.find("•") == 0)
            continue;
        std::istringstream iss(line);
        char c1, c2;
        if (iss >> t.h >> c1 >> t.m >> c2 >> t.s) {
            if (c1 == ':' && c2 == ':') {
                size_t endIdx = line.find_first_not_of("0123456789:", 0);
                if (endIdx != std::string::npos) {
                    std::string text = line.substr(endIdx);
                    text.erase(0, text.find_first_not_of(" \t"));
                    if (!text.empty())
                        allLines.emplace_back(t, text);
                }
            }
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
  std::string names[3]{"рутуб", "ВК", "ютуб"};
  bool hasHours;
  int j = 0;

  if (out.is_open()) {
    for (auto i : {a1, a2, a3}) {
      out << names[j++] << '\n';
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
  std::cout << "Enter timings\n";
  std::cout << "Enter VK start\n";
  std::cin >> newTime1;
  std::cout << "Enter Youtube start\n";
  std::cin >> newTime2;
  generateNew(allLines, vkLines, newTime1);
  generateNew(allLines, youLines, newTime2);

  writeFile(allLines, vkLines, youLines);
}
