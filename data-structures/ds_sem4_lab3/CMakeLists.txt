cmake_minimum_required(VERSION 3.26)
project(ds_sem4_lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ds_sem4_lab3 main.cpp
        TicTacToeField.h
        TicTacToeWinPossibilityCalculator.h)