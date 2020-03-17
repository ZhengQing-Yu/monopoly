/*
 * player.cpp
 *
 *  Created on: Apr. 25, 2019
 *      Author: zheng qing yu
 */

#include "Player.h"
#include "board.h"

#include <ctime>

extern const int in_jail = -1;

// Constructor
Player::Player(int num, std::string name, Board* in_board): num(num), name(name), in_board(in_board){
    money = 0;
    position = 0;
    rolls_out_of_jail = 0;
    get_out_of_jail_free = false;
}


void Player::addmoney(int amount){
    money += amount;
}


void Player::addproperty(property* new_property){
    new_property->setowner(num);
    owned.insert(new_property);
}


int Player::getnum() const{
    return num;
}

std::string Player::getname() const{
    return name;
}

int Player::getmoney() const{
    return money;
}


bool Player::own(property* property){
    return owned.find(property) != owned.end();
}

void Player::buy(property* property){
    property->setowner(num);
    money -= property->getprice();
    owned.insert(property);
}

void Player::mortgage(property* property){
    property->ismortgaged = true;
    money += property->getmortgagevalue();
}

void Player::taketurn(){
    char response;
    if(position != in_jail){
        goto roll;
    }
    if(get_out_of_jail_free){
        std::cout<< "Do you want to use your get out of jail free? ";
        std::cin>> response;
        if (!std::cin){
            std::cerr<< "Invalid input given player::taketurn()" <<std::endl;
            return;
        }
        if(response == 'y' || response == 'Y'){
            get_out_of_jail_free = false;
            position = 10;
            goto roll;
        }
    }
    goto try_rolling_double;
    roll:
        rolls_out_of_jail = 0;
        roll();
        return;
    try_rolling_double:
        if (rand() % 6 == rand() % 6){
            position = 10;
            goto roll;
        } else{
            ++rolls_out_of_jail;
            if(rolls_out_of_jail == 3){
                goto pay;
            }
        }
    pay:
        money -= 50;
        position = 10;
        goto roll;
}

void Player::roll(){
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


void Player::advance(int distance){
    if (distance == in_jail){
        position = in_jail;
    }
    position += distance;
    // pass go
    if (position >= 40){
        ++money;
        position %= 40;
    }
    switch(position){
    case 4:
        // income tax
        money -= 200;
        return;
    case 30:
        // go to jail
        position = in_jail;
        return;
    case 38:
        // luxury tax
        money -= 75;
        return;
    case 2: case 17: case 33:
        //community chest
        break;
    case 7: case 22: case 36:
        //chance
        break;
    case 12: case 28:
        //utility
    {
        utility* current = static_cast<utility*>(in_board->board[position]);
        int utilities_owned = 0, i = 0;
        while (i < 2){
            if (in_board->players[current->getowner() - 1].own(utilities[i]) && !utilities[i]->ismortgaged){
                utilities_owned++;
            }
            ++i;
        }
        if (utilities_owned == 0){
            return;
        } else if (utilities_owned == 1){
            money -= 4 * distance;
            in_board->players[current->getowner() - 1].addmoney(4 * distance) ;
        } else if (utilities_owned == 2){
            money -= 10 * distance;
            in_board->players[current->getowner() - 1].addmoney(10 * distance) ;
        }
        return;
    }
    default:
        property* current = static_cast<property*>(in_board->board[position]);
        if (!current->ismortgaged){
            money -= current->getrent();
            in_board->players[current->getowner() - 1].addmoney(current->getrent());
        }
        return;
    }
}

