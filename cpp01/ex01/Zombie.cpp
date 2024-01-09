#include "Zombie.hpp"

Zombie::Zombie(){
	return ;
}

Zombie::~Zombie(){
	std::cout << "del " << this->name << std::endl;
}

void	Zombie::announce(void){
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setname(std::string name){
	this->name = name;
}
