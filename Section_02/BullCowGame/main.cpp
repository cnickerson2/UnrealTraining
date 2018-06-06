/*
    This is the console executable that makes use of the BullCow class
    This acts as the view in a MVC pattern, and is responsible for all user
    interaction. For gameLogic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include <locale>

#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void GetGuess(FText&);
bool CheckValidityOfGuess(FText&);
void PrintBullCowCount(FBullCowCount&);
bool IsPlayAgain();
bool AskToPlayAgain(FText&);
void PrintGameSummary();

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
    // Introduce the Game
    std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
    std::cout << std::endl;

}

void PrintGameSummary()
{
    if(BCGame.IsGameWon())
    {
        std::cout << "Congratulations! You guess it correctly! ";
    }
    else
    {
        std::cout << "Better luck next time. ";
    }
}

void PlayGame()
{
    BCGame.Reset();

    for (int32 i = 0; i < BCGame.GetGuessLimit() && !BCGame.IsGameWon(); ++i)
    {

        FText Guess = "";
        GetGuess(Guess);

        // Submit a valid guess to the game
        FBullCowCount BullCowCount = std::move(BCGame.SubmitValidGuess(Guess));
        // Print number of Bulls and Cows
        PrintBullCowCount(BullCowCount);
        std::cout << std::endl;

    }

    PrintGameSummary();
}

void GetGuess(FText& Guess) // Dereference Guess
{
    do 
    {
        std::cout << "Try #" << BCGame.GetCurrentTry() << "/" << BCGame.GetGuessLimit() << ". ";
        // Get a Guess from the Player
        std::cout << "Please enter your guess: ";
        std::getline(std::cin, Guess);
    } 
    while (!CheckValidityOfGuess(Guess)); // While not a valid guess

    

}

bool CheckValidityOfGuess(FText& Guess)
{
    EGuessStatus Status = BCGame.IsGuessValid(Guess);

    switch (Status)
    {
    case EGuessStatus::Wrong_Length:
        std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
        std::cout << std::endl;
        return false;
    case EGuessStatus::Not_Isogram:
        std::cout << "Please enter a word without repeating letters." << std::endl;
        std::cout << std::endl;
        return false;
    case EGuessStatus::Not_Lowercase:
        std::cout << "Please enter all lowercase characters." << std::endl;
        std::cout << std::endl;
        return false;
    default:
        return true;
    }
}

void PrintBullCowCount(FBullCowCount& BullCowCount)
{
    std::cout << "Bulls: " << BullCowCount.Bulls << ". Cows: " << BullCowCount.Cows << std::endl;
}

bool IsPlayAgain()
{
    FText Response = "";
    bool isPlayAgain = AskToPlayAgain(Response); 

    if(isPlayAgain) // add a new line if they're playing again
    {
        std::cout << std::endl;
    }

    return isPlayAgain;
}

bool AskToPlayAgain(FText& Response)
{
    std::cout << "Do you want to play again with the same word? (Y or N): ";

    std::getline(std::cin, Response);

    return tolower(Response[0]) == 'y' ? true : tolower(Response[0]) == 'n' ? false : AskToPlayAgain(Response);
}