#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int part1(string fileName);
long long int part2(string fileName);

vector<string> split(string line, char c);
string insertChar(string s,char c, int index);
int getLengths(vector<int> point, vector<string> image);
long long int getLengths1000(vector<int> point, vector<string> image, vector<int> expandRows, vector<int> expandColumns);
int main() {
  //cout << "part 1 " << part1("puzzleInput.txt") << "\n";
  cout << "part 2 " << part2("puzzleInput.txt") << "\n";
}

int part1(string fileName){
  ifstream textfile(fileName);
  string line;

  vector<string> image;
  bool noGalaxies;

  int num = 0;

  while(getline(textfile, line)){
    noGalaxies = true;

    for(int i = 0; i < line.length(); i++){
      if(line[i] == '#'){
        noGalaxies = false;
        break;
      }
    }

    if(noGalaxies){
      //adds two lines if there are no galaxiss in line
      image.push_back(line);
    }

    image.push_back(line);
    ++num;
  }

  // Check columns


  for(int x = 0; x < image[0].length(); x++){
    noGalaxies = true;
    for(int y = 0; y < image.size(); y++){
      if(image[y][x] == '#'){noGalaxies = false; break;}
    }
    cout << "\n";


    if(noGalaxies) {
      cout << "double column:" << x << "\n";
      for(int y = 0; y < image.size(); y++){
        image[y] = insertChar(image[y], '.', x);
      }   
      ++x;

    }
  }

  vector<vector<int>> galaxyPoints;

  for(int y = 0; y < image.size(); y++){
    for(int x = 0; x < image[0].length(); x++){
      if(image[y][x] == '#'){ galaxyPoints.push_back({x,y});}
    }
  }


  for(int i = 0; i < image.size(); i++){
    cout << image[i] << "\n";
  }

  int total = 0;
  
  for(int i = 0; i < galaxyPoints.size(); i++){
    vector<int> currentGalaxy = galaxyPoints[i];

    image[currentGalaxy[1]][currentGalaxy[0]] = '.';
    cout << currentGalaxy[0] << "," << currentGalaxy[1] << "\n";
    total = total +  getLengths(currentGalaxy, image);



  }

  return total;
}
long long int part2(string fileName){

  ifstream textfile(fileName);
  string line;

  vector<string> image;

  vector<int> expandRows;
  vector<int> expandColumns;

  bool noGalaxies;

  int num = 0;

  while(getline(textfile, line)){
    noGalaxies = true;

    for(int i = 0; i < line.length(); i++){
      if(line[i] == '#'){
        noGalaxies = false;
        break;
      }
    }

    if(noGalaxies){
      expandRows.push_back(num);
    }

    image.push_back(line);
    ++num;
  }

  // Check columns


  for(int x = 0; x < image[0].length(); x++){
    noGalaxies = true;
    for(int y = 0; y < image.size(); y++){
      if(image[y][x] == '#'){noGalaxies = false; break;}
    }
    cout << "\n";


    if(noGalaxies) {
      expandColumns.push_back(x);
    }
  }



  vector<vector<int>> galaxyPoints;

  for(int y = 0; y < image.size(); y++){
    for(int x = 0; x < image[0].length(); x++){
      if(image[y][x] == '#'){ galaxyPoints.push_back({x,y});}
    }
  }


  for(int i = 0; i < image.size(); i++){
    cout << image[i] << "\n";
  }

  long long int total = 0;
  
  for(int i = 0; i < galaxyPoints.size(); i++){
    vector<int> currentGalaxy = galaxyPoints[i];

    image[currentGalaxy[1]][currentGalaxy[0]] = '.';
    cout << currentGalaxy[0] << "," << currentGalaxy[1] << "\n";
    total = total +  getLengths1000(currentGalaxy, image, expandRows, expandColumns);



  }

  return total;
}

int getLengths(vector<int> point, vector<string> image){
  vector<vector<int>> points;
  points.push_back(point);

  vector<vector<int>> nextPoints;

  int total = 0;
  int steps = -1;
  while(!points.empty()){
    ++steps;
    for(int i = 0; i < points.size(); i++){

      if(points[i][0] < 0 || points[i][0] >= image[0].length() || points[i][1] < 0 || points[i][1] >= image.size() || image[points[i][1]][points[i][0]] == 'X'){
        continue;
      }

      if(image[points[i][1]][points[i][0]] == '#'){
        total += steps;
        cout << steps << "\n";
      }

      image[points[i][1]][points[i][0]] = 'X';

      nextPoints.push_back({points[i][0] + 1,points[i][1]});
      nextPoints.push_back({points[i][0] - 1,points[i][1]});
      nextPoints.push_back({points[i][0],points[i][1] + 1});
      nextPoints.push_back({points[i][0],points[i][1] - 1});


    }

    points = nextPoints;
    nextPoints = {};
  }

  return total;

}

long long int getLengths1000(vector<int> point, vector<string> image, vector<int> expandRows, vector<int> expandColumns){

  vector<vector<long long int>> points;
  points.push_back({point[0], point[1], 0});

  vector<vector<long long int>> nextPoints;

  long long int total = 0;

  int rowMove = 1;
  int columnMove =1;
  int steps = 0;
  while(!points.empty()){
    ++steps;
    for(int i = 0; i < points.size(); i++){
      rowMove = 1;
      columnMove = 1;
      if(points[i][0] < 0 || points[i][0] >= image[0].length() || points[i][1] < 0 || points[i][1] >= image.size() || image[points[i][1]][points[i][0]] == 'X'){
        continue;
      }

      if(image[points[i][1]][points[i][0]] == '#'){
        total += points[i][2];
        cout << steps << "\n";
      }

      image[points[i][1]][points[i][0]] = 'X';

      for(int z = 0; z < expandColumns.size(); z++){
        if(expandColumns[z] == points[i][0]){columnMove = 1000000;}
      }
      for(int z = 0; z < expandRows.size(); z++){
        if(expandRows[z] == points[i][1]){rowMove = 1000000;}
      }

      nextPoints.push_back({points[i][0] + 1,points[i][1],points[i][2] + columnMove});
      nextPoints.push_back({points[i][0] - 1,points[i][1], points[i][2] + columnMove});
      nextPoints.push_back({points[i][0],points[i][1] + 1, points[i][2] + rowMove});
      nextPoints.push_back({points[i][0],points[i][1] - 1, points[i][2] + rowMove});


    }

    points = nextPoints;
    nextPoints = {};
    
  }

  return total;

}

string insertChar(string s,char c, int index){
  string newString = "";

  for(int i  = 0; i < s.length(); i++){
    newString += s[i];

    if(i == index){
      newString += c;
    }
  }

  return newString;
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
