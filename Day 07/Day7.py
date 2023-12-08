print("hello world") 

print ("part 1: " + part1(filename))

def part1 (filename):
    with open("file.txt") as file_in:
        lines = []


        for line in file_in:
            cards = line.split(' ')[0]
            bet = int(line.split(' ')[1])



class cardSort:
    def __init__(self):
        self.card = ""
        self.type = 0
        self.bet = 0
        self.cardScores = []

    def calculateCardScores(self):
        for i in range(5):
            self.cardScores.append(getCardValue(i))

        return
    
    def getCardValue(cardIndex){
        values = ('A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3','2')
        char c = card[cardindex]
    }
    

