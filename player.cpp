/*
 * player.cpp
 *
 *  Created on: Apr. 25, 2019
 *      Author: zheng qing yu
 */

#include "player.h"


extern const int in_jail = -1;
std::vector<player> players;


void init(){
	int number_of_players;
	std::cout<< "Enter number of players: ";
	std::cin>> number_of_players;
	for(int i=0; i<number_of_players; i++){
		players.push_back(player(i + 1));
	}
}


// Constructor
player::player(int num){
	name = num;
	money = 0;
	position = 0;
	rolls_out_of_jail = 0;
	get_out_of_jail_free = false;
}


void player::add_money(int amount){
	money += amount;
}


void player::add_property(property* new_property){
	new_property->setowner(name);
	owned.insert(new_property);
}


int player::getname(){
	return name;
}


int player::getmoney(){
	return money;
}


bool player::own(property property){
	return owned.find(&property) != owned.end();
}


void player::roll(){
	int reroll = 0;
	int dice1 = (int)(((((double)std::rand()) / RAND_MAX) * 6) + 1);
	int dice2 = (int)(((((double)std::rand()) / RAND_MAX) * 6) + 1);

	do{
		dice1 = rand() % 6 + 1;
		dice2 = rand() % 6 + 1;
		//std::cout << "dice1: " << dice1 << " dice2: " << dice2 <<endl;
		if (dice1 == dice2){
			reroll++;
			//std::cout << "rolled a double" << endl;
		} else{
			reroll = 0;
		}
		if (reroll == 3){
			advance(in_jail);
			//std::cout << "goto jail" << endl;
			return;
		}
		advance(dice1 + dice2);
	}while (reroll != 0);
	//std::cout << endl;
}


void player::advance(int distance){
	if (distance == in_jail){
		position = in_jail;
	}
	position += distance;
	switch(position){
	case 4:
		// income tax
		money -= 200;
		break;
	case 30:
		// go to jail
		position = in_jail;
		break;
	case 38:
		// luxury tax
		money -= 75;
		break;
	case 2: case 17: case 33:
		//community chest
		break;
	case 7: case 22: case 36:
		//chance
		break;
	case 12:
		//electricity
		if (utilities[0]->getowner() == utilities[1]->getowner()){
			players[utilities[0]->getowner() - 1].add_money(distance * 10);
			money -= distance * 10;
		} else{
			players[utilities[0]->getowner() - 1].add_money(distance * 4);
			money -= distance * 4;
		}
		break;
	case 28:
		//water
		if (utilities[0]->getowner() == utilities[1]->getowner()){
			players[utilities[0]->getowner() - 1].add_money(distance * 10);
		} else{
			players[utilities[1]->getowner() - 1].add_money(distance * 4);
		}
		break;
	default:
		for(int i=0; i<26; i++){
			if(streets[i]->getposition() == position){
				money -= streets[i]->getrent();
				players[streets[i]->getowner() - 1].add_money(streets[i]->getrent());
				return;
			}
		}
	}
}

