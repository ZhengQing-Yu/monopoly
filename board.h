/*
 * board.h
 *
 *  Created on: Jun. 24, 2019
 *      Author: zheng
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "player.h"
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <filesystem>


/*
 * The save() method writes the required input to initialize a new board to the current state in a file
 *      To resume from a saved board, pass the save file as input to the program
 */
class board{
    friend class player;
    public:
        board();
        ~board();
        void save(const std::string& filename = "savefile");
    private:
        std::vector<player> players;
        square* board[40];
};

#endif /* BOARD_H_ */
