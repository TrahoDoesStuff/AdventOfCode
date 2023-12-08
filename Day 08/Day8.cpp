

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

int part1(string fileName);
long long int part2(string fileName);

vector<string> split(string line, char c);
string removeChar(string line, char c);

int main() {
  int result1 = part1("puzzleInput.txt");
  long long int result2 = part2("puzzleInput.txt");

  cout << "part 1:" << result1 << "\n";
  cout << "part 2:" << result2 << "\n";
  // cout << "part 2:" << part1("test1.txt") << "\n";dddd
}

int part1(string fileName) {

  // Open text file
  ifstream mapFile(fileName);
  string line = "";

  // First, get the instructions
  getline(mapFile, line);

  string directions = line;

  cout << line << "\n";
  getline(mapFile, line);

  // Start storing maps

  map<string, string> leftMap;
  map<string, string> rightMap;

  while (getline(mapFile, line)) {
    string key = split(line, ' ')[0];
    string temp = removeChar(line, '=');

    temp = split(temp, '(')[1];

    temp = removeChar(temp, '(');
    temp = removeChar(temp, ')');
    temp = removeChar(temp, ' ');
    string left = split(temp, ',')[0];
    string right = split(temp, ',')[1];

    leftMap[key] = left;
    rightMap[key] = right;

    cout << key << "," << leftMap[key] << "," << rightMap[key] << "\n";
  }
  int stepCount = 0;
  int directionIndex;
  string currentKey = "AAA";

  while (currentKey != "ZZZ") {
    if (directions[directionIndex] == 'L') {
      currentKey = leftMap[currentKey];
    } else {
      currentKey = rightMap[currentKey];
    }
    cout << currentKey << "\n";

    ++directionIndex;
    if (directions.size() == directionIndex) {
      directionIndex = 0;
    }

    ++stepCount;
  }

  mapFile.close();

  return stepCount;
}



long long int part2(string fileName) {

  // Open text file
  ifstream mapFile(fileName);
  string line = "";

  // First, get the instructions
  getline(mapFile, line);

  string directions = line;

  cout << line << "\n";
  getline(mapFile, line);

  // Start storing maps

  map<string, string> leftMap;
  map<string, string> rightMap;

  vector<string> pathIndexs;

  while (getline(mapFile, line)) {
    string key = split(line, ' ')[0];
    string temp = removeChar(line, '=');

    if (key[key.size() - 1] == 'A') {
      pathIndexs.push_back(key);
    }

    temp = split(temp, '(')[1];

    temp = removeChar(temp, '(');
    temp = removeChar(temp, ')');
    temp = removeChar(temp, ' ');
    string left = split(temp, ',')[0];
    string right = split(temp, ',')[1];

    leftMap[key] = left;
    rightMap[key] = right;

    cout << key << "," << leftMap[key] << "," << rightMap[key] << "\n";
  }

  vector<long int> values = {directions.length()};

  for (int i = 0; i < pathIndexs.size(); i++) {
    int stepCount = 0;
    int directionIndex = 0;
    string currentKey = pathIndexs[i];

    while (currentKey[2] != 'Z') {
      if (directions[directionIndex] == 'L') {
        currentKey = leftMap[currentKey];
      } else {
        currentKey = rightMap[currentKey];
      }
      cout << currentKey << "\n";

      ++directionIndex;
      if (directions.length() == directionIndex) {
        directionIndex = 0;
      }

      ++stepCount;
    }

    values.push_back(stepCount);
  }

  long int total = 1;

  cout << values[0] << "\n";

  for (int i = 0; i < values.size(); i++) {
    cout << values[i] << "\n";
    total = lcm(total, values[i]);
  }

  mapFile.close();

  return total;
}


string removeChar(string line, char c) {
  string newLine = "";

  for (char ci : line) {
    if (ci != c) {
      newLine += ci;
    }
  }

  return newLine;
}

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
