#include "FBullCowGame.h"



FBullCowGame::FBullCowGame()
{
    Reset();
}

int FBullCowGame::GetGuessLimit() const
{
    return MyGuessLimit;
}

int FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const
{
    return false;
}

bool FBullCowGame::IsGuessValid(std::string)
{
    return false;
}

void FBullCowGame::Reset()
{

    constexpr int GUESS_LIMIT = 8;

    MyCurrentTry = 1;
    MyGuessLimit = GUESS_LIMIT;

    return;
}
