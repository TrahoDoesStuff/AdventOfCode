#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

vector<string> readFile(string fileName);
int part1(string fileName);
int part2(string fileName);
string parseWrittenNumbers(string line);


int main()
{

    cout << part1("tests/puzzleInput.txt");
    cout << part2("tests/puzzleInput.txt");


    return 0;
}


int part1(string fileName){

    
    int total = 0;
    string line;

    ifstream file(fileName);
    
    while (getline(file,line)){
        string numL;
        string numR;

        cout << line << "\n";

        // Get number on right;

        int index = 0;
        

        while(!isdigit(line[index])){
            ++index;
        }

        numL = line[index];

        // Get number on left;

        index = line.length() -1;

        while(!isdigit(line[index])){
            --index;
        }

        numR = line[index];
    
        total += stoi(numL + numR);

    }

    file.close();

    return total;



}


int part2(string fileName){
    
    int total = 0;
    string line;

    ifstream file(fileName);
    
    while (getline(file,line)){

        line = parseWrittenNumbers(line);
        string numL;
        string numR;


        // Get number on right;

        int index = 0;
        

        while(!isdigit(line[index])){
            ++index;
        }

        numL = line[index];

        // Get number on left;

        index = line.length() -1;

        while(!isdigit(line[index])){
            --index;
        }

        numR = line[index];
    
        total += stoi(numL + numR);

    }

    file.close();

    return total;
}


string parseWrittenNumbers(string line){
    string numberWords[9] = {"one","two","three","four","five","six","seven","eight","nine"};


    
    string newLine = "";
    int index = 0;

    while(index < line.length()){
        if(isdigit(line[index])){
            newLine += line[index];
        } else{
            int offSet = 0;
            string buildWord = "";
            buildWord += line[index];
            offSet++;

            while(offSet < 5 && (index + offSet) < line.length()){
                buildWord += line[index + offSet];
                for(int i = 0; i < 9; i++){
                    if(buildWord.compare(numberWords[i])== 0){
                        newLine += to_string(i + 1);
                        index += offSet  -1;
                        offSet = 6;
                        break;
                    }
                }

                ++offSet;
                
            }
        }

        index++;
        
    }


    return newLine;
}