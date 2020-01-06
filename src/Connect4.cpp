//
//  Connect4.cpp
//  fantastic-finale-bclam2
//
//  Created by Benjamin Lam on 11/24/19.
//

#include "Connect4.hpp"
#include <vector>
#include <string>

/*
6 .......
5 .......
4 .......
3 .......
2 .......
1 .......
0 .......
 */

Connect4::Connect4() {
    size = 7;
    win_size = 4;
    
    for (int i = 0; i < size; i++) {
        std::string row(size, '.');
        game_state.push_back(row);
    }
    
    current_chip = GetStartingChip();
    is_menu = true;
}

Connect4::Connect4(int board_size, int game_win_size) {
    size = board_size;
    win_size = game_win_size;
    
    for (int i = 0; i < size; i++) {
        std::string row(size, '.');
        game_state.push_back(row);
    }
    
    current_chip = GetStartingChip();
    is_menu = true;
}

Connect4::Connect4(int board_size, int game_win_size, std::string init_state) {
    size = board_size;
    win_size = game_win_size;
    
    for (int i = size - 1; i >= 0; i--) {
        std::string row = init_state.substr(i * size, size);
        
        game_state.push_back(row);
    }
    
    current_chip = GetStartingChip();
    is_menu = true;
}

/*
 Evaluation
 */

Evaluation Connect4::EvaluateState() {
    Evaluation turn_result = EvaluateBlocks(GetAllBlocks());
    
    if (IsReachable(turn_result)) {
        return turn_result;
    }
    
    return Evaluation::UnreachableState;
}

Evaluation Connect4::EvaluateBlocks(std::vector<std::string> blocks) {
    Evaluation turn_result = Evaluation::NoWinner;
    
    for (const std::string block : blocks) {
        Evaluation result = EvaluateWin(block);
        
        if (HasUnreachableWins(result, turn_result)) {
            turn_result = Evaluation::UnreachableState;
            break;
        } else if (result != Evaluation::NoWinner) {
            turn_result = result;
        }
    }
    
    return turn_result;
}

std::vector<std::string> Connect4::GetAllBlocks() {
    std::vector<std::string> all_blocks;
    std::vector<std::string> horizontal_blocks = GetHorizontalBlocks();
    std::vector<std::string> vertical_blocks = GetVerticalBlocks();
    std::vector<std::string> diagonal_blocks = GetDiagonalBlocks();

    all_blocks.insert(all_blocks.end(), horizontal_blocks.begin(), horizontal_blocks.end());
    all_blocks.insert(all_blocks.end(), vertical_blocks.begin(), vertical_blocks.end());
    all_blocks.insert(all_blocks.end(), diagonal_blocks.begin(), diagonal_blocks.end());

    return all_blocks;
}

std::vector<std::string> Connect4::GetHorizontalBlocks() {
    std::vector<std::string> blocks;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= size - win_size; j++) {
            blocks.push_back(game_state[i].substr(j, win_size));
        }
    }
    
    return blocks;
}

std::vector<std::string> Connect4::GetVerticalBlocks() {
    std::vector<std::string> blocks;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= size - win_size; j++) {
            std::string block;
            
            for (int k = 0; k < win_size; k++) {
                block += game_state[k + j][i];
            }
            
            blocks.push_back(block);
        }
    }
    
    return blocks;
}

std::vector<std::string> Connect4::GetDiagonalBlocks() {
    std::vector<std::string> blocks;
    
    for (int i = 0; i <= size - win_size; i++) {
        for (int j = 0; j <= size - win_size; j++) {
            std::string left_right_diagonal;
            std::string right_left_diagonal;
            
            for (int k = 0; k < win_size; k++) {
                left_right_diagonal += game_state[i + k][j + k];
                right_left_diagonal += game_state[i + k][size - (j + k + 1)];
            }
            
            blocks.push_back(left_right_diagonal);
            blocks.push_back(right_left_diagonal);
        }
    }
    
    return blocks;
}

