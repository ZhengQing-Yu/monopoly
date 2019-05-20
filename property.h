/*
 * property.h
 *
 *  Created on: Apr. 25, 2019
 *      Author: zheng qing yu
 */

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

#ifndef PROPERTY_H_
#define PROPERTY_H_


class property{
	public:
		// constructor
		property(std::string name, int posn, int mtg, int property_cost);
		void setowner(int owner);

		std::string getname();
		int getposition();
		int getowner();
		int getmortgage();
		int getcost();
		// gets overridden by get_rent() method in its derived classes
		virtual int getrent(){
			return -1;
		}
	protected:
		std::string name;
		int position;
		int owner;
		int mortgage;
		int cost;
};

class street: public property{
	public:
		// constructor
		street(std::string name, int posn, int h0, int h1, int h2, int h3, int h4, int hotel,
				int mtg, int housecost, int property_cost);
		int gethouseprice();
		int getrent() override;

	protected:
		std::vector<int> rent;
		int houseprice;
		int house;
};

class railroad: public property{
	public:
		// constructor
		railroad(std::string name, int posn, int mtg, int property_cost);
		int getrent() override;
};

class utility: public property{
	public:
		utility(std::string name, int posn, int mtg, int property_cost);
};


extern property* const streets[];
extern railroad* const railroads[];
extern utility* const utilities[];

#endif /* PROPERTY_H_ */
