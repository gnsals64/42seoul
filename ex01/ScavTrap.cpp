#include "ScavTrap.hpp"

ScavTrap::ScavTrap() {
	this->name = "default";
	this->Hit_points = 100;
	this->Energy_points = 50;
	this->Attack_damage = 20;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	this->name = name;
	this->Hit_points = 100;
	this->Energy_points = 50;
	this->Attack_damage = 20;
	std::cout << "ScavTrap name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& cpy) : ClapTrap(cpy) {
	std::cout << "ScavTrap Copy constructor called" << std::endl;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Energy_points = cpy.Energy_points;
	this->Attack_damage = cpy.Attack_damage;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& cpy) {
	std::cout << "ScavTrap Copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Energy_points = cpy.Energy_points;
	this->Attack_damage = cpy.Attack_damage;
	return *this;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap Destructor called" << std::endl;
}

void	ScavTrap::attack(const std::string& target) {
	if (this->Energy_points > 0 && this->Hit_points > 0) {
		std::cout << "ScavTrap " << this->name << " attacks " << target
		<< " , causing " << this->Attack_damage << " points of damage!" << std::endl;
		this->Hit_points -= this->Attack_damage;
		this->Energy_points--;
	}
	else
		std::cout << "ScavTrap can't do anything" << std::endl;
}

void	ScavTrap::guardGate() {
	if (this->Energy_points > 0 && this->Hit_points > 0) {
		std::cout << "ScavTrap is now in Gatekeeper mode" << std::endl;
		this->Energy_points--;
	}
	else
		std::cout << "ScavTrap can't do anything" << std::endl;
}
