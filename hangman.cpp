/*
 * Author: Ryan McKay
 * Date: 07/24/2020
 * File Name: hangman.cpp
 * Class: CSC160-470
 * Summary: loops a game of hangman, that reads words in from hangman.dat and asks you to guess letters.
 * */

#include "HangManGame.h"

int main()
{
    HangManGame hangman;  // initialize the object
    hangman.Run();  // run the game
    return 0;  // exit the program
}
