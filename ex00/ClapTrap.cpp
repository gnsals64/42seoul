#include "ClapTrap.hpp"

ClapTrap::ClapTrap(){
	std::cout << "Default constructor called" << std::endl;
	this->name = "default";
	this->Hit_points = 10;
	this->Envergy_points = 10;
	this->Attack_damage = 0;
}

ClapTrap::ClapTrap(std::string name){
	std::cout << "name constructor called" << std::endl;
	this->name = name;
	this->Hit_points = 10;
	this->Envergy_points = 10;
	this->Attack_damage = 0;
}

ClapTrap::~ClapTrap(){
	std::cout << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& cpy){
	std::cout << "Copy constructor called" << std::endl;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Envergy_points = cpy.Envergy_points;
	this->Attack_damage = cpy.Attack_damage;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& cpy){
	std::cout << "Copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Envergy_points = cpy.Envergy_points;
	this->Attack_damage = cpy.Attack_damage;
	return *this;
}
