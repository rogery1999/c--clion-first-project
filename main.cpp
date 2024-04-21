#include <iostream>
#include "random/mersenne_twister.h"


static void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


template<typename T>
static T readFromConsole(std::string *retryMsg) {
    while (true) {
        T value{};
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            ignoreLine();
            std::cout << *retryMsg;
            continue;
        }
        ignoreLine();

        return value;
    }
}

static int getUserGuess(int guessNum) {
    std::cout << "Guess #" << guessNum << ": ";
    std::string retryMsg{"Invalid guess. Please enter a number: "};
    return readFromConsole<int>(&retryMsg);
}

static void startGame() {
    const int randomNum{Random::get(1, 100)};

    std::cout << "Let's play a game. I'm thinking of a number between 1 and "
                 "100. You have 7 tries to guess what it is.\n";

    int guessNum{};
    for (int i = 1; i <= 7; i++) {
        guessNum = getUserGuess(i);
        if (randomNum == guessNum) {
            std::cout << "Correct! You win!\n";
            return;
        }

        std::cout << (randomNum > guessNum ? "Your guess is too low.\n"
                                           : "Your guess is too high.\n");
    }
}


char getInputContinueWithTheGame() {
    char continueWithTheGame{};
    std::string inputMsg{"Would you like to play again (y/n)? "};
    std::string inputRetryMsg{"Invalid character entered. Please try again (y/n): "};
    bool isFirstInput{true};

    while (true) {
        std::cout << (isFirstInput ? inputMsg : inputRetryMsg);

        continueWithTheGame = readFromConsole<char>(&inputRetryMsg);

        if (isFirstInput) {
            isFirstInput = false;
        }

        if (!(continueWithTheGame == 'y' || continueWithTheGame == 'n')) {
            continue;
        }
        return continueWithTheGame;
    }
}


int main() {
    char continueWithTheGame{};
    do {
        startGame();
        continueWithTheGame = getInputContinueWithTheGame();
    } while (continueWithTheGame == 'y');

    return 0;
}