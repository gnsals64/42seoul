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

void	MateriaSource::learnMateria(AMateria* a) {
	for (int i = 0; i < 4; i++){
		if (!this->slots[i]) {
			this->slots[i] = a;
			return ;
		}
	}
}

AMateria*	MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < 4; i++) {
		if (this->slots[i]->getype() == type) {
			AMateria *tmp = this->slots[i]->clone();
			return tmp;
		}
	}
	return NULL;
}
