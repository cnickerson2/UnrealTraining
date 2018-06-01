#pragma once
#include <string>

class FBullCowGame
{
public:
    //Constructor
    FBullCowGame();
    //Public Methods
    int GetGuessLimit() const;
    int GetCurrentTry() const;
    bool IsGameWon() const;
    bool IsGuessValid(std::string); // TODO: Make a more rich return
    void Reset(); // TODO: Make a more Rich Return Value;



private:
    int MyCurrentTry;
    int MyGuessLimit;
    
};