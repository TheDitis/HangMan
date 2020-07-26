/* Author: Ryan McKay
 * Date: 07/24/2020
 * File Name: GameBoard.cpp
 * Class: CSC160-470
 * Summary: definition of main GameBoard method
*/


#include "GameBoard.h"

#include <string>


std::string GameBoard::GetBoardState(int numStrikes) {
    if (numStrikes < 7 && numStrikes >= 0)  // if the number passed is within the appropriate range:
    {
        return boardStates[numStrikes];  // return the string associated with the given number of strikes
    }
    else  // if numStrikes is not in index range:
    {
        return "Error: index for game board state out of range (0-6)";  // return an error message
    }
}
