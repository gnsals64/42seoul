#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include "ICharacter.hpp"

class ICharacter;

class AMateria {
	protected:
		std::string	type;

	public:
		AMateria(void);
		virtual ~AMateria(void);
		AMateria(const AMateria& cpy);
		AMateria& operator=(const AMateria& cpy);
		std::string const& getype() const;
		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};

#endif
