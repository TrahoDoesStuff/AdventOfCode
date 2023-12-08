#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int part1(string fileName);
int part2(string fileName);

vector<string> split(string line, char c);

int main() {}

vector<string> split(string line, char c) {
  vector<string> splitValues;

  string currentSection = "";

  for (int i = 0; i < line.length(); i++) {
    if (line[i] == c) {
      if (currentSection.length() > 0) {
        splitValues.push_back(currentSection);
        currentSection = "";
      }
    } else {
      currentSection += line[i];
    }
  }

  if (currentSection.length() > 0) {
    splitValues.push_back(currentSection);
  }

  return splitValues;
}
