/* Author: Ryan McKay
 * Date: 07/24/2020
 * File Name: HangManGame.cpp
 * Class: CSC160-470
 * Summary: defines all methods for the HangManGame class
*/

#include "HangManGame.h"
#include "randword.h"
#include "PromptYN.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>


HangManGame::HangManGame()
{
    getWords("hangman.dat");  // load up the list of words
}

void HangManGame::Run()
{
    int errorCount = 0;  // number of consecutive poorly formatted inputs
    int playStatus;

    while (!quitGame && errorCount < 3)  // keep the game loop going as long as the game isn't supposed to quit
    {
        playStatus = AskToPlay();
        if (playStatus == PLAY)  // if the user said yes:
        {
            errorCount = 0;  // reset error count each successful playthrough
            PlayGame();  // run method to play a round
        }
        else if (playStatus == STOP)  // if the user said no:
        {
            quitGame = true;  // set quitGame to exit loop
        }
        else if (playStatus == ERROR)  // if the user input didn't make sense:
        {
            errorCount++;  // increment the error count
            if (errorCount >= 3) {
                std::cout << "Toomany unknown inputs. Goodbye!" << std::endl;
            }
            else
            {
                std::cout << "Input not recognized. Input y or n." << std::endl;  // tell the user they done messed up
            }
        }
        else  // in case none of these cases ran:
        {
            std::cout << "ERROR: playStatus not recognized. Check Run()." << std::endl;  // print error message
        }

    }
}

int HangManGame::AskToPlay()  // ask the user if they want to play, and return the gameplay interpretation of their input
{
    std::string userInput;  // initialize string variable
    std::cout << std::setw(20) << std::setfill('-') << "" << "Hangman"
              << std::setw(20) << std::setfill('-') << "" << std::endl;  // print header
    std::cout << "Do you want to play hangman? <y or n>: ";  // prompt user
    std::cin >> userInput;  // assign input to variable
    return PromptYN(userInput);  // pass variable to function that determines whether or not to play the gamee
}

void HangManGame::PlayGame()  // start the game
{
    NewGame();  // refresh the state of the game
    if (!wordToGuess.empty())  // if wordToGuess is a thing:
    {
//        std::cout << "Word: " << wordToGuess << std::endl;  // for debugging, show wordToGuess
        while (!win && !lose)  // while you haven't won or lost:
        {
            PlayTurn();  // play a turn
        }
    }
    else  // if wordToGuess isn't a thing:
    {
        std::cout << "No more words to play with. Try adding to your words file!" << std::endl;  // tell the user to add more words
        quitGame = true;  // make game exit
    }
}

void HangManGame::NewGame()  // resets the state of the game entirely
{
    // reset the state of all class attributes to their defaults:
    wordToGuess = getNextWord();
    numStrikes = 0;
    win = false;
    lose = false;
    numCorrect = 0;
    maskedWord = "";
    lettersGuessed.clear();  // clear vector

    // convert wordToGuess to lowercase
    std::for_each(  // for each item of wordToGuess
            wordToGuess.begin(),  // from beginning of the word
            wordToGuess.end(),  // to the end
            [](char& letter){letter = std::tolower(letter);}  // convert that character to lowercase
    );

    // creating blank maskedWord string:
    for (int _ : wordToGuess)  // for each letter in wordToGuess:
    {
        maskedWord += "_ ";  // add another underscore and space
    }

    std::cout << "Let's PLAY" << std::endl << std::endl;
    std::cout << maskedWord << std::endl << std::endl;  // output masked string
    std::cout << board.GetBoardState(0) << std::endl;  // print initial board state
}

