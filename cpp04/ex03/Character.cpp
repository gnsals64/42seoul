#include "Character.hpp"
#include "AMateria.hpp"

Character::Character(void) {}

Character::~Character(void) {}

Character::Character(std::string name) {
	for (int i = 0; i < 4; i++)
		this->slots[i] = NUake
		LL;
	this->name = name;
}

Character::Character(const Character& cpy) {
	this->name = cpy.name;
	for (int i = 0; i < 4; i++) {
		if (this->slots[i])
			delete(this->slots[i]);
		this->slots[i] = cpy.slots[i]->clone();
	}
}

Character& Character::operator=(const Character& cpy) {
	if (this == &cpy)
		return *this;
	this->name = cpy.name;
	for (int i = 0; i < 4; i++) {
		if (this->slots[i])
			delete(this->slots[i]);
		this->slots[i] = cpy.slots[i]->clone();
	}
	return *this;
}

std::string const& Character::getName() const {
	return this->name;
}

void	Character::equip(AMateria* m) {
	for (int i = 0; i < 4; i++) {
		if (this->slots[i] == NULL) {
			this->slots[i] = m->clone();
			break ;
		}
	}
}

void	Character::unequip(int idx) {
	this->slots[idx] == NULL;
}

void	Character::use(int idx, ICharacter& target) {
	this->slots[idx]->use(target);
}
