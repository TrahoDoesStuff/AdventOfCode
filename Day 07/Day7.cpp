
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int part1(string fileName);
int part2(string fileName);

class cardSort;
class cardInfo;

vector<string> split(string line, char c);
cardSort getCardValue(string cards);
cardSort getCardValue2(string cards);
bool compareCardSets(cardSort card1, cardSort card2);



int main(){
    //cout << "part 1:" << part1("tests/puzzleInput.txt") << "\n";
    
    cout << "part 2:" << part2("tests/test2.txt") << "\n";
}

class cardSort{
    public:
    string card;
    public:
    int type;
    public:
    int bet;
    public:
    vector<int> cardScores;

    public:
    void calculateCardScores(){
        for(int i = 0; i < 5; i++){
            cardScores.push_back(getCardValue(i));

        }

        return;
    }

    void calculateCardScores2(){
       for(int i = 0; i < 5; i++){
        cardScores.push_back(getCardValue2(i));
       } 

        return;
    }
    
    int getCardValue(int cardIndex){
        char values[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3','2'};
        char c = card[cardIndex];

        for(int i = 0; i < 13; i++){
            if(c == values[i]){
                return ( 13 - i);
            }
        }

        return -1;
    }

    int getCardValue2(int cardIndex){

        char values[13] = {'A', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3','2', 'K'};
        char c = card[cardIndex];

        for(int i = 0; i < 13; i++){
            if(c == values[i]){
                return ( 13 - i);
            }
        }

        return -1;
    }
};


class cardInfo{
    public:
    vector<char> accumChars;
    vector<int> accumNums;
    int type;


    public:
    void parseString(string str){
        for(char c : str){
            addCard(c);
        }

    }

    void addCard(char c){
        int index = findCharInCharVector(c); 
        if(index != -1){

            accumNums[index] = accumNums[index] + 1;
            return;
        }

        accumChars.push_back(c);
        accumNums.push_back(1);

        return;

    }

    int findCharInCharVector(char c){
        for(int i = 0; i < accumChars.size(); i++ ){
            if(c == accumChars[i]){
                return i;
            }
        }

        return -1;
    }

    public:
    int getType(){
        if(accumChars.size() == 1){
            // Five of a kind
            return 7;
        }

        if(accumChars.size() == 2){
            if(accumNums[0] == 1 || accumNums[1] == 1){
                // Four of a kind
                return 6;
            }
            
            // Full house
            return 5;
        }

        if(accumChars.size() == 3){
            if(accumNums[0] == 3 || accumNums[1] == 3 || accumNums[2] == 3){
                // Three of a kind
                return 4;
            }

            if(accumNums[0] == 1 || accumNums[1] == 1 || accumNums[2] == 1){
                // Two pair
                return 3;
            }

            
        }

        if(accumChars.size() == 4){
            // One pair
            return 2;
        }

        // High card
        return 1;
    }

    int getTypeJ(){
        if(!containsJoker()){
            return getType();
        }

        int jokerNum = jokerCount();
        if(jokerNum == 5){
            return 7;
        }

        if(jokerNum == 4){
            return 7;
        }

        if(jokerNum == 3){
            if(accumChars.size() == 2){
                return 7;
            }

            return 6;
            
        }

        if(jokerNum == 2){
            if(accumChars.size() == 2){
                return 7;
            }

            if(accumChars.size() == 3){
                return 6;
            }

            if(accumChars.size() == 4){
                return 4;
            }
        }

        if(jokerNum == 1){
            if(accumChars.size() == 2){
                return 7;
            }
            if(accumChars.size() == 3){
                return 5;
            }
            if(accumChars.size() == 4){
                return 4;
            }
            if(accumChars.size() == 5){
                return 2;
            }
        }


        return 0;
    }


    bool containsJoker(){
        for(int i = 0; i < 5; i++){
            if(accumChars[i] == 'J') return true;
        }
        cout << "nod joker" << "\n";
        return false;
    }

    int jokerCount(){
        for(int i= 0; i < 5; i++){
            if(accumChars[i] == 'J') cout << "found j" << "\n"; return accumNums[i];
        }

        return 0;
    }
};

int part1(string fileName){
    vector<cardSort> cardsToSort = {};

    string line;
    ifstream cardFile(fileName);

    while(getline(cardFile, line)){
        string cards = split(line, ' ')[0];
        int bet = stoi(split(line, ' ')[1]);

        cardSort temp = getCardValue(cards);
        temp.bet = bet;

        cardsToSort.push_back(temp);
        

    }

    cardFile.close();

    cout << cardsToSort.size() << "\n";

    //Sort vector    
    sort( cardsToSort.begin( ), cardsToSort.end( ), [ ]( const auto& card1, const auto&  card2 )
    {
        if(card1.type != card2.type){
            return card1.type < card2.type;
        }

        int index =0;

        while(index < 5 && card1.cardScores[index] == card2.cardScores[index]){
            ++index;
        }

        return card1.cardScores[index] < card2.cardScores[index]; 


    });


    // multiply bets

    int total = 0;

    for(int i  = 0 ; i < cardsToSort.size(); i++){
        cout << cardsToSort[i].card << " " << cardsToSort[i].type << "\n";
        total += cardsToSort[i].bet * (i + 1);
    }

    return total;

    
}

int part2(string fileName){
    vector<cardSort> cardsToSort = {};

    string line;
    ifstream cardFile(fileName);

    while(getline(cardFile, line)){
        string cards = split(line, ' ')[0];
        int bet = stoi(split(line, ' ')[1]);

        cardSort temp = getCardValue2(cards);
        temp.bet = bet;

        cardsToSort.push_back(temp);
        

    }

    cardFile.close();

    cout << cardsToSort.size() << "\n";

    //Sort vector    
    sort( cardsToSort.begin( ), cardsToSort.end( ), [ ]( const auto& card1, const auto&  card2 )
    {
        if(card1.type != card2.type){
            return card1.type < card2.type;
        }

        int index =0;

        while(index < 5 && card1.cardScores[index] == card2.cardScores[index]){
            ++index;
        }

        return card1.cardScores[index] < card2.cardScores[index]; 


    });


    // multiply bets

    int total = 0;

    for(int i  = 0 ; i < cardsToSort.size(); i++){
        cout << cardsToSort[i].card << " " << cardsToSort[i].type << "\n";
        total += cardsToSort[i].bet * (i + 1);
    }

    return total;

    
}

cardSort getCardValue(string cards){
    int level;
    int score;

    cardInfo currentCard;
    currentCard.parseString(cards);
    
    cardSort cardSorted;
    cardSorted.card = cards;
    cardSorted.type = currentCard.getType();
    cout << currentCard.accumChars.size() << "," << cards << "\n";
    cardSorted.calculateCardScores();
    return cardSorted;
    
}

cardSort getCardValue2(string cards){

    int level;
    int score;

    cardInfo currentCard;
    currentCard.parseString(cards);
    
    cardSort cardSorted;
    cardSorted.card = cards;
    cardSorted.type = currentCard.getTypeJ();
    cout << currentCard.accumChars.size() << "," << cards << "\n";
    cardSorted.calculateCardScores2();

    return cardSorted;
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
