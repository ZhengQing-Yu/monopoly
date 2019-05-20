#include "player.h"


int main(){
	srand(time(NULL));
	init();
	std::cout << "yeet" << std::endl;
	for (int u=0; u<26 ; u++){
		property* i = streets[u];
		std::cout << i->getname() << std::endl;
		std::cout << '\t' << " position: " << i->getposition() << std::endl;
		std::cout << '\t' << " rent with 0 house: " << i->getrent() << std::endl;
		std::cout << '\t' << " cost: "<< i->getcost() << std::endl;
		std::cout << '\t' << " mortgage cost: "<< i->getmortgage() << std::endl;
	}
}

