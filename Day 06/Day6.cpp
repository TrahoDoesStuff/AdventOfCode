#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

int part1(string fileName);
int part2(string fileName);

vector<string> split(string line, char c);

string removeChar(string line, char c);

int main(){
    cout << "part 1:" << part1("tests/puzzleInput.txt") << "\n";
    cout << "part 2:" << part2("tests/puzzleInput.txt");
}

int part1(string fileName){
    string line;
    ifstream sheet(fileName);

    int total = 1;

    getline(sheet,line);

    line = split(line , ':')[1];
    
    vector<string> timeVector = split(line, ' ');

    getline(sheet,line);

    line = split(line, ':')[1];

    vector<string> distanceVector = split(line, ' ');

    sheet.close();

    while(!timeVector.empty()){
        int entryTime = stoi(timeVector.back());
        int entryDistance = stoi(distanceVector.back());
        int currentTotal = 0;

        for(int h = 0; h <= entryTime; h++){
            if((h*entryTime - (h * h)) > entryDistance){
                ++currentTotal;
            }
        }
        cout << currentTotal << "\n";

        total = total * currentTotal;
        timeVector.pop_back();
        distanceVector.pop_back();
    }

    return total;
}


int part2(string fileName){
    string line;
    ifstream sheet(fileName);

    int total = 0;

    getline(sheet,line);

    line = split(line , ':')[1];
    
    long long int entryTime = stoll(removeChar(line, ' '));
    cout << entryTime << "\n";

    getline(sheet,line);

    line = split(line, ':')[1];
    cout << removeChar(line, ' ') << "\n";
    long long int entryDistance = stoll(removeChar(line, ' '));
    cout << entryDistance << "\n";

    sheet.close();


    

    for(long long int h = 0; h <= entryTime; h++){
        if((h*entryTime - (h * h)) > entryDistance){
            ++total;
        }
    }


    return total;
}



vector<string> split(string line, char c){
    vector<string> splitValues;

    string currentSection = "";

    for(int i = 0; i < line.length(); i++){
        if(line[i] == c){
            if(currentSection.length() > 0){
                splitValues.push_back(currentSection);
                currentSection = "";
            }
        }
        else {
            currentSection += line[i];
        }
    }

    if(currentSection.length() > 0){
        splitValues.push_back(currentSection);
    }


    return splitValues;    


}

string removeChar(string line, char c){
    string finalString = "";
    for(int i = 0; i < line.length(); i++){
        if(line[i] == c) continue;

        finalString += line[i];
    }

    return finalString;
}