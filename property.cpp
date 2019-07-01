/*
 * property.cpp
 *
 *  Created on: Apr. 25, 2019
 *      Author: zheng qing yu
 */

#include "property.h"

square::square(std::string name_init, int posn)
	: name(name_init), position(posn){}

std::string square::getname() const{
	return name;
}

int square::getposition() const{
	return position;
}


int property::getowner() const{
	return owner;
}

int property::getmortgagevalue() const{
	return mortgage;
}

int property::getprice() const{
	return price;
}

void property::setowner(int own){
	owner = own;
}

property::property(std::string name_init, int posn_init, int mortgage_init, int price_init):
	square(name_init, posn_init){
	owner = 0;
	mortgage = mortgage_init;
	price = price_init;
	ismortgaged = false;
}

int street::gethouseprice() const{
	return houseprice;
}

void street::addhouse(){
	++house;
}

int street::getrent(){
	if (!ismortgaged){
		return rent.at(house);
	} else{
		return 0;
	}
}

street::street(std::string name, int posn, int h0, int h1, int h2, int h3, int h4, int hotel,
				int mortgage, int houseprice_init, int cost_init)
	: property(name, posn, mortgage, cost_init){
	rent = {h0, h1, h2, h3, h4, hotel};
	houseprice = houseprice_init;
	house = 0;
}


int railroad::getrent(){
	if (ismortgaged){
		return 0;
	}
	int railroad_owned = 0;
	for (int i=0; i<4; i++){
		if(railroads[i]->getowner() == owner){
			railroad_owned++;
		}
	}
	return 25 * railroad_owned;
}

railroad::railroad(std::string name, int posn, int mtg, int property_cost)
	: property(name, posn, mtg, property_cost){

}

utility::utility(std::string name, int posn, int mtg, int property_cost)
	: property(name, posn, mtg, property_cost){

}

square* square::clone() const{
	return new square(*this);
}

street* street::clone() const{
	return new street(*this);
}

railroad* railroad::clone() const{
	return new railroad(*this);
}

utility* utility::clone() const{
	return new utility(*this);
}

square square::operator=(const square& rhs){
	return rhs;
}

property property::operator=(const property& rhs){
	return rhs;
}

street street::operator=(const street& rhs){

	return rhs;
}

railroad railroad::operator=(const railroad& rhs){
	return rhs;
}

utility utility::operator=(const utility& rhs){
	return rhs;
}


std::ostream& square::output(std::ostream& out) const{
	out<< position << ": " << name << std::endl;
	return out;
}

std::ostream& property::output(std::ostream& out) const{
	square::output(out);
	out<< '\t' << "Price: " << price << std::endl;
	out<< '\t' << "Owner: Player" << owner << std::endl;
	out<< '\t' << "Mortgage Value: " << mortgage << std::endl;
	return out;
}

std::ostream& street::output(std::ostream& out) const{
	property::output(out);
	out<< '\t' << "Price: " << price << std::endl;
	out<< '\t' << "Mortgage Value: " << mortgage << std::endl;
	out<< '\t' << "Rent:" << std::endl;
	out<< '\t' << '\t' << "0 house: " << rent[0] << std::endl;
	out<< '\t' << '\t' << "1 house: " << rent[1] << std::endl;
	out<< '\t' << '\t' << "2 house: " << rent[2] << std::endl;
	out<< '\t' << '\t' << "3 house: " << rent[3] << std::endl;
	out<< '\t' << '\t' << "4 house: " << rent[4] << std::endl;
	out<< '\t' << '\t' << "Hotel  : " << rent[5] << std::endl;
	out<< '\t' << "House costs " << houseprice << std::endl;
 	return out;
}

std::ostream& railroad::output(std::ostream& out) const{
	property::output(out);
	out<< '\t' << "Rent: 25 times the number of railroads the owner has " << std::endl;
	return out;
}

std::ostream& utility::output(std::ostream& out) const{
	property::output(out);
	out<< '\t' << "Rent: if owner owns 1 utility, 4 times the value of the die" << std::endl;
	out<< '\t' << "      if owner owns both utilities, 10 times the value of the die" << std::endl;
	return out;
}


std::ostream& operator<<(std::ostream& out, const square& rhs){
	return rhs.output(out);
}

std::ostream& operator<<(std::ostream& out, const street& rhs){
	return rhs.output(out);
}

std::ostream& operator<<(std::ostream& out, const railroad& rhs){
	return rhs.output(out);
}

