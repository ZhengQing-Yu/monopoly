/*
 * property.h
 *
 *  Created on: Apr. 25, 2019
 *      Author: zheng qing yu
 */
#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>


class square{
	public:
		square(std::string name, int posn);
		std::string getname() const;
		int getposition() const;
		virtual ~square(){};
		virtual square* clone() const;
		virtual square operator=(const square& rhs);
		virtual std::ostream& output(std::ostream& out) const;
	private:
		const std::string name;
		const int position;
};

class property: public square{
	public:
		// constructor
		property(std::string name, int posn, int mtg, int price);
		void setowner(int owner);
		int getowner() const;
		int getmortgagevalue() const;
		int getprice() const;
		bool ismortgaged;
		virtual ~property(){};
		// gets overridden by get_rent() method in its derived classes
		virtual int getrent(){
			return {};
		}
		virtual property operator=(const property& rhs);
		virtual std::ostream& output(std::ostream& out) const;
	protected:
		int owner = 0;
		int mortgage;
		int price;
};

class street: public property{
	public:
		// constructor
		street(std::string name, int posn, int h0, int h1, int h2, int h3, int h4, int hotel,
				int mortgage, int houseprice, int price);
		int gethouseprice() const;
		void addhouse();
		int getrent() override;
		virtual ~street(){};
		virtual street* clone() const;
		virtual street operator=(const street& rhs);
		virtual std::ostream& output(std::ostream& out) const;
	protected:
		std::vector<int> rent;
		int houseprice;
		int house = 0;
};

class railroad: public property{
	public:
		// constructor
		railroad(std::string name, int posn, int mtg, int property_cost);
		int getrent() override;
		virtual ~railroad(){};
		virtual railroad* clone() const;
		virtual railroad operator=(const railroad& rhs);
		virtual std::ostream& output(std::ostream& out) const;
};

class utility: public property{
	public:
		utility(std::string name, int posn, int mtg, int property_cost);
		virtual ~utility(){};
		virtual utility* clone() const;
		virtual utility operator=(const utility& rhs);
		virtual std::ostream& output(std::ostream& out) const;
};

// Output operators
std::ostream& operator<<(std::ostream& out, const square& rhs);
std::ostream& operator<<(std::ostream& out, const street& rhs);
std::ostream& operator<<(std::ostream& out, const railroad& rhs);
std::ostream& operator<<(std::ostream& out, const utility& rhs);


extern property* const properties[];
extern railroad* const railroads[];
extern utility* const utilities[];
extern square* const current_board[];

#endif /* PROPERTY_H_ */
