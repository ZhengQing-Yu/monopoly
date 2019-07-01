/*
 * board.cpp
 *
 *  Created on: Jun. 24, 2019
 *      Author: zheng
 */

#include "board.h"

board::board() {
	// initializes a default blank board
	for(int i=0; i<40; ++i){
		squares[i] = current_board[i]->clone();
	}
	int input_int;
	std::string input_str;
	players_prompt:
	std::cout<< "Enter number of players: ";
	std::cin>> input_int;
	std::cerr<< input_int << std::endl;
	std::cin.ignore();
	for(int i=0; i<input_int; ++i){
		std::string name;
		std::cout<< "Enter name of player " << i + 1 << ": ";
		std::getline(std::cin, name);
		players.push_back(player(i, name));
	}
	newgame_prompt:
	std::cout<< "Do you wish to start a new game? (y/n)" << std::endl;
	std::cout<< "If you answer no, you can initialize the board from any position." << std::endl;
	std::getline(std::cin, input_str);
	char ans;
	std::istringstream ss(input_str);
	ss >> ans;
	std::cerr<< ans << std::endl;
	switch(ans){
		case 'y': case 'Y':
			std::cout<< "Starting a new game" << std::endl;
			return;
		case 'n': case 'N':
			break;
		default:
			std::cout<< "Please enter \'y\' or \'n\'" << std::endl;
			goto newgame_prompt;
	}
	for(int i=0; i<28; ++i){
		std::cout<< properties[i]->getname() << std::endl;
		std::cout<< '\t' << "Enter owner as a number." <<std::endl;
		std::cout<< '\t' << "i.e. enter 1 if the property is owned by player 1" <<std::endl;
		std::cout<< '\t' << "Enter 0 if the property is unowned." <<std::endl;
		std::cin>> input_int;
		if (input_int){
			players[input_int - 1].add_property(properties[i]);
		}
		dynamic_cast<property*>(squares[properties[i]->getposition()])->setowner(input_int);
		const std::type_info& type_info = typeid(* properties[i]);
		if(type_info == typeid(street)){
			house_num_prompt:
			std::cout<< '\t' << "Enter number of houses on this property." << std::endl;
			std::cout<< '\t' << "If there is a hotel, enter 5. " << std::endl;
			std::cin>> input_int;
			if(input_int < 0 || input_int > 5){
				std::cout<< '\t' << "This field expects an input between 0 and 5." << std::endl;
				goto house_num_prompt;
			}
			while(input_int > 0){
				(dynamic_cast<street*>(squares[properties[i]->getposition()]))->addhouse();
				--input_int;
			}
		}
	}
}

void board::setglobal(){
	for(int i=0; i<40; ++i){
		*current_board[i] = *squares[i];
	}
	current_players = players;
}

board::~board() {
	for(int i=0; i<40; ++i){
		delete squares[i];
	}
}
