#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

int part1(string fileName);
int part2(string fileName);

int main()
{
    //cout << part1("tests/puzzleInput.txt") << "\n";
    cout << part2("tests/puzzleInput.txt");

}


int part1(string fileName){
    // initialize Map for ball count
    map<string, int> ballAmount;

    ballAmount["red"] = 12;
    ballAmount["green"] = 13;
    ballAmount["blue"] = 14;
    
    int total = 0;
    
    string line;

    ifstream testcase(fileName);


    while(getline(testcase,line)){
        string section = "";
        bool valid = true;
        int id = 0;

        for(int index = 0; index < line.length(); ++index){
            section += line[index]; 
            
            

            if(line[index] == ':'){
                int numOffset = 5;
                string idString = "";
                while(numOffset + 1 < section.length()){
                    idString += section[numOffset];
                    numOffset++;
                }

                id = stoi(idString);
                cout << id << "\n";
                section = "";
            }
            
            else if(line[index] == ';' || index + 1 == line.length()){
                int offSet = 0;
                while(offSet < section.length()){
                    //process ball
                    offSet += 1;
                    string numString = "";
                    while(section[offSet] != ' '){
                        numString += section[offSet];
                        offSet++;
                    }

                    int numOfBalls = stoi(numString);

                    //Get colour name

                    offSet++;
                    string colour = "";

                    while(section[offSet] != ',' && offSet < section.length() && section[offSet] != ';'){
                        colour += section[offSet];
                        offSet++;
                        
                    }
                    
                    offSet++;

                    if(ballAmount[colour] < numOfBalls){
                        valid = false;
                        break;
                    }
                }


                section = "";
                

            }


           
        }

        if(valid){ total += id; cout << "valid" << "\n";}

    }

    return total;
}

int part2(string fileName){

    
    int total = 0;
    
    string line;

    ifstream testcase(fileName);


    while(getline(testcase,line)){
        // initialize Map for ball count
        map<string, int> ballAmount;

        ballAmount["red"] = 0;
        ballAmount["green"] = 0;
        ballAmount["blue"] = 0;


        string section = "";
        bool valid = true;
        int id = 0;

        for(int index = 0; index < line.length(); ++index){
            section += line[index]; 
            
            

            if(line[index] == ':'){
                section = "";
            }
            
            else if(line[index] == ';' || index + 1 == line.length()){
                int offSet = 0;
                while(offSet < section.length()){
                    //process ball
                    offSet += 1;
                    string numString = "";
                    while(section[offSet] != ' '){
                        numString += section[offSet];
                        offSet++;
                    }

                    int numOfBalls = stoi(numString);

                    //Get colour name

                    offSet++;
                    string colour = "";

                    while(section[offSet] != ',' && offSet < section.length() && section[offSet] != ';'){
                        colour += section[offSet];
                        offSet++;
                        
                    }
                    
                    offSet++;

                    if(ballAmount[colour] < numOfBalls){
                        ballAmount[colour] = numOfBalls;
                    }
                }


                section = "";
                

            }

           
        }

        total += ballAmount["red"] * ballAmount["green"] * ballAmount["blue"];

    }

    return total;
}