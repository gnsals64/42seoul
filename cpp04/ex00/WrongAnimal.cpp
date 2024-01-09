#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) {
	std::cout << "Default constructor called" << std::endl;
	this->type = "default";
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "WrongAnimal Destructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& cpy) {
	std::cout << "WrongAnimal Copy constructor called" << std::endl;
	this->type = cpy.type;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& cpy) {
	std::cout << "WrongAnimal Copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	return *this;
}

void	WrongAnimal::makeSound(void) const {
	std::cout << "The WrongAnimal didn't make any sound" << std::endl;
}

std::string	WrongAnimal::getType(void) const {
	return this->type;
}

WrongCat::WrongCat(void) {
	std::cout << "WrongCat constructor called" << std::endl;
	this->type = "WrongCat";
}

WrongCat::~WrongCat(void) {
	std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& cpy) {
	std::cout << "WrongCat copy constructor called" << std::endl;
	this->type = cpy.type;
}

WrongCat& WrongCat::operator=(const WrongCat& cpy) {
	std::cout << "WrongCat copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	return *this;
}

void	WrongCat::makeSound(void) const{
	std::cout << "The WrongCat meowed" << std::endl;
}

std::string	WrongCat::getType(void) const {
	return this->type;
}
