#include "Cure.hpp"
#include "ICharacter.hpp"

Cure::Cure(void) {
	this->type = "Cure";
}

Cure::~Cure(void) {}

Cure::Cure(const Cure& cpy) {
	this->type = cpy.type;
}

Cure& Cure::operator=(const Cure& cpy) {
	if (this == &cpy)
		return (*this);
	this->type = cpy.type;
	return (*this);
}

AMateria* Cure::clone() const {
	AMateria *tmp = new Cure();
	return tmp;
}

void	Cure::use(ICharacter& target) {
	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
