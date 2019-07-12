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
 * The board class stores the state of the board at one point in time.
 * The board used by the main function are global arrays current_board (defined in property.h) and
 * 		current_players (defined in player.h)
 * To use the data stored in a board object in the main function, you need to use the setglobal()
 * 		method to set the global arrays appropriately
 * The save() method writes the required input to initialize a new board to the current state in a file
 * 		To resume from a saved board, pass the save file as input to the program
 */
class board{
	public:
		board();
		~board();
		void setglobal();
		void save(const std::string& filename = "savefile");
	public:
		std::vector<player> players;
		square* squares[40];
};

#endif /* BOARD_H_ */
