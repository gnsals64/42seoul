#include "ClapTrap.hpp"

ClapTrap::ClapTrap(){
	this->name = "default";
	this->Hit_points = 10;
	this->Envergy_points = 10;
	this->Attack_damage = 0;
}

ClapTrap::ClapTrap(std::string name){
	this->name = name;
	this->Hit_points = 10;
	this->Envergy_points = 10;
	this->Attack_damage = 0;
}

ClapTrap::~ClapTrap(){
}

ClapTrap::ClapTrap(const ClapTrap& cpy){
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Envergy_points = cpy.Envergy_points;
	this->Attack_damage = cpy.Attack_damage;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& cpy){
	if (this == &cpy)
		return *this;
	this->name = cpy.name;
	this->Hit_points = cpy.Hit_points;
	this->Envergy_points = cpy.Envergy_points;
	this->Attack_damage = cpy.Attack_damage;
	return *this;
}


