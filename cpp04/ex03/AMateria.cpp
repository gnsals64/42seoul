#include "AMateria.hpp"

AMateria::AMateria(void) {}

AMateria::~AMateria(void) {}

AMateria::AMateria(const AMateria& cpy) {
	this->type = cpy.type;
}

AMateria& AMateria::operator=(const AMateria& cpy) {
	if (this == &cpy)
		return *this;
	this->type = cpy.type;
	return *this;
}

std::string const& AMateria::getype() const {
	return this->type;
}

void AMateria::use(ICharacter& target) {
	std::cout << target.getName() << std::endl;
}
