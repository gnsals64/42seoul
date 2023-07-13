#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
	std::cout << "Default constructor called" << std::endl;
	this->name = "default";
	this->Hit_points = 10;
	this->Energy_points = 10;
	this->Attack_damage = 0;
}

ClapTrap::ClapTrap(std::string name) {
	std::cout << "name constructor called" << std::endl;
	this->name = name;
	this->Hit_points = 10;
	this->Energy_points = 10;
	this->Attack_damage = 0;
}

ClapTrap::~ClapTrap() {
	std::cout << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& cpy) {
	std::cout << "Copy constructor called" << std::endl;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Energy_points = cpy.Energy_points;
	this->Attack_damage = cpy.Attack_damage;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& cpy) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Energy_points = cpy.Energy_points;
	this->Attack_damage = cpy.Attack_damage;
	return *this;
}

void	ClapTrap::attack(const std::string& target) {
	if (this->Energy_points > 0 && this->Hit_points > 0) {
		std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing "
			<< this->Attack_damage << " points of damage!" << std::endl;
		this->Hit_points -= this->Attack_damage;
		this->Energy_points--;
	}
	else
		std::cout << "not enough energy or hitpoint" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (this->Energy_points > 0 && this->Hit_points > 0) {
		std::cout << this->name << " has recovered " << amount << std::endl;
		this->Hit_points += amount;
		this->Energy_points--;
	}
	else
		std::cout << "not enough energy or hitpoint" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (this->Energy_points > 0 && this->Hit_points > 0) {
		std::cout << this->name << " was damaged " << amount << std::endl;
		this->Hit_points -= amount;
		this->Energy_points--;
	}
	else
		std::cout << "not enough energy or hitpoint" << std::endl;
}
