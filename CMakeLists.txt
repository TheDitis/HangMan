cmake_minimum_required(VERSION 3.15)
project(HangMan)

set(CMAKE_CXX_STANDARD 14)
include_directories(../)

add_executable(HangMan hangman.cpp randword.cpp randword.h PromptYN.cpp PromptYN.h GameBoard.cpp GameBoard.h HangManGame.cpp HangManGame.h)