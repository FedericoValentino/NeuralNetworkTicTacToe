cmake_minimum_required(VERSION 3.23)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 23)

add_executable(Learning main.cpp TicTacToe/TicTacToe.cpp TicTacToe/TicTacToe.h BrainLib/BrainFart.cpp BrainLib/BrainFart.h MatrixLib/MatrixLib.h MatrixLib/MatrixLib.cpp main.cpp)
