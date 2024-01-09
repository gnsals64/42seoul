#include "FlagTrap.hpp"

FlagTrap::FlagTrap() {
	this->name = "default";
	this->Hit_points = 100;
	this->Energy_points = 50;
	this->Attack_damage = 20;
	std::cout << "FlagTrap default constructor called" << std::endl;
}

FlagTrap::FlagTrap(std::string name) : ClapTrap(name) {
	this->name = name;
	this->Hit_points = 100;
	this->Energy_points = 50;
	this->Attack_damage = 20;
	std::cout << "FlagTrap name constructor called" << std::endl;
}

FlagTrap::FlagTrap(const FlagTrap& cpy) : ClapTrap(cpy) {
	std::cout << "FlagTrap Copy constructor called" << std::endl;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Energy_points = cpy.Energy_points;
	this->Attack_damage = cpy.Attack_damage;
}

FlagTrap& FlagTrap::operator=(const FlagTrap& cpy) {
	std::cout << "FlagTrap Copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Energy_points = cpy.Energy_points;
	this->Attack_damage = cpy.Attack_damage;
	return *this;
}

FlagTrap::~FlagTrap() {
	std::cout << "FlagTrap Destructor called" << std::endl;
}

void	FlagTrap::attack(const std::string& target) {
	if (this->Energy_points > 0 && this->Hit_points > 0) {
		std::cout << "FlagTrap " << this->name << " attacks " << target
		<< " , causing " << this->Attack_damage << " points of damage!" << std::endl;
		this->Hit_points -= this->Attack_damage;
		this->Energy_points--;
	}
	else
		std::cout << "FlagTrap can't do anything" << std::endl;
}

void	FlagTrap::highFivesGuys(void) {
	if (this->Energy_points > 0 && this->Hit_points > 0) {
		std::cout << "high five" << std::endl;
	}
	else
		std::cout << "FlagTrap can't do anything" << std::endl;
}
