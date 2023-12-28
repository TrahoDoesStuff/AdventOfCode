#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int part1(string fileName);
int part2(string fileName);

vector<string> split(string line, char c);
string removeChar(string line, char c);

int main() {
  cout << "part 1:" << part1("test1.txt") << "\n";
}

int part1(string fileName){
  ifstream records(fileName);
  string line;

  while(getline(records,line)){
    string springs = split(line, ' ')[0];
    string count = split(line, ' ')[1];
    vector<string> temp = split(count, ',');

    cout << springs << ","; 


    // get broken groups already present
    int brokentCount = 0;
    vector<int> exisitingBroken;

    for(int i = 0; i < springs.length(); i++){
      if(springs[i] == '#'){
        ++brokentCount;
      } else {
        if(brokentCount > 0){
          exisitingBroken.push_back(brokentCount);
        }
        brokentCount = 0;

      }

      if(brokentCount > 0){
        exisitingBroken.push_back(brokentCount);
      }
    }
    exisitingBroken.push_back(-1);

    vector<int> groupsSize;
    int EBIndex = 0;

    for(int i = 0; i < temp.size(); i++){
      if(exisitingBroken[EBIndex] == stoi(temp[i])){
        ++EBIndex;
      } 
      else{
        groupsSize.push_back(stoi(temp[i]));
      }
    }

    cout << "group num:" << groupsSize.size() << "\n";

    springs = removeChar(springs, '#');

    cout << springs << "\n";
  }


  return 0;
}

string removeChar(string line, char c){
  string newline = "";
  for(int i = 0; i < line.length(); i++){
    if(line[i] == c){continue;}
    newline += line[i];
  }

  return newline;
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