void HangManGame::PlayTurn()  // go through one guess cycle
{
    std::string userInput;
    std::cout << std::setw(17) << std::setfill('<') << "" << " MAKE A GUESS "
              << std::setw(17) << std::setfill('>') << "" << std::endl;  // print turn header
    std::cout << "Guessed Letters: ";  // show the user previous guesses
    for (char i : lettersGuessed)  // print out each item in previous guessed letters separated by spaces:
        std::cout << static_cast<char>(std::toupper(i)) << "  ";
    std::cout << "\n\n";  // newline

    std::cout << "Enter a letter to guess: ";  // prompt user for guess
//    std::getline(std::cin, userInput);
    std::cin >> currentGuess;  // get letter from input
    currentGuess = std::tolower(currentGuess);  // convert letter to lowercase


    if (addGuessedLetter(currentGuess))  // add guess to list of guesses, and if it was a new guess (not in the list already):
    {
        if (IsCorrect())  // if the current guess is in the word
        {
            numCorrect++;  // increment number of correct guesses
            if (numCorrect == NumUniqueCharacters())  // if the number of correct guesses is equal to the number of unique characters:
            {
                std::cout << "You've guessed the word!! WINNER! It was " << wordToGuess << "\n\n";  // tell the user that they won
                win = true;  // set win to true so that the current game ends
                return;
            }
        }
        else
        {
            numStrikes++;  // increment strike count
            std::cout << currentGuess << " is NOT in the word to guess." << std::endl;  // let user know that they were not correct
            if (numStrikes >= 6)
            {
                std::cout << board.GetBoardState(numStrikes) << std::endl;  // print final game board
                std::cout << "Sorry you Lose :( It was: " << wordToGuess << std::endl;  // tell the user that they lost
                lose = true;
                return;
            }
        }
    }
    UpdateMaskedWord();  // make sure the masked word shows all correctly guessed letters
    std::cout << maskedWord << std::endl;  // output masked string
    std::cout << board.GetBoardState(numStrikes) << std::endl;  //  output board string
}

int HangManGame::NumUniqueCharacters()  // returns number of unique characters in wordToGuess
{
    std::string unique;  // initialize empty string for unique characters
    for (char i : wordToGuess)  // for each character in wordToGuess:
    {
        if (unique.find(i) == std::string::npos)  // if the character is not already in unique:
        {
            unique += i;  // add it to unique
        }
    }
    return unique.size();  // return length of unique
}

void HangManGame::UpdateMaskedWord()  // to add the correctly guessed characters each correct guess
{
    for (int i = 0; i < wordToGuess.size(); i++)  // for each letter of wordToGuess:
    {
        if (wordToGuess.at(i) == currentGuess)  // if the letter at the current index equals the current guess:
        {
            maskedWord.at(i * 2) = std::toupper(currentGuess);  // change the corresponding underscore in maskedWord to that letter
        }
    }
}

bool HangManGame::addGuessedLetter(char letter)  // determines whether or not the letter has already been guessed, and adds it to the list if not
{
    if (BinarySearch(lettersGuessed.data(), lettersGuessed.size(), letter))  // if the letter is found in the list of previous guesses:
    {
        return false;  // tells program not to evaluate your guess, since it already has.
    }
    else if (lettersGuessed.size() <= 26 && std::isalpha(letter))  // if it's a new guess and its in the alphabet and the number of items in lettersGuessed < length of the alphabet:
    {
        lettersGuessed.push_back(letter);  // add that letter to the list
    }
    BubbleSort(lettersGuessed.data(), lettersGuessed.size());  // sort the list of guesses so that the search will work next time around
    return true;  // tells the program that it can go ahead and evaluate your guess and score you accordingly.
}

bool HangManGame::BinarySearch(const char usedLetters[], int numItems, char letter)  // tells us if letter is in usedLetters;
{
    int left = 0;  // variable for the leftmost boundary
    int right = numItems - 1;  //  and the rightmost boundary
    while (left <= right)  // while the left variable remains on the left of right
    {
        int mid = left + (right - left) / 2;  // set the value of middle to the index in the middle of the two boundaries
        if (letter == (usedLetters[mid]))  // if the letter we're searching for is at the current search point:
        {
            return true;  // yes it was found
        }
        if (letter > (usedLetters[mid]))  // if the target is to the right of the midpoint:
        {
            left = mid + 1;  // move the leftmost boundary to just right of the previous middle
        }
        else  // if the target is to the left of the midpoint:
        {
            right = mid - 1;  // set the rightmost boundary to just left of the previous midpoint
        }
    }
    return false;
}

void HangManGame::BubbleSort(char usedLetters[], int numItems)  // sort the list of characters
{
    // initialize variables:
    bool isSorted = false;
    char swapTemp;

    while (!isSorted)  // while the list is not sorted:
    {
        isSorted = true;  // assume it's sorted until proven otherwise
        for (int i = 0; i < numItems - 1; i++)  // for each item up to one short of the end:
        {
            if (usedLetters[i] > usedLetters[i + 1])  // if the current item is greater than the item to its right:
            {
                isSorted = false;  // make sure we loop through again
                swapTemp = usedLetters[i];  // assign temp value to the current item
                usedLetters[i] = usedLetters[i + 1];  // assign the next item to the current item's place
                usedLetters[i + 1] = swapTemp;  // assign the next position to what previously was the current place
            }
        }
    }
}

