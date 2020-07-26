/* Author: Ryan McKay
 * Date: 07/24/2020
 * File Name: GameBoard.h
 * Class: CSC160-470
 * Summary: header file for game board
*/

#ifndef HANGMAN_GAMEBOARD_H
#define HANGMAN_GAMEBOARD_H

#include <string>


class GameBoard {
public:
    std::string GetBoardState(int numStrikes);

private:
    // initializing all of the board states possible:
    const std::string BOARD0 = " -------|\n"
                               " |      |\n"
                               "        |\n"
                               "        |\n"
                               "        |\n"
                               "        |\n"
                               "      -----";
    const std::string BOARD1 = " -------|\n"
                               " |      |\n"
                               " O      |\n"
                               "        |\n"
                               "        |\n"
                               "        |\n"
                               "      -----";
    const std::string BOARD2 = " -------|\n"
                               " |      |\n"
                               " O      |\n"
                               " |      |\n"
                               "        |\n"
                               "        |\n"
                               "      -----";
    const std::string BOARD3 = " -------|\n"
                               " |      |\n"
                               " O      |\n"
                               "-|      |\n"
                               "        |\n"
                               "        |\n"
                               "      -----";
    const std::string BOARD4 = " -------|\n"
                               " |      |\n"
                               " O      |\n"
                               "-|-     |\n"
                               "        |\n"
                               "        |\n"
                               "      -----";
    const std::string BOARD5 = " -------|\n"
                               " |      |\n"
                               " O      |\n"
                               "-|-     |\n"
                               "/       |\n"
                               "        |\n"
                               "      -----";
    const std::string BOARD6 = " -------|\n"
                               " |      |\n"
                               " O      |\n"
                               "-|-     |\n"
                               "/ \\     |\n"
                               "        |\n"
                               "      -----";

    std::string boardStates [7] = {BOARD0, BOARD1, BOARD2, BOARD3, BOARD4, BOARD5, BOARD6};  // create array of board states to iterate over
};


#endif //HANGMAN_GAMEBOARD_H
