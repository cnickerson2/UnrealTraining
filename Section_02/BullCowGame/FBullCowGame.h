#pragma once
#include <string>

using FString = std::string;
using int32 = int;

enum EGuessStatus
{
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

class FBullCowGame
{
public:
    //Constructor
    FBullCowGame();
    //Public Methods
    int32 GetGuessLimit() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;

    bool IsGameWon() const;
    EGuessStatus IsGuessValid(const FString&) const;

    void Reset();
    // Provide a method for counting bulls and cows and increasing try number. Assumes Valid Guess
    FBullCowCount SubmitValidGuess(const FString&);


private:
    int32 MyCurrentTry;
    int32 MyGuessLimit;
    FString MyHiddenWord;
    bool b_IsGameWon;

    bool IsIsogram(const FString&) const;
    bool IsLowercase(const FString&) const;
};