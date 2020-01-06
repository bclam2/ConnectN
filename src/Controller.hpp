//
//  Controller.hpp
//  fantastic-finale-bclam2
//
//  Created by Benjamin Lam on 12/3/19.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Connect4.hpp"
#include <string>

const int BACKGROUND_COLOR = 0x0472a6;
const int BACKGROUND_SIZE = 720;
const int WHITE_COLOR = 0xffffff;
const int YELLOW_COLOR = 0xfed400;
const int RED_COLOR = 0xd42202;

class Controller {
public:
    int board_size;
    int win_size;
    bool IsRenderMenu;
    bool IsRenderBoard;
    bool IsRenderMessage;
    bool IsRenderEndMenu;
    Evaluation current_eval;
    Connect4 board;
    std::string message;
    
    Controller();
    void RenderMenu();
    void ProcessMenuPress(int x, int y);
    void ProcessSizePress(int x, int y);
    void ProcessBeginPress(int x, int y);
    void ProcessNPress(int x, int y);
    void ProcessEndPress(int n);
    void RenderSizePrompt();
    void RenderNPrompt();
    void RenderBoard();
    void RenderMessage();
    void RenderEndMenu();
    void UpdateEval();
    void UpdateMessage();
    void Reset();
};

#endif /* Controller_hpp */
