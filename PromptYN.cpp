/* Author: Ryan McKay
 * Date: 07/24/2020
 * File Name: myfuncts.cpp
 * Class: CSC160-470
 * Summary: definition of PromptYN function and its helper functions
*/


#include <string>
#include <cctype>
#include <algorithm>
#include "PromptYN.h"

std::string lowercase(string str)  // helper function for converting inputs to lowercase
{
    for (char & i : str)  // looping through the characters in a string
    {
        i = std::tolower(i);  // we can modify the original through i since we defined it as a reference
    }
    return str;  // output the lowercase string
}


bool isIn(std::string item, std::string arr[], int arrayLength)
{
    item = lowercase(item);  // convert input to lowercase for comparison
    for (int i = 0; i < arrayLength; ++i)  // for each item in the array
    {
        if (item == arr[i])  // if the all-lowercase version of the typed reply matches the current list item:
        {
            return true;  // return true indicating a match!
        }
    }
    return false;  // in the case that no matches were made (return never called) return false
}


int PromptYN(std::string reply)
{
    const int N_PLAY_REPLIES = 5;
    const int N_STOP_REPLIES = 7;
    std::string playReplies [N_PLAY_REPLIES] = {"yes", "yea", "sure", "ok", "y"};  // array of lowercase versions of proper play responses
    std::string stopReplies [N_STOP_REPLIES] = {"no", "nah", "quit", "stop", "terminate", "n", "q"};  // array of lowercase versions of proper stop responses

    char play = isIn(reply, playReplies, N_PLAY_REPLIES) ? 'y' : 'e';  // if reply belongs to playReplies, set play to y (for yes), else to e (for error)
    play = isIn(reply, stopReplies, N_STOP_REPLIES) ? 'n' : play;  // if reply belongs to stopReplies, reassign play to n, otherwise maintain previous assignment

//    std::cout << "myfuncts out: " << reply << " " << play << std::endl;  // for debugging purposes, output info to console

    if (play == 'y')  // if user entered something that is in playReplies:
    {
        return PLAY;  // return variable for continuation
    }
    else if (play == 'n')
    {
        return STOP;  // return variable for ending the game
    }
    else
    {
        return ERROR;  // return variable for indicating an bad input or error
    }

}
