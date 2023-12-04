#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

int part1(string fileName);
int part2(string fileName);

vector<int> addcopy(vector<int> copyList, int index, int num);

string removeUpTo(string line, char c);
vector<string> split(string line, char c);

int main(){
    //cout << "\n Part 1:" << part1("tests/patternInput.txt");
    cout << "\n Part 2:" << part2("tests/patternInput.txt");
    
}


int part1(string fileName){
    int total = 0;

    ifstream lotteryTickets(fileName);
    string line;

    while(getline(lotteryTickets, line)){
        int ticketScore = 0;

        line = removeUpTo(line, ':');
        cout << line << "\n";

        vector<string> ticketNumbers = split(split(line, '|')[0],' ');
        vector<string> winningNumbers = split(split(line, '|')[1],' ');
        
        for(int i = 0; i < ticketNumbers.size(); i++){
            for(int z = 0; z < winningNumbers.size(); z++){
                if(ticketNumbers[i] == winningNumbers[z]){
                    ticketScore = ((ticketScore == 0) ? (1):(ticketScore * 2));
                    break;
                }

                
            }
        }

        total += ticketScore;
    }

    return total;
}


int part2(string fileName){
    int total = 0;

    ifstream lotteryTickets(fileName);
    string line;

    vector<int> copyList;
    copyList.push_back(1);
    int lineIndex = 0;

    while(getline(lotteryTickets, line)){
        int lineCopys = (lineIndex < copyList.size()) ? copyList[lineIndex] : 1;
        cout<< "line:" << lineIndex << "\n";
        cout << "card count:" << lineCopys << "\n";
        
        int copyTotal = 0;

        line = removeUpTo(line, ':');

        vector<string> ticketNumbers = split(split(line, '|')[0],' ');
        vector<string> winningNumbers = split(split(line, '|')[1],' ');
        
        for(int i = 0; i < ticketNumbers.size(); i++){
            for(int z = 0; z < winningNumbers.size(); z++){
                if(ticketNumbers[i] == winningNumbers[z]){
                    ++copyTotal;
                    break;
                }

                
            }
        }

        for(int i = lineIndex + 1; i < lineIndex + 1 + copyTotal; i++){
            copyList = addcopy(copyList, i, lineCopys);
            cout << "added:" << i << "," << lineCopys <<"\n";

        }

        lineIndex++;
    }
    
    while(!copyList.empty()){
        total += copyList.back();
        cout << "index:" << lineIndex << ", count:" << copyList.back() << "\n";
        --lineIndex;
        copyList.pop_back();
    }

    while(lineIndex > 0){
        ++total;
        --lineIndex;
    }

    return total;
}

vector<int> addcopy(vector<int> copyList, int index, int num){
     
    while(index >= copyList.size()){
        copyList.push_back(1);
    }

    copyList[index] += num;

    return copyList;
    
}

string removeUpTo(string line, char c){

    int charIndex = 0;

    while(line[charIndex] != c && charIndex < line.length()){
        charIndex++;
    }

    line.erase(0,charIndex + 1);

    return line;
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