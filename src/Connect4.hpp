//
//  Connect4.hpp
//  fantastic-finale-bclam2
//
//  Created by Benjamin Lam on 11/24/19.
//

#ifndef Connect4_hpp
#define Connect4_hpp

#include <stdio.h>
#include <vector>
#include <string>

enum class Evaluation {
    NoWinner,
    YellowWins,
    RedWins,
    UnreachableState
};

enum class Chip {
    Yellow,
    Red,
    Empty
};

class Connect4 {
    
public:
    Connect4();
    Connect4(int board_size, int game_win_size);
    Connect4(int board_size, int game_win_size, std::string init_state);
    Evaluation EvaluateState();
    bool AddChip(int column, Chip chip);
    void ProcessKeyPress(int key);
    void ProcessMoves(int key);
    void ProcessReset(int key);
    Chip GetPositionType(int row, int column);
    std::string DisplayBoard();
    Chip GetCurrentChip();
    void ResetGame();
    bool IsMenu();
    int GetSize();
    
private:
    std::vector<std::string> game_state;
    Chip current_chip;
    int size;
    int win_size;
    int is_menu;
    
    Evaluation EvaluateBlocks(std::vector<std::string> blocks);
    std::vector<std::string> GetAllBlocks();
    std::vector<std::string> GetHorizontalBlocks();
    std::vector<std::string> GetVerticalBlocks();
    std::vector<std::string> GetDiagonalBlocks();
    Evaluation EvaluateWin(std::string block);
    int GetNumYellow();
    int GetNumRed();
    bool HasUnreachableWins(Evaluation result, Evaluation turn_result);
    bool IsReachable(Evaluation result);
    bool CheckFloating();
    
    Chip GetStartingChip();
    void SwapChip();
    void SetChip(int row, int column, Chip chip);
    bool HasChip(int i, int j);
};

#endif /* Connect4_hpp */
