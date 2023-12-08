#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

long long int part1(string fileName);
long long int part2(string fileName);

vector<string> split(string line, char c);
vector<long long int> addVectorValues(vector<long long int> vector, int index,long long int value);
long long int getValuesFromVector(vector<long long int> vector, int index);

int main(){
    cout << "part 2:" << part2("tests/puzzleInput.txt");
}

long long int part1(string fileName){
    
    string line;
    ifstream almanac(fileName);

    getline(almanac, line);
    line = split(line, ':')[1];

    vector<string> currentSeedValuesTemp = split(line, ' ');
    vector<long long int> currentSeedValues  = {};

    vector<long long int> nextMapSeedValues= {} ;

    for(string s : currentSeedValuesTemp){
        nextMapSeedValues.push_back(stoll(s));
    }

    cout << nextMapSeedValues[0] << "\n";
    while(getline(almanac, line)){
        if(line == ""){
            continue;
        }
        if(!isdigit(line[0])){
            cout << "new map:" << "\n";
            currentSeedValues = nextMapSeedValues;
            nextMapSeedValues = {};
            continue;
        }

        cout << line << "\n";
        
        vector<string> lineMappingValues = split(line,' ');
        long long int destinationRangeStart = stoll(lineMappingValues[0]);
        long long int sourceRangeStart = stoll(lineMappingValues[1]);
        long long int rangeLength =  stoll(lineMappingValues[2]);

        for(int i = 0; i < currentSeedValues.size(); i++){
            long long int difference = currentSeedValues[i] - sourceRangeStart;
            if( difference >= 0 && difference < rangeLength ){
                cout << "    difference:" << destinationRangeStart << "\n";
                cout << "   added:"  << difference + destinationRangeStart << "\n";
                nextMapSeedValues =  addVectorValues(nextMapSeedValues, i, difference + destinationRangeStart);
            } else if (getValuesFromVector(nextMapSeedValues, i) ==  -1){
                nextMapSeedValues = addVectorValues(nextMapSeedValues, i, currentSeedValues[i]);
            }
        }
        
        

    }

    // Find smallest
    long long int smallest = nextMapSeedValues[0];
    cout << "end" << "\n";
    for(long long int value : nextMapSeedValues){
        cout << value << "\n";
        if(value < smallest){
            smallest = value;
        }
    }

    return smallest;
}

long long int findDestination(string fileName, int nextValue){

    string line;
    ifstream almanac(fileName);

    getline(almanac, line);

    int currentValue;

    while(getline(almanac, line)){
        if(line == ""){
            continue;
        }
        if(!isdigit(line[0])){
            currentValue = nextValue;
            nextValue = -1;
            continue;
        }

        
        vector<string> lineMappingValues = split(line,' ');
        long long int destinationRangeStart = stoll(lineMappingValues[0]);
        long long int sourceRangeStart = stoll(lineMappingValues[1]);
        long long int rangeLength =  stoll(lineMappingValues[2]);

        long long int difference = currentValue - sourceRangeStart;
        if( difference >= 0 && difference < rangeLength ){
            nextValue = difference + destinationRangeStart;
        } else if (nextValue ==  -1){
            nextValue = currentValue;
        }

        
        

    }

    almanac.close();

    return nextValue;
}

long long int part2(string fileName){
    
    string line;
    ifstream almanac(fileName);

    int smallest;

    getline(almanac, line);
    line = split(line, ':')[1];

    vector<string> currentSeedValuesTemp = split(line, ' ');

    almanac.close();
    vector<long long int> currentSeedValues  = {};

    vector<long long int> nextMapSeedValues= {} ;
    for(int i = 0 ; i < currentSeedValuesTemp.size(); i = i + 2){
        long long int start = stoll(currentSeedValuesTemp[i]);
        long long int length = stoll(currentSeedValuesTemp[i + 1]);

        long long int index = start;
        cout << start << "," << length << "\n";
        if(i == 0){
          
            smallest = findDestination(fileName, index);


            index++;
        }
        while(index < start + length){
            
            int va = findDestination(fileName, index);

            if(va < smallest){
                smallest = va;
            }
            index++;
        }

    }


    

    return smallest;

}





vector<long long int> addVectorValues(vector<long long int> vector, int index, long long int value){
    while(index >= vector.size()){
        vector.push_back(-1);
    }

    vector[index] =  value;

    return vector;
}

long long int getValuesFromVector(vector<long long int> vector, int index){
    if(index >= vector.size()){
        return -1;
    }

    return vector[index];
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