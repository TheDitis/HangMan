/* Author: Ryan McKay
 * Date: 07/24/2020
 * File Name: HangManGame.h
 * Class: CSC160-470
 * Summary: defines class HangManGame
*/

#ifndef HANGMAN_HANGMANGAME_H
#define HANGMAN_HANGMANGAME_H

#include <vector>
#include <string>

#include "GameBoard.h"


class HangManGame
{
    public:
        HangManGame();
        void Run();
        static int AskToPlay();
        void PlayGame();
        void NewGame();
        void PlayTurn();
        int NumUniqueCharacters();
        void UpdateMaskedWord();
        bool addGuessedLetter(char letter);
        bool IsCorrect() {return (wordToGuess.find(currentGuess) != std::string::npos);};
        static bool BinarySearch(const char usedLetters[], int numItems, char letter);
        static void BubbleSort(char usedLetters[], int numItems);

    private:
        GameBoard board;
        bool quitGame = false;
        bool win = false;
        bool lose = false;
        int numCorrect = 0;
        char currentGuess{};
        int numStrikes = 0;
        std::string wordToGuess;
        std::string maskedWord;
        std::vector<char> lettersGuessed;
};


#endif //HANGMAN_HANGMANGAME_H
