#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int part1(string fileName);
int part2(string fileName);


vector<string> split(string line, char c);

class pathPoint;

pathPoint processNewPoint(pathPoint currentPoint, vector<string> tunnelMap);
char getNewDirection(char tile, char direction);
int checkPointContained(int x, int y, vector<string> tunnelMap);
int checkInBetween(int rowNum, int columnStart, int columnEnd, vector<string> tunnelMap);

class pathPoint{
  public:
    int pos[2];
    char direction;
    pathPoint(int px, int py, char pdirection){
      pos[0] = px;
      pos[1] = py;

      direction = pdirection;

    }

};

class levelsPassed{
  public:
    vector<vector<int>> levelsPassed;

    bool levelBeenPassed(int level){
      for(int i = 0; i < levelsPassed.size(); i++){
        if(levelsPassed[i][0] == level){
          return true;
        }
      }

      return false;
    }


    int getLevelLastPassedXCord(int level){
      for(int i = 0; i < levelsPassed.size(); i++){
        if(levelsPassed[i][0] == level){
          return levelsPassed[i][1];
        }
      }

      return -1;
    }

    void addLevel(int level, int xCord){
      levelsPassed.push_back({level,xCord});
    }

    void removeLevel(int level){
      
      for(int i = 0; i < levelsPassed.size(); i++){
        if(levelsPassed[i][0] == level){
          levelsPassed.erase(levelsPassed.begin() + i);
        }
      }
    }
};

int main() {
  //cout << "part 1: " << part1("puzzleInput.txt") << "\n";
  cout << "part 2: " << part2("test4.txt") << "\n";
}


int part1(string fileName) {
  //read and store all lines
  vector<string> tunnelMap;


  ifstream file(fileName);
  string line;

  int SPos[2];
  int lineNum = 0;

  while(getline(file, line)){
    //cout << line << "\n";
    tunnelMap.push_back(line);

    for(int i = 0; i < line.length(); i++){
      if(line[i] == 'S'){SPos[0] = i; SPos[1] = lineNum; cout << "x:" << i << ", y:" << lineNum << "\n";}
    }

    ++lineNum;
  }


  vector<pathPoint> pathPoints;
  vector<pathPoint> nextPathPoints;


  pathPoint north(SPos[0], SPos[1], 'N');
  pathPoint east(SPos[0], SPos[1], 'E');
  pathPoint south(SPos[0], SPos[1], 'S');
  pathPoint west(SPos[0], SPos[1], 'W');

  pathPoints.push_back(north);
  pathPoints.push_back(east);
  pathPoints.push_back(south);
  pathPoints.push_back(west);

  int distance = 0;

  tunnelMap[SPos[1]][SPos[0]] = '0';

  while(!pathPoints.empty()){
    cout << "distance:" << distance << "\n";
    for(int i = 0; i < pathPoints.size(); i++){

      pathPoint temp = pathPoints[i];

      temp = processNewPoint(temp, tunnelMap);
      cout << temp.direction;
      if(temp.direction != 'X'){
        tunnelMap[temp.pos[1]][temp.pos[0]]  = 'X';
        nextPathPoints.push_back(temp);
      }


    }

    cout << "\n";
    //for(int i = 0; i < tunnelMap.size(); i++){ cout << tunnelMap[i] << "\n";}
    
    ++distance;
    pathPoints = nextPathPoints;
    nextPathPoints = {};
  }
  --distance;
  return distance;
}
int part2(string fileName) {
  //read and store all lines
  vector<string> tunnelMap;


  ifstream file(fileName);
  string line;

  int SPos[2];
  int lineNum = 0;

  while(getline(file, line)){
    //cout << line << "\n";
    tunnelMap.push_back(line);

    for(int i = 0; i < line.length(); i++){
      if(line[i] == 'S'){SPos[0] = i; SPos[1] = lineNum; cout << "x:" << i << ", y:" << lineNum << "\n";}
    }

    ++lineNum;
  }


  vector<pathPoint> pathPoints;
  vector<pathPoint> nextPathPoints;

  pathPoint north(SPos[0], SPos[1], 'N');
  pathPoint east(SPos[0], SPos[1], 'E');
  pathPoint south(SPos[0], SPos[1], 'S');
  pathPoint west(SPos[0], SPos[1], 'W');

  pathPoints.push_back(north);
  pathPoints.push_back(east);
  pathPoints.push_back(south);
  pathPoints.push_back(west);

 
  vector<vector<int>> pointsPast;

  tunnelMap[SPos[1]][SPos[0]] = 'X';

  while(!pathPoints.empty()){
    for(int i = 0; i < pathPoints.size(); i++){

      pathPoint temp = pathPoints[i];

      pointsPast.push_back({temp.pos[0], temp.pos[1]});

      pathPoint newTemp = processNewPoint(temp, tunnelMap);
      cout << temp.direction;
      if(temp.direction != 'X'){
        if(newTemp.direction == temp.direction && (temp.direction == 'E' || temp.direction == 'W')){tunnelMap[newTemp.pos[1]][newTemp.pos[0]] = 'Q';}
        else{tunnelMap[newTemp.pos[1]][newTemp.pos[0]]  = 'X';}
        nextPathPoints.push_back(newTemp);
      }


    }

    cout << "\n";
    for(int i = 0; i < tunnelMap.size(); i++){ cout << tunnelMap[i] << "\n";}
    pathPoints = nextPathPoints;
    nextPathPoints = {};
  }
  
  int total = 0;
  int held = 0;
  bool inside = false;

  for(int y = 0; y < tunnelMap.size(); y++){
    inside = false;
    held = 0;
    cout << "line " << y << "\n";
    for(int x = 0; x < tunnelMap[0].length(); x++){
      if(tunnelMap[y][x] == 'X'){
        inside = !inside;
        total += held;
        cout << held << "\n";
        held = 0;
      }
      else if(inside && tunnelMap[y][x] == '.'){
        ++held;
      }
    }

  }



  return total;
}

