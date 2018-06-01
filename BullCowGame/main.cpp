#include <iostream>
#include <string>
#include <locale>

#include "FBullCowGame.h"


void PrintIntro();
void PlayGame();
void GetGuess(std::string& Guess);
void PrintGuess(std::string& Guess);
bool IsPlayAgain();
bool AskToPlayAgain(std::string& Response);

//Global Variables
FBullCowGame BCGame; // Instantiate the Class FBullCowGame


//Entry point for the application
int main()
{
    do 
    {
        PrintIntro();
        PlayGame();
    } 
    while (IsPlayAgain());
    return 0;
}


void PrintIntro()
{
    constexpr int WORD_LENGTH = 5; // Constant Expression must be evaluated at Compile Time
    // Introduce the Game
    std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
    std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of" << std::endl;
    std::cout << std::endl;

}

void PlayGame()
{
    BCGame.Reset();

    for (int i = 0; i < BCGame.GetGuessLimit(); ++i)
    {

        std::string Guess = "";
        GetGuess(Guess);
        PrintGuess(Guess);
        std::cout << std::endl;

    }
}

void GetGuess(std::string& Guess) // Dereference Guess
{
    std::cout << "Try #" << BCGame.GetCurrentTry() << ". ";
    // Get a Guess from the Player
    std::cout << "Please enter your guess: ";
    std::getline(std::cin, Guess);
}

void PrintGuess(std::string& Guess)
{
    // Repeat the guess back to them
    std::cout << "You entered: " << Guess << std::endl;
}

bool IsPlayAgain()
{
    std::string Response = "";
    bool isPlayAgain = AskToPlayAgain(Response); 

    if(isPlayAgain) // add a new line if they're playing again
    {
        std::cout << std::endl;
    }

    return isPlayAgain;
}

bool AskToPlayAgain(std::string& Response)
{
    std::cout << "Do you want to play again? (Y or N): ";

    std::getline(std::cin, Response);

    return tolower(Response[0]) == 'y' ? true : tolower(Response[0]) == 'n' ? false : AskToPlayAgain(Response);
}