std::ostream& operator<<(std::ostream& out, const utility& rhs){
	return rhs.output(out);
}


square square0("Go", 0);
square square2("Community Chest", 2);
square square4("Income tax", 4);
square square7("Chance", 7);
square square10("Jail", 10);
square square17("Community Chest", 17);
square square20("Free Parking", 20);
square square22("Chance", 22);
square square30("Go to jail", 30);
square square33("Community Chest", 33);
square square36("Chance", 36);
square square38("Chance", 38);

street mediterranean("Mediterranean Avenue", 1, 2, 10, 30, 90, 160, 250, 30, 50, 60);
street baltic("Baltic Avenue", 3, 4, 20, 60, 180, 320, 450, 30, 50, 60);
street oriental("Oriental Avenue", 6, 6, 30, 90, 270, 400, 550, 50, 50, 100);
street vermont("Vermont Avenue", 8, 6, 30, 90, 270, 400, 550, 50, 50, 100);
street connecticut("Connecticut Avenue", 9, 8, 40, 100, 300, 450, 600, 60, 50, 120);
street stcharles("St. Charles Place", 11, 10, 50, 150, 450, 625, 750, 70, 100, 140);
street states("States Avenue", 13, 10, 50, 150, 450, 625, 750, 70, 100, 140);
street virginia("Virginia Avenue", 14, 12, 60, 180, 500, 700, 900, 80, 100, 160);
street stjames("St. James Place", 16, 14, 70, 200, 550, 750, 950, 90, 100, 180);
street tennessee("Tennessee Avenue", 18, 14, 70, 200, 550, 750, 950, 90, 100, 180);
street ny("New York Avenue", 19, 16, 80, 220, 600, 800, 1000, 100, 100, 200);
street kentucky("Kentucky Avenue", 21, 18, 90, 250, 700, 875, 1050, 110, 150, 220);
street indiana("Indiana Avenue", 23, 18, 90, 250, 700, 875, 1050, 110, 150, 220);
street illinois("Illinois Avenue", 24, 20, 100, 300, 750, 925, 1100, 120, 150, 240);
street atlantic("Atlantic Avenue", 26, 22, 110, 330, 800, 975, 1150, 130, 150, 260);
street ventnor("Ventnor Avenue", 27, 22, 110, 330, 800, 975, 1150, 130, 150, 260);
street mgardens("Marvin Gardens", 29, 24, 120, 360, 850, 1025, 1200, 140, 150, 280);
street pacific("Pacific Avenue", 31, 26, 130, 390, 900, 1100, 1275, 150, 200, 300);
street ncarolina("North Carolina Avenue", 32, 26, 130, 390, 900, 1100, 1275, 150, 200, 300);
street penn("Pennsylvania Avenue", 34, 28, 150, 450, 1000, 1200, 1400, 160, 200, 320);
street park("Park Place", 37, 35, 175, 500, 1100, 1300, 1500, 175, 200, 350);
street boardwalk("Boardwalk", 39, 50, 200, 600, 1400, 1700, 2000, 200, 200, 400);

railroad reading("Reading Railroad", 5, 100, 200);
railroad pennr("Pennsylvania Railroad", 15, 100, 200);
railroad bo("B&O Railroad", 25, 100, 200);
railroad sline("Short Line Railroad", 35, 100, 200);

utility electricity("Electricity Company", 12, 75, 150);
utility water("Water Works", 28, 75, 150);


property* const properties[28] = {&mediterranean, &baltic, &reading,
	&oriental, &vermont, &connecticut, &stcharles, &electricity, &states, &virginia,
	&pennr, &stjames, &tennessee, &ny, &kentucky, &indiana, &illinois,
	&bo, &atlantic, &ventnor, &water, &mgardens, &pacific, &ncarolina, &penn,
	&sline, &park, &boardwalk};

railroad* const railroads[4] = {&reading, &pennr, &bo, &sline};

utility* const utilities[2] = {&electricity, &water};

square* const current_board[40] = {&square0, &mediterranean, &square2, &baltic, &square4, &reading,
		&oriental, &square7, &vermont, &connecticut, &square10, &stcharles, &electricity, &states,
		&virginia,	&pennr, &stjames, &square17, &tennessee, &ny, &square20, &kentucky, &square22,
		&indiana, &illinois, &bo, &atlantic, &ventnor, &water, &mgardens, &square30, &pacific,
		&ncarolina,	&square33, &penn, &sline, &square36, &park, &square38, &boardwalk};

