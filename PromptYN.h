/* Author: Ryan McKay
 * Date: 07/24/2020
 * File Name: myfuncts.h
 * Class: CSC160-470
 * Summary: header file for PromptYN function
*/

#ifndef HANGMAN_PROMPTYN_H
#define HANGMAN_PROMPTYN_H
#define _SCL_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

#define PLAY 1
#define STOP 0
#define ERROR -1

int PromptYN(string reply);

#endif //HANGMAN_PROMPTYN_H
