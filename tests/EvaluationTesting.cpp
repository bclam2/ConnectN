//
//  EvaluationTesting.cpp
//  fantastic-finale-bclam2 copy
//
//  Created by Benjamin Lam on 11/25/19.
//

#include <stdio.h>
#include "../src/Connect4.hpp"
#include "catch.hpp"

// No winner test cases

TEST_CASE("Default board") {
    Connect4 test_board;
    
    REQUIRE(test_board.EvaluateState() == Evaluation::NoWinner);
}

TEST_CASE("2 yellow 1 red board") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "......."
    "x....xo";
    Connect4 test_board(7, 4, board_string);
    
    REQUIRE(test_board.EvaluateState() == Evaluation::NoWinner);
}

TEST_CASE("2 yellow 2 red board") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "......."
    "o.x..ox";
    Connect4 test_board(7, 4, board_string);
    
    REQUIRE(test_board.EvaluateState() == Evaluation::NoWinner);
}

TEST_CASE("Random characters") {
    std::string board_string =
    "......."
    "......."
    "sfjilse"
    "......."
    "......."
    "......."
    "ogxsfox";
    Connect4 test_board(7, 4, board_string);
    
    REQUIRE(test_board.EvaluateState() == Evaluation::NoWinner);
}

// Unreachable state test cases

TEST_CASE("1 red") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "......."
    ".....o.";
    Connect4 test_board(7, 4, board_string);
    
    REQUIRE(test_board.EvaluateState() == Evaluation::UnreachableState);
}

TEST_CASE("Too many red") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "......."
    ".ox..o.";
    Connect4 test_board(7, 4, board_string);
    
    REQUIRE(test_board.EvaluateState() == Evaluation::UnreachableState);
}

TEST_CASE("Yellow wins, too many red") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    ".o..o.."
    "xxxxoo.";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::UnreachableState);
}

TEST_CASE("Red and yellow win row") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "oooo..."
    "xxxx..x";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::UnreachableState);
}

TEST_CASE("Red and yellow win column") {
    std::string board_string =
    "......."
    "......."
    "......."
    "xo....."
    "xo....."
    "xo....."
    "xox....";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::UnreachableState);
}

TEST_CASE("Floating chips") {
    std::string board_string =
    "......."
    "......."
    "......."
    "xo....."
    ".o....."
    "x......"
    "xox....";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::UnreachableState);
}

TEST_CASE("Floating chips bottom row") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "o......"
    "..x....";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::UnreachableState);
}

// Yellow wins test cases

TEST_CASE("Yellow win row") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "......."
    "xxxxooo";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

TEST_CASE("Yellow win column") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......x"
    "......x"
    "......x"
    ".ooo..x";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

TEST_CASE("Yellow win left to right diagonal") {
    std::string board_string =
    "......."
    "......."
    "......."
    "...x..."
    "..xo..."
    "xxox..."
    "xooo...";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

TEST_CASE("Yellow win right to left diagonal") {
    std::string board_string =
    "......."
    "......."
    "......."
    "...x..."
    "...ox.."
    "...xoxx"
    "...ooox";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

TEST_CASE("Yellow win double diagonal") {
    std::string board_string =
    "......."
    "......."
    "......."
    "...x..."
    "..xox.."
    "oxoxox."
    "xooxoox";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

TEST_CASE("Size 9 board horizontal") {
    std::string board_string =
    "........."
    "........."
    "........."
    "........."
    "........."
    "........."
    "........."
    "o........"
    "xxxx.o.o.";
    Connect4 test_board(9, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

TEST_CASE("Size 9 board vertical") {
    std::string board_string =
    "........."
    "........."
    "........."
    "........."
    "........."
    "x........"
    "xo......."
    "xo......."
    "xo.......";
    Connect4 test_board(9, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

TEST_CASE("Size 9 board diagonal") {
    std::string board_string =
    "........."
    "........."
    "........."
    "........."
    "........."
    "...x....."
    "..xo....."
    "oxxo....."
    "xoox.....";
    Connect4 test_board(9, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::YellowWins);
}

// Red wins test cases

TEST_CASE("Red win row") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......."
    "......."
    "x......"
    "xxxoooo";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::RedWins);
}

TEST_CASE("Red win column") {
    std::string board_string =
    "......."
    "......."
    "......."
    "......o"
    "....o.o"
    "xxx.x.o"
    "xxx.ooo";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::RedWins);
}

TEST_CASE("Red win left to right diagonal") {
    std::string board_string =
    "......."
    "......."
    "......."
    "...o..."
    "..ox..."
    ".oxo..."
    "oxxx...";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::RedWins);
}

TEST_CASE("Red win right to left diagonal") {
    std::string board_string =
    "......."
    "......."
    "......."
    "...o..."
    "...xo.."
    "...oxo."
    "...xxxo";
    Connect4 test_board(7, 4, board_string);
    Evaluation e = test_board.EvaluateState();
    
    REQUIRE(test_board.EvaluateState() == Evaluation::RedWins);
}

// AddChip testing

TEST_CASE("Drop Yellow") {
    std::string board_string =
    "......."
    "......."
    "......."
    "...o..."
    "...xo.."
    "...oxo."
    "...xxxo";
    Connect4 test_board(7, 4, board_string);
    test_board.AddChip(0, Chip::Yellow);
    
    std::string new_board_string =
    "......."
    "......."
    "......."
    "...o..."
    "...xo.."
    "...oxo."
    "x..xxxo";
    
    REQUIRE(test_board.DisplayBoard() == new_board_string);
}

TEST_CASE("Drop Red") {
    std::string board_string =
    "......."
    "......."
    "......."
    "....o.."
    "...xo.."
    "...oxo."
    "x..xxxo";
    Connect4 test_board(7, 4, board_string);
    test_board.AddChip(6, Chip::Red);
    
    std::string new_board_string =
    "......."
    "......."
    "......."
    "....o.."
    "...xo.."
    "...oxoo"
    "x..xxxo";
    
    REQUIRE(test_board.DisplayBoard() == new_board_string);
}
