
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

int part1(string fileName);
int part2(string fileName);
bool checkAdjacentSymbol(string beforeLine,string currentLine, int startIndex, int length);
int min(int a , int b);
int max(int a , int b);



int main()
{

    cout << "\n Part 1:" << part1("tests/patternInput.txt");
    cout << "\n Part 2:" << part2("tests/patternInput.txt");


}


int part1(string fileName){
    int total = 0;
    
    string lineBefore = "";
    string line;
    ifstream textfile(fileName);
    int linenum = 0;

    while(getline(textfile,line)){
        cout<< "line:    " << linenum << "\n";
        ++linenum;

        for(int index = 0; index < line.length(); ++index){

            if(isdigit(line[index]) ) {
                int offset = 0;
                string numberString = "";


                while(isdigit(line[index + offset]) && (index + offset) < line.length()){
                    numberString += line[index + offset];
                    ++offset;
                }

                //cout << numberString << "\n";
                bool adjacentSymbol = checkAdjacentSymbol(lineBefore, line, index, offset);

                if(adjacentSymbol){
                    total += stoi(numberString);
                    cout << numberString << "\n";


                    for(int i = index; i < index + offset; i++){
                        line[i] = '.';
                     }
                }

                index += offset - 1;

                //cout << numberString << "," << (adjacentSymbol ? "true": "false" )<< "\n";

                
            }           

            else if( lineBefore != "" && line[index] != '.'){
                //cout << line[index] << "\n";
                


                // Check line above for adjacent numbers
                for(int i = max(index -1, 0); i <= min(index + 1, line.length()); i++){
                    if(i >= 0 && i < lineBefore.length()  && isdigit(lineBefore[ i ])){
                        //find the start
                        int offset = 0;

                        while(isdigit(lineBefore[i + offset])){
                            --offset;
                        }
                        ++offset;
                        string numberLine = "";
                        while(isdigit(lineBefore[i + offset])){
                            numberLine += lineBefore[i + offset];
                            lineBefore[i + offset] = '.';
                            ++offset;
                        }
                        cout << numberLine << "\n";

                        total += stoi(numberLine);
                        
                    }
                }

                //cout << "\n";

                

            }
        }


        lineBefore = line;
    }

    return total;
}


bool checkAdjacentSymbol(string beforeLine,string currentLine, int startIndex, int length){

    for(int i = max(startIndex - 1, 0) ; i <= min(startIndex + length, currentLine.length() - 1)  ; i++ ){
        
        if(!isdigit(currentLine[i]) && currentLine[i] != '.'){
            return true;
        }

        if(beforeLine != "" && !isdigit(beforeLine[i]) &&  beforeLine[i] != '.'){
            return true;
        }


    }

    return false;
}


int part2(string fileName){
    int total = 0;
    
    string lineBefore = "";
    string line;
    ifstream textfile(fileName);
    int linenum = 1;

    vector<int> currentStarsIndex;
    vector<int> currentStarsNum;
    vector<int> lastLineStarsIndex;
    vector<int> lastLineStarsNum;

    while(getline(textfile,line)){
        cout<< "\n" << "line:    " << linenum << "\n";
        ++linenum;

        int currentStarIndex = 0;
        int currentStarNum = 0;

        for(int index = 0; index < line.length(); ++index){


            if(line[index] == '*'){
                currentStarIndex = index;
                currentStarNum = 0;

                // check for values on line above
                for(int i = max(index -1, 0); i <= min(index + 1, line.length()); i++){
                    if(isdigit(lineBefore[ i ])){
                        //find the start
                        int offset = 0;

                        while(isdigit(lineBefore[i + offset])){
                            --offset;
                        }
                        ++offset;
                        string numberLine = "";
                        while(isdigit(lineBefore[i + offset])){
                            numberLine += lineBefore[i + offset];
                            lineBefore[i + offset] ='.';
                            ++offset;
                        }

                        if(currentStarNum == 0){
                            currentStarNum = stoi(numberLine);
                            cout << "possible value:" << numberLine <<"\n";
                        }
                        else if(currentStarNum != -1){
                            total += currentStarNum * stoi(numberLine);
                            cout << "possible value:" << numberLine <<"\n";
                            cout<<"value added:" << currentStarNum * stoi(numberLine) << "\n";
                            currentStarNum =  -1;
                        }
                        
                        
                    }
                }

                // same but for current line
                
                for(int i = max(index -1, 0); i <= min(index + 1, line.length()); i++){
                    if(isdigit(line[ i ])){
                        //find the start
                        int offset = 0;

                        while(isdigit(line[i + offset])){
                            --offset;
                        }
                        ++offset;
                        string numberLine = "";
                        while(isdigit(line[i + offset])){
                            numberLine += line[i + offset];
                            line[i + offset] = '.';
                            ++offset;
                        }

                        if(currentStarNum == 0){
                            currentStarNum = stoi(numberLine);

                            cout << "possible value:" << numberLine <<"\n";
                        }
                        else if(currentStarNum != -1) {
                            total += currentStarNum * stoi(numberLine);

                            cout << "possible value 2:" << numberLine <<"\n";
                            cout<<"value added:" << currentStarNum * stoi(numberLine) << "\n";
                            currentStarNum = -1;
                        }
                        
                    }

                }

                if(currentStarNum != -1){
                    cout << "star index:" << currentStarNum << "\n";

                    currentStarsIndex.push_back(currentStarIndex);
                    currentStarsNum.push_back(currentStarNum);
                }
            }


    


                
        }


        cout << "\n" << "last line completion" << "\n";
        while(!lastLineStarsIndex.empty()){
            int currentStarIndex = lastLineStarsIndex.back();
            int currentStarNum = lastLineStarsNum.back();
            cout << "current star index:" << currentStarIndex << "\n";
            
            for(int i = max(currentStarIndex-1, 0); i <= min(currentStarIndex + 1, line.length()); i++){
                if(i >= 0 && i < line.length()  && isdigit(line[ i ])){
                    cout << i << "\n";
                    //find the start
                    int offset = 0;

                    while(isdigit(line[i + offset])){
                        cout << line[i + offset] << "\n";
                        --offset;
                    }
                    ++offset;
                    string numberLine = "";
                    while(isdigit(line[i + offset])){
                        numberLine += line[i + offset];
                        line[i + offset] = '.';
                        ++offset;
                    }
                    cout << numberLine << "\n";
                    if(currentStarNum== 0){
                        currentStarNum= stoi(numberLine);
                        cout << "possible value:" << numberLine <<"\n";
                    }
                    else if(currentStarNum != -1){
                        total += currentStarNum * stoi(numberLine);
                        cout << "possible value:" << numberLine <<"\n";
                        cout<<"value added:" << currentStarNum * stoi(numberLine) << "\n";
                        currentStarNum = -1;
                    }
                    
                    
                }

            } 
             lastLineStarsIndex.pop_back();
             lastLineStarsNum.pop_back();
        }
        lineBefore = line;
        lastLineStarsIndex = currentStarsIndex;
        lastLineStarsNum = currentStarsNum;
        currentStarsIndex = {};
        currentStarsNum = {};
    }

    return total; 
}



int min(int a , int b){
    if( a < b){
        return a;
    }

    return b;
}

int max(int a, int b){
    if(a > b){
        return a;
    }

    return b;
}
