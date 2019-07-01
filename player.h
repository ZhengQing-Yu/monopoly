/*
 * player.h
 *
 *  Created on: Apr. 25, 2019
 *      Author: zheng qing yu
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "property.h"
#include <set>
#include <ctime>


extern const int in_jail;

struct property_sort {
	bool operator() (property* x, property* y){
		return x->getposition() < y->getposition();
	}
};

class player {
public:
	player(int num, std::string name);
	void add_money(int amount);
	void add_property(property* new_property);
	// class functions
	int getnum();
	std::string getname();
	int getmoney();
	bool own(property property);
	void buy(property property);
	void mortgage(property property);
	void taketurn();
	void roll();
	void advance(int distance);
private:
	int num;
	std::string name;
	int money;
	int position;
	int rolls_out_of_jail;
	bool get_out_of_jail_free;
	std::set<property*, property_sort> owned;
};

extern std::vector<player> current_players;


#endif /* PLAYER_H_ */
