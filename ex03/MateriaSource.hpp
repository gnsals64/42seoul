#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource{
	public:
		MateriaSource(void);
		~MateriaSource(void);
		MateriaSource(const MateriaSource& cpy);
		MateriaSource& operator=(const MateriaSource& cpy);
		void	learnMateria(AMateria*);
		AMateria*	createMateria(std::string const & type);
	private:
		AMateria *slots[4];
};

#endif
