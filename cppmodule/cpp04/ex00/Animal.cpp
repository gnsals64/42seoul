#include "Animal.hpp"

Animal::Animal(void) {
	std::cout << "Default constructor called" << std::endl;
	this->type = "default";
}

Animal::~Animal(void) {
	std::cout << "Animal Destructor called" << std::endl;
}

Animal::Animal(const Animal& cpy) {
	std::cout << "Animal Copy constructor called" << std::endl;
	this->type = cpy.type;
}

Animal& Animal::operator=(const Animal& cpy) {
	std::cout << "Animal Copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	return *this;
}

void	Animal::makeSound(void) const {
	std::cout << "The animal didn't make any sound" << std::endl;
}

std::string	Animal::getType(void) const {
	return this->type;
}

Cat::Cat(void) {
	std::cout << "Cat constructor called" << std::endl;
	this->type = "Cat";
}

Cat::~Cat(void) {
	std::cout << "Cat destructor called" << std::endl;
}

Cat::Cat(const Cat& cpy) {
	std::cout << "Cat copy constructor called" << std::endl;
	this->type = cpy.type;
}

Cat& Cat::operator=(const Cat& cpy) {
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	return *this;
}

void	Cat::makeSound(void) const{
	std::cout << "The cat meowed" << std::endl;
}

std::string	Cat::getType(void) const {
	return this->type;
}

Dog::Dog(void) {
	std::cout << "Dog constructor called" << std::endl;
	this->type = "Dog";
}

Dog::~Dog(void) {
	std::cout << "Dog destructor called" << std::endl;
}

Dog::Dog(const Dog& cpy) {
	std::cout << "Dog copy constructor called" << std::endl;
	this->type = cpy.type;
}

Dog& Dog::operator=(const Dog& cpy) {
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	return *this;
}

void	Dog::makeSound(void) const{
	std::cout << "The dog barked" << std::endl;
}

std::string	Dog::getType(void) const {
	return this->type;
}
