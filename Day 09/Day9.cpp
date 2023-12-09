#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int part1(string fileName);
// int part2(string fileName);

int getnextValue(vector<int> sequence);
// int getpreviousvalue(vector<int> sequence);

vector<string> split(string line, char c);

int main() {
  // int part1A = part1("test1.txt");
  //  int part2A = part2("test1.txt");

  // cout << "part 1:" << part1A << "\n";
  //  cout << "part 2:" << part2A << "\n";

  return 0;
}

int part1(string fileName) {
  ifstream oasis(fileName);
  string line;
  int total = 0;

  while (getline(oasis, line)) {
    vector<string> temp = split(line, ' ');

    vector<int> sequence = {};

    for (int i = 0; i < temp.size(); i++) {
      sequence.push_back(stoi(temp[i]));
    }

    total += getnextValue(sequence);
  }

  return total;
}

/**
int part2(string fileName) {
  ifstream oasis(fileName);
  string line;
  int total = 0;

  while (getline(oasis, line)) {
    vector<string> temp = split(line, ' ');

    vector<int> sequence = {};

    for (int i = 0; i < temp.size(); i++) {
      sequence.push_back(stoi(temp[i]));
    }

    total += getpreviousvalue(sequence);
  }

  return total;
}
*/

int getnextvalue(vector<int> sequence) {
  vector<int> difference = {};
  bool allzero = true;

  for (int i = 1; i < sequence.size(); i++) {
    difference.push_back(sequence[i] - sequence[i - 1]);
    cout << difference[i - 1] << ",";
    if (difference[i - 1] != 0) {
      allzero = false;
    }
  }

  cout << "\n";
  if (sequence.size() == 0) {
    return 0;
  }
  if (allzero == false) {
    return sequence[sequence.size() - 1] + getnextvalue(difference);
  } else {

    int value = sequence.size() - 1;
    cout << sequence[0] << "\n";
    return sequence[0];
  }
}
/*
int getpreviousvalue(vector<int> sequence) {
  vector<int> difference = {};
  bool allzero = true;

  for (int i = 1; i < sequence.size(); i++) {
    difference.push_back(sequence[i] - sequence[i - 1]);
    cout << difference[i - 1] << ",";
    if (difference[i - 1] != 0) {
      allzero = false;
    }
  }

  cout << "\n";
  if (sequence.size() == 0) {
    return 0;
  }
  if (allzero == false) {
    return sequence[sequence.size() - 1] + getnextvalue(difference);
  } else {

    int value = sequence.size() - 1;
    cout << sequence[0] << "\n";
    return sequence[0];
  }
}
*/
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
