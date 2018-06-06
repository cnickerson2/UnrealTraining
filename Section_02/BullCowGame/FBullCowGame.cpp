#include "FBullCowGame.h"
#include <locale>
#include <map>

#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame()
{
    Reset();
}

int32 FBullCowGame::GetGuessLimit() const
{
    return MyGuessLimit;
}

int32 FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
    return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
    return b_IsGameWon;
}

EGuessStatus FBullCowGame::IsGuessValid(const FString& guess) const
{

    // If the guess isn't an isogram, return Not_Isogram error
    if(!IsIsogram(guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    // If the guess is wrong length, return Wrong_Length error
    else if (guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    // If the guess is not lowercase, return Not_Lowercase error
    else if (!IsLowercase(guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

void FBullCowGame::Reset()
{

    constexpr int32 GUESS_LIMIT = 8;

    MyCurrentTry = 1;
    MyGuessLimit = GUESS_LIMIT;

    // TODO: Pull a random hidden word from a text file
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;

    b_IsGameWon = false;

    return;
}

// Receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(const FString& guess)
{
    
    ++MyCurrentTry;

    
    FBullCowCount BullCowCount; 

    // Loop through all letters in the Hidden Word
    for (int32 i = 0; i < GetHiddenWordLength(); ++i) // Because we receive a valid guess, we can assume that the two lengths are the same
    {
        // For each letter, compare against the Guess
        for (int32 j = 0; j < GetHiddenWordLength(); ++j)
        {
            if(MyHiddenWord[i] == guess[j])
            {
                //Right Letter, Right Place
                if(i == j)
                {
                    ++BullCowCount.Bulls;
                }
                //Right Letter, Wrong Place
                else
                {
                    ++BullCowCount.Cows;
                }
            }
        }

            
    }

    if(BullCowCount.Bulls == GetHiddenWordLength())
    {
        // You've won
        b_IsGameWon = true;
    }

    // Return the BullCowCount
    return BullCowCount; 
}

bool FBullCowGame::IsIsogram(const FString& Word) const
{
    // Treat 0 or 1 letter strings as Isograms
    if(Word.length() > 1)
    {    
        // Create a Map of key char and value bool
        TMap<char, bool> LetterSeen;
        
        for (auto letter : Word)
        {
            letter = tolower(letter);
            // Check if the letter is already in the map
            if (LetterSeen[letter])
            {
                // Not an Isogram
                return false;
            }
            else
            {
                // If not in map, Add the letter to the map
                LetterSeen[letter] = true;
            }

        }
        // No duplicate values, return true
    }
    return true;
}

bool FBullCowGame::IsLowercase(const FString& Word) const
{
    // Check if it's a null/empty string
    if(Word.length() > 0)
    {
        // check through each letter of the word
        for (auto Letter : Word)
        {
            // is this letter lower case?
            if(isupper(Letter))
            {
                return false;
            }
        }
    }
    // it is lowercase
    return true;
}
