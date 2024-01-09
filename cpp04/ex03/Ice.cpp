#include "Ice.hpp"
#include "ICharacter.hpp"

Ice::Ice(void) {
	this->type = "Ice";
}

Ice::~Ice(void) {}

Ice::Ice(const Ice& cpy) {
	this->type = cpy.type;
}

Ice& Ice::operator=(const Ice& cpy) {
	if (this == &cpy)
		return (*this);
	this->type = cpy.type;
	return (*this);
}

AMateria* Ice::clone() const {
	AMateria *tmp = new Ice();
	return tmp;
}

void	Ice::use(ICharacter& target) {
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
