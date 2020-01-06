//
//  Controller.cpp
//  fantastic-finale-bclam2
//
//  Created by Benjamin Lam on 12/3/19.
//

#include "Controller.hpp"

Controller::Controller() {
    board_size = 7;
    win_size = 4;
    
    IsRenderMenu = true;
    IsRenderBoard = false;
    IsRenderMessage = false;
}

void Controller::RenderMenu() {
    std::string title = "Connect N";
    std::string begin_game = "Begin game";
    
    ofDrawBitmapString(title, (ofGetWidth() - title.length() * 8) / 2, ofGetHeight() * 0.2);
    RenderSizePrompt();
    RenderNPrompt();
    ofDrawBitmapStringHighlight(begin_game, (ofGetWidth() - begin_game.length() * 8) / 2, ofGetHeight() * 0.5);
}

void Controller::ProcessMenuPress(int x, int y) {
    ProcessSizePress(x, y);
    ProcessNPress(x, y);
    ProcessBeginPress(x, y);
}

void Controller::ProcessSizePress(int x, int y) {
    int center_position = (ofGetWidth() - 5 * 8) / 2;
    int vert_position = ofGetHeight() * 0.35;
    bool x_7_range = x >= center_position - ofGetWidth() * 0.1 && x <= center_position - ofGetWidth() * 0.1 + 0.05 * ofGetWidth();
    bool x_8_range = x >= center_position && x <= center_position + 0.05 * ofGetWidth();
    bool x_9_range = x >= center_position + ofGetWidth() * 0.1 && x <= center_position + ofGetWidth() * 0.1 + 0.05 * ofGetWidth();
    bool y_range = y >= ofGetHeight() * 0.3 - ofGetHeight() * 0.03 && y <= vert_position + ofGetHeight() * 0.02;
    
    if (x_7_range && y_range) {
        board_size = 7;
    }
    
    if (x_8_range && y_range) {
        board_size = 8;
    }
    
    if (x_9_range && y_range) {
        board_size = 9;
    }
}

void Controller::ProcessNPress(int x, int y) {
    bool x_7_range = x >= ofGetWidth() / 2 - ofGetWidth() * 0.1 && x <= ofGetWidth() / 2 - ofGetWidth() * 0.1 + 0.02 * ofGetWidth();
    bool x_8_range = x >= ofGetWidth() / 2 && x <= ofGetWidth() / 2 + 0.02 * ofGetWidth();
    bool x_9_range = x >= ofGetWidth() / 2 + ofGetWidth() * 0.1 && x <= ofGetWidth() / 2 + ofGetWidth() * 0.1 + 0.02 * ofGetWidth();
    bool y_range = y >= ofGetHeight() * 0.45 - ofGetHeight() * 0.03 && y <= ofGetHeight() * 0.45 + ofGetHeight() * 0.02;
    
    if (x_7_range && y_range) {
        win_size = 4;
    }
    
    if (x_8_range && y_range) {
        win_size = 5;
    }
    
    if (x_9_range && y_range) {
        win_size = 6;
    }
}

void Controller::ProcessEndPress(int n) {
    if (n == 114) {
        board.ResetGame();
    } else if (n == 109) {
        Reset();
    }
}

void Controller::ProcessBeginPress(int x, int y) {
    bool x_range = x >= (ofGetWidth() - 80) / 2 && x <= (ofGetWidth() - 50) / 2 + ofGetWidth() * 0.07;
    bool y_range = y >= ofGetHeight() * 0.5 - ofGetHeight() * 0.03 && y <= ofGetHeight() * 0.5 + ofGetHeight() * 0.02;
    
    if (x_range && y_range) {
        IsRenderMenu = false;
        IsRenderBoard = true;
        IsRenderMessage = true;
        board = Connect4(board_size, win_size);
    }
}

