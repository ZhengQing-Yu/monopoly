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

class board;

extern const int in_jail;

struct property_sort {
    inline bool operator() (const property* const x, const property* const y) const{
        return x->getposition() < y->getposition();
    }
};

class player {
public:
    player(int num, std::string name, board* in_board);
    void addmoney(int amount);
    void addproperty(property* new_property);
    // class functions
    int getnum() const;
    std::string getname() const;
    int getmoney() const;
    bool own(property* property);
    void buy(property* property);
    void mortgage(property* property);
    void taketurn();
    void roll();
    void advance(int distance);
private:
    int num;
    std::string name;
    int money = 1500;
    int position;
    int rolls_out_of_jail;
    bool get_out_of_jail_free;
    std::set<property*, property_sort> owned;
    board* in_board;
};

extern std::vector<player> current_players;


#endif /* PLAYER_H_ */
