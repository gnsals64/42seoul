#include "ScavTrap.hpp"

ScavTrap::ScavTrap() {
	this->name = "default";
	this->Hit_points = 100;
	this->Energy_points = 50;
	this->Attack_damage = 20;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) {
	this->name = name;
	this->Hit_points = 100;
	this->Energy_points = 50;
	this->Attack_damage = 20;
	std::cout << "ScavTrap name constructor called" << std::endl;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap Destructor called" << std::endl;
}
