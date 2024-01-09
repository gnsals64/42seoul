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
	this->brain = new Brain;
	this->type = "Cat";
}

Cat::~Cat(void) {
	delete this->brain;
	std::cout << "Cat destructor called" << std::endl;
}

Cat::Cat(const Cat& cpy) {
	std::cout << "Cat copy constructor called" << std::endl;
	this->type = cpy.type;
	this->brain = cpy.brain;
}

Cat& Cat::operator=(const Cat& cpy) {
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	this->brain = cpy.brain;
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
	this->brain = new Brain;
}

Dog::~Dog(void) {
	delete this->brain;
	std::cout << "Dog destructor called" << std::endl;
}

Dog::Dog(const Dog& cpy) {
	std::cout << "Dog copy constructor called" << std::endl;
	this->type = cpy.type;
	this->brain = new Brain;
}

Dog& Dog::operator=(const Dog& cpy) {
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	this->brain = cpy.brain;
	return *this;
}

void	Dog::makeSound(void) const{
	std::cout << "The dog barked" << std::endl;
}

std::string	Dog::getType(void) const {
	return this->type;
}

Brain::Brain(void) {
	std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& cpy) {
	std::cout << "Brain copy constructor called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = cpy.ideas[i];
	}
}

Brain& Brain::operator=(const Brain& cpy) {
	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this == &cpy)
		return *this;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = cpy.ideas[i];
	}
	return *this;
}

Brain::~Brain(void) {
	std::cout << "Brain Destructor called" << std::endl;
}
