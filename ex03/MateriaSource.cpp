#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void) {}

MateriaSource::~MateriaSource(void) {}

MateriaSource::MateriaSource(const MateriaSource& cpy) {

}

MateriaSource& MateriaSource::operator=(const MateriaSource& cpy) {
	if (this == &cpy)
		return *this;
	return *this;
}

void	MateriaSource::learnMateria(AMateria*){}

AMateria*	MateriaSource::createMateria(std::string const & type){}
