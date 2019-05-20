/*
 * property.cpp
 *
 *  Created on: Apr. 25, 2019
 *      Author: zheng qing yu
 */

#include "property.h"

std::string property::getname(){
	return name;
}

int property::getowner(){
	return owner;
}

int property::getposition(){
	return position;
}

int property::getmortgage(){
	return mortgage;
}

int property::getcost(){
	return cost;
}

void property::setowner(int own){
	owner = own;
}

property::property(std::string n, int posn, int mtg, int property_cost){
	name = n;
	position = posn;
	owner = 0;
	mortgage = mtg;
	cost = property_cost;
}

int street::gethouseprice(){
	return houseprice;
}

int street::getrent(){
	return rent.at(house);
}

street::street(std::string name, int posn, int h0, int h1, int h2, int h3, int h4, int hotel,
		int mtg, int housecost, int property_cost) : property(name, posn, mtg, property_cost){
	rent = {h0, h1, h2, h3, h4, hotel};
	houseprice = housecost;
	house = 0;
}


int railroad::getrent(){
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



property* const streets[26] = {&mediterranean, &baltic, &reading,
	&oriental, &vermont, &connecticut, &stcharles, &states, &virginia,
	&pennr, &stjames, &tennessee, &ny, &kentucky, &indiana, &illinois,
	&bo, &atlantic, &ventnor, &mgardens, &pacific, &ncarolina, &penn,
	&sline, &park, &boardwalk};

railroad* const railroads[4] = {&reading, &pennr, &bo, &sline};

utility* const utilities[2] = {&electricity, &water};