void Controller::RenderSizePrompt() {
    std::string size_prompt = "Select a board size:";
    int center_position = (ofGetWidth() - 5 * 8) / 2;
    int vert_position = ofGetHeight() * 0.35;
    
    ofDrawBitmapString(size_prompt, (ofGetWidth() - size_prompt.length() * 8) / 2, ofGetHeight() * 0.3);
    
    if (board_size == 7) {
        ofDrawBitmapStringHighlight("7 x 7", center_position - ofGetWidth() * 0.1, vert_position);
    } else {
        ofDrawBitmapString("7 x 7", center_position - ofGetWidth() * 0.1, vert_position);
    }
    
    if (board_size == 8) {
        ofDrawBitmapStringHighlight("8 x 8", center_position, vert_position);
    } else {
        ofDrawBitmapString("8 x 8", center_position, vert_position);
    }
    
    if (board_size == 9) {
        ofDrawBitmapStringHighlight("9 x 9", center_position + ofGetWidth() * 0.1, vert_position);
    } else {
        ofDrawBitmapString("9 x 9", center_position + ofGetWidth() * 0.1, vert_position);
    }
}

void Controller::RenderNPrompt() {
    std::string n_prompt = "Select an N value:";
    
    ofDrawBitmapString(n_prompt, (ofGetWidth() - n_prompt.length() * 8) / 2, ofGetHeight() * 0.4);
    
    if (win_size == 4) {
        ofDrawBitmapStringHighlight("4", ofGetWidth() / 2 - ofGetWidth() * 0.1, ofGetHeight() * 0.45);
    } else {
        ofDrawBitmapString("4", ofGetWidth() / 2 - ofGetWidth() * 0.1, ofGetHeight() * 0.45);
    }
    
    if (win_size == 5) {
        ofDrawBitmapStringHighlight("5", ofGetWidth() / 2, ofGetHeight() * 0.45);
    } else {
        ofDrawBitmapString("5", ofGetWidth() / 2, ofGetHeight() * 0.45);
    }
    
    if (win_size == 6) {
        ofDrawBitmapStringHighlight("6", ofGetWidth() / 2 + ofGetWidth() * 0.1, ofGetHeight() * 0.45);
    } else {
        ofDrawBitmapString("6", ofGetWidth() / 2 + ofGetWidth() * 0.1, ofGetHeight() * 0.45);
    }
}

void Controller::RenderBoard() {
    for (int i = board.GetSize() - 1; i >= 0; i--) {
        for (int j = 0; j < board.GetSize(); j++) {
            if (board.GetPositionType(i, j) == Chip::Red) {
                ofSetHexColor(RED_COLOR);
            } else if (board.GetPositionType(i, j) == Chip::Yellow) {
                ofSetHexColor(YELLOW_COLOR);
            } else {
                ofSetHexColor(WHITE_COLOR);
            }
            
            int radius = ofGetHeight() / (2.6 * board.GetSize());
            int x_pos = j * (ofGetWidth() / (1.1 * board.GetSize())) + ofGetWidth() * 0.11;
            int y_pos = (board.GetSize() - 1 - i) * (ofGetHeight() / (board.GetSize() * 1.1)) + ofGetHeight() * 0.07;
            
            ofDrawCircle(x_pos, y_pos, radius);
            
            if (i == board.GetSize() - 1) {
                ofSetHexColor(WHITE_COLOR);
                ofDrawBitmapString(std::to_string(j + 1), x_pos, ofGetHeight() * 0.95);
            }
        }
    }
}

void Controller::RenderMessage() {
    ofSetHexColor(WHITE_COLOR);
    ofDrawBitmapString(message, (ofGetWidth() - message.size() * 8) / 2, ofGetHeight() - 20);
}

void Controller::UpdateEval() {
    current_eval = board.EvaluateState();
}

void Controller::UpdateMessage() {
    if (current_eval == Evaluation::YellowWins) {
        message = "Yellow wins! Press 'r' to reset game. Press 'm' to return to the menu.";
    } else if (current_eval == Evaluation::RedWins) {
        message = "Red wins! Press 'r' to reset game. Press 'm' to return to the menu.";
    } else if (board.GetCurrentChip() == Chip::Yellow) {
        message = "Yellow turn";
    } else {
        message = "Red turn";
    }
}

void Controller::Reset() {
    board_size = 7;
    win_size = 4;
    
    IsRenderMenu = true;
    IsRenderBoard = false;
    IsRenderMessage = false;
}
