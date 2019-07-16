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
	std::istringstream ss;
	// initializes players
	players_prompt:
	std::cout<< "Enter number of players: ";
	// with type checking for making sure input is an int
	std::cin>> input_str;
	std::cerr << "Input string: " << input_str << std::endl;
	ss.str(input_str);
	if(!(ss >> input_int) || input_int < 2 || input_int > 8){
		ss.clear();
		std::cout << "Number of players has to be between 2 and 8." << std::endl;
		goto players_prompt;
	}
	std::cerr<< "Input int: "<< input_int << std::endl;

	//std::cin>>input_int;
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
	ss.clear();
	ss.str(input_str);
	ss >> ans;
	std::cerr << ans << std::endl;
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
	// initializes properties if you want to resume from a game in progress
	for(int i=0; i<28; ++i){
		owner_prompt:
		std::cout<< properties[i]->getname() << std::endl;
		std::cout<< '\t' << "Enter owner as a number." <<std::endl;
		std::cout<< '\t' << "i.e. enter 1 if the property is owned by player 1" <<std::endl;
		std::cout<< '\t' << "Enter 0 if the property is unowned." <<std::endl;
		// with type checking for making sure input is an int
		std::cin>> input_str;
		std::cerr << "Input string: " << input_str << std::endl;
		ss.clear();
		ss.str(input_str);
		if(!(ss >> input_int)){
			ss.clear();
			std::cout << "Please enter a valid number." << std::endl;
			goto owner_prompt;
		}

		//std::cin>> input_int;
		if (input_int < 0 || input_int > players.size()){
			std::cout << "Make sure the player number is correct." << std::endl;
			goto owner_prompt;

		}
		if (input_int){
			players[input_int - 1].addproperty(properties[i]);
		}
		dynamic_cast<property*>(squares[properties[i]->getposition()])->setowner(input_int);
		const std::type_info& type_info = typeid(* properties[i]);
		if(type_info == typeid(street)){
			house_num_prompt:
			std::cout<< '\t' << "Enter number of houses on this property." << std::endl;
			std::cout<< '\t' << "If there is a hotel, enter 5. " << std::endl;
			// with type checking for making sure input is an int
			std::cin>> input_str;
			std::cerr << "Input string: " << input_str << std::endl;
			ss.clear();
			ss.str(input_str);
			if(!(ss >> input_int)){
				ss.clear();
				std::cout << "Please enter a valid number." << std::endl;
				goto house_num_prompt;
			}
			//std::cin>> input_int;
			if(input_int < 0 || input_int > 5){
				std::cout<< '\t' << "This field expects an input between 0 and 5." << std::endl;
				std::cout<< '\t' << properties[i]->getname() << std::endl;
				goto house_num_prompt;
			}
			while(input_int > 0){
				(static_cast<street*>(squares[properties[i]->getposition()]))->addhouse();
				--input_int;
			}
		}
	}
	std::cout<< "Enter the starting amount for each player" << std::endl;
	for(auto player:players){
		starting_money_prompt:
		std::cout<< '\t' << "Player" << player.getnum() << ": " << player.getname() << ' ';
		// with type checking for making sure input is an int
		std::cin>> input_str;
		std::cerr << "Input string: " << input_str << std::endl;
		ss.clear();
		ss.str(input_str);
		if(!(ss >> input_int)){
			ss.clear();
			std::cout << "Please enter a valid number." << std::endl;
			goto starting_money_prompt;
		}
		// std::cin >> input_int;
		player.addmoney(input_int - player.getmoney());
	}
}

void board::setglobal(){
	for(int i=0; i<40; ++i){
		*current_board[i] = *(squares[i]->clone());
	}
	current_players = players;
}

void board::save(const std::string& filename){
	namespace filesystem = std::filesystem;
	filesystem::path output_filename(filename);
	if(!output_filename.has_extension()){
		output_filename.replace_extension(".monopoly");
	}
	bool overwrite = 1;
	if(filesystem::exists(output_filename)){
		std::cout<< "File " << output_filename << " already exists." << std::endl;
		std::cout<< "Do you want to overwrite it? (y/n)" << std::endl;
		do{
			std::string input_str;
			std::cin >> input_str;
			std::istringstream ss(input_str);
			char c;
			ss >> c;
			switch(c){
				case 'y': case 'Y':
					overwrite = 1;
					goto end_loop;
				case 'n': case 'N':
					overwrite = 0;
					goto end_loop;
				default:
					break;
			}
		} while(1);
	} else{
		goto create_savefile;
	}
	end_loop:
	if(!overwrite){
		// try adding numbers (i) before the extension to get an unique filename
		int i = 1;
		filesystem::path new_filename;
		do{
			new_filename = output_filename;
			new_filename.replace_filename(new_filename.stem().string() + "(" +
						std::to_string(i) + ")" + new_filename.extension().string());
			++i;
		}
		while(filesystem::exists(new_filename));
		output_filename = new_filename;
	} else{
		// delete file before creating a new one
		// if the file did not exist before, nothing is done
		filesystem::remove(output_filename);
	}
	create_savefile:
	std::ofstream output_file(output_filename, std::fstream::out | std::fstream::trunc);
	output_file << players.size() << std::endl;
	for(auto player: players){
		output_file << player.getname() << std::endl;
	}
	output_file << "n" << std::endl;
	for(int i=0; i<40; ++i){
		// dynamic_cast returns null pointer if unsuccessful
		property* current = dynamic_cast<property*>(squares[i]);
		if(current){
			output_file << current->getowner() << std::endl;
			if(typeid(*squares[i]) == typeid(street)){
				output_file << static_cast<street*>(current)->gethousenum() << std::endl;
			}
		}
	}
	for(auto player: players){
		output_file << player.getmoney() << std::endl;
	}

}

board::~board() {
	for(int i=0; i<40; ++i){
		delete squares[i];
	}
}
