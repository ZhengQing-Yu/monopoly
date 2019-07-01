#include "board.h"


int main(){
	srand(time(NULL));
	std::cout << __cplusplus <<std::endl;
	for (int i=0; i<40 ; i++){
		std::cout<< *current_board[i] << std::endl;
	}
	board newboard;
	for(auto i: newboard.players){
		std::cout<< i.getname() << std::endl;
	}
}