Evaluation Connect4::EvaluateWin(std::string block) {
    std::string red_win(win_size, 'o');
    std::string yellow_win(win_size, 'x');
    
    if (block == red_win) {
        return Evaluation::RedWins;
    } else if (block == yellow_win) {
        return Evaluation::YellowWins;
    } else {
        return Evaluation::NoWinner;
    }
}

int Connect4::GetNumYellow() {
    int num_yellow = 0;
    
    for (int i = 0; i < size; i++) {
        for (char c : game_state[i]) {
            if (c == 'x') {
                num_yellow++;
            }
        }
    }
    
    return num_yellow;
}

int Connect4::GetNumRed() {
    int num_red = 0;
    
    for (int i = 0; i < size; i++) {
        for (char c : game_state[i]) {
            if (c == 'o') {
                num_red++;
            }
        }
    }
    
    return num_red;
}

bool Connect4::HasUnreachableWins(Evaluation result, Evaluation turn_result) {
    return (result == Evaluation::RedWins && turn_result == Evaluation::YellowWins)
    || (result == Evaluation::RedWins && turn_result == Evaluation::YellowWins);
}

bool Connect4::IsReachable(Evaluation result) {
    int num_yellow = GetNumYellow();
    int num_red = GetNumRed();
    
    if (result == Evaluation::YellowWins) {
        return num_yellow == num_red + 1;
    } else if (result == Evaluation::RedWins) {
        return num_yellow == num_red;
    }
    
    return (num_yellow == num_red || num_yellow == num_red + 1) && CheckFloating();
}

bool Connect4::CheckFloating() {
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (HasChip(i, j) && !HasChip(i - 1, j)) {
                return false;
            }
        }
    }
    
    return true;
}

/*
 Front end interaction
 */

bool Connect4::AddChip(int column, Chip chip) {
    for (int i = 0; i < size; i++) {
        if (!HasChip(i, column)) {
            SetChip(i, column, chip);
            return true;
        }
    }
    
    return false;
}

void Connect4::ProcessKeyPress(int key) {
    ProcessMoves(key);
    ProcessReset(key);
}

void Connect4::ProcessMoves(int key) {
    if (key >= 49 && key < 49 + size) {
        if (AddChip(key - 49, current_chip)) {
            SwapChip();
        }
    }
}

void Connect4::ProcessReset(int key) {
    if (key == 114) {
        ResetGame();
    }
}

Chip Connect4::GetPositionType(int row, int column) {
    if (game_state[row][column] == 'x') {
        return Chip::Yellow;
    } else if (game_state[row][column] == 'o') {
        return Chip::Red;
    } else {
        return Chip::Empty;
    }
}

std::string Connect4::DisplayBoard() {
    std::string board_string;
    
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < size; j++) {
            board_string += game_state[i][j];
        }
    }
    
    return board_string;
}

Chip Connect4::GetCurrentChip() {
    return current_chip;
}

void Connect4::ResetGame() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            game_state[i][j] = '.';
        }
    }
    
    current_chip = GetStartingChip();
}

bool Connect4::IsMenu() {
    return is_menu;
}

int Connect4::GetSize() {
    return size;
}

/*
 Helper methods
 */

void Connect4::SwapChip() {
    if (current_chip == Chip::Yellow) {
        current_chip = Chip::Red;
    } else {
        current_chip = Chip::Yellow;
    }
}

Chip Connect4::GetStartingChip() {
    int num_yellow = GetNumYellow();
    int num_red = GetNumRed();
    
    if (num_yellow == num_red + 1) {
        return Chip::Red;
    }
    
    return Chip::Yellow;
}

void Connect4::SetChip(int row, int column, Chip chip) {
    if (chip == Chip::Yellow) {
        game_state[row][column] = 'x';
    } else {
        game_state[row][column] = 'o';
    }
}

bool Connect4::HasChip(int row, int column) {
    return game_state[row][column] == 'x' || game_state[row][column] == 'o';
}