int checkInBetween(int rowNum, int columnStart, int columnEnd, vector<string> tunnelMap){
  int total = 0;
  
  cout << "layer:" << rowNum;

  if(columnEnd < columnStart){
    int temp = columnStart;
    columnStart = columnEnd;
    columnEnd = temp;
  }


  for(int x = columnStart; x < columnEnd; x++){
    char C = tunnelMap[rowNum][x];

    if(C == '.'){
      ++total;
      tunnelMap[rowNum][x] = 'P';
    }
  }

  cout << ",num:" << total << "\n";

  for(int i = 0; i < tunnelMap.size(); i++){cout << tunnelMap[i] << "\n";}

  return total;
}

pathPoint processNewPoint(pathPoint currentPoint, vector<string> tunnelMap){
  if(currentPoint.direction == 'N'){
    currentPoint.pos[1] -= 1;
  }

  if(currentPoint.direction == 'E'){
    currentPoint.pos[0] += 1;
  }

  if(currentPoint.direction == 'S'){
    currentPoint.pos[1] += 1;
  }

  if(currentPoint.direction == 'W'){
    currentPoint.pos[0] -= 1;
  }

  
  if(currentPoint.pos[0] < 0 || currentPoint.pos[1] >= tunnelMap[0].length() || currentPoint.pos[1] < 0 || currentPoint.pos[1] >= tunnelMap.size()){
    //outside of bounds
    currentPoint.direction = 'X';
    return currentPoint;
  }

  currentPoint.direction = getNewDirection(tunnelMap[currentPoint.pos[1]][currentPoint.pos[0]], currentPoint.direction);
  return currentPoint;
}

char getNewDirection(char tile, char direction){
  if(direction == 'N'){
    switch(tile){
      case '|':
        return 'N';
      case 'F':
        return 'E';
      case '7':
        return 'W';
      default:
        return 'X';
    }
  }

  if(direction == 'S'){
    switch(tile){
      case '|':
        return 'S';
      case 'J':
        return 'W';
      case 'L':
        return 'E';
      default:
        return 'X';
    }
  }


  if(direction == 'E'){
    switch(tile){
      case '-':
        return 'E';
      case 'J':
        return 'N';
      case '7':
        return 'S';
      default:
        return 'X';
    }
  }

  if(direction == 'W'){
    switch(tile){
      case '-':
        return 'W';
      case 'F':
        return 'S';
      case 'L':
        return 'N';
      default:
        return 'X';
    }
  }


  return 'X';
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
