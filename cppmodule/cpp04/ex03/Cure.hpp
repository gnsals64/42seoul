#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

class Cure : public AMateria {
	public:
		Cure(void);
		~Cure(void);
		Cure(const Cure& cpy);
		Cure& operator=(const Cure& cpy);
		AMateria* clone() const;
		void use(ICharacter& target);
};

#endif
