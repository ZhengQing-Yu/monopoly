/*
 * board.h
 *
 *  Created on: Jun. 24, 2019
 *      Author: zheng
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <typeinfo>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "Player.h"


/*
 * The save() method writes the required input to initialize a new board to the current state in a file
 *      To resume from a saved board, pass the save file as input to the program
 */
class Board{
    friend class Player;
    public:
        Board();
        ~Board();
        std::ostream& output(std::ostream& out) const;
        void save(const std::string& filename = "savefile");
    private:
        std::vector<Player> players;
        square* board[40];
};

std::ostream& operator<<(std::ostream& out, const Board& rhs);

#endif /* BOARD_H_ */
