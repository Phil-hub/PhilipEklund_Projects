
class Hangman():
    letters = []
    wrong = []
    cletters = []
    visible = []
    cnumbers = 0
    lives = 6
    solved = False
    guess = ' '

    def __init__(self):
        word = input("Enter word: ")
        print(word)
        self.letters = list(word)
        for i in self.letters:
            self.visible.append("*")

        self.loop()

    def guess(self, char):
        print(self.char)

    def loop (self):

        while self.lives > 0 and not self.solved:
            count = 0
            valid = True

            self.guess = input('Guess a character: ')

            while self.guess.__len__() > 1:

                if self.guess == "exit":
                    exit(0)

                self.guess = input('[-] Guess a character, not word: ')

            for g in self.wrong:
                if g == self.guess:
                    print("Already guessed\n")
                    valid = False
            for c in self.cletters:
                if c == self.guess:
                    print("Already guessed\n")
                    valid = False

            if valid:
                for i in self.letters:
                    if self.guess == i:
                        self.visible[count] = i
                        self.cletters.append(i)
                        self.cnumbers +=1
                    else:
                        count +=1

                if count == len(self.letters):
                    self.wrong.append(self.guess)
                    self.lives -= 1

                if self.cnumbers == len(self.letters):
                    self.solved = True

                self.printStatement()

        if self.solved:
            print("Congratulations, you won!")
        else:
            print("Game over")
        exit(0)

    def printStatement(self):
        vis = ""
        for l in self.visible:
            vis = vis + l
        gues = ""
        for l in self.wrong:
            gues = gues + l
        print("\n")
        print("Word: " + vis)
        print("Guessed Letters: " + gues)
        print("Amount of lives left: ", self.lives)
        print("\n")

play = Hangman()
