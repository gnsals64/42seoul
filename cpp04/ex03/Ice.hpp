#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"

class Ice : public AMateria {
	public:
		Ice(void);
		~Ice(void);
		Ice(const Ice& cpy);
		Ice& operator=(const Ice& cpy);
		void use(ICharacter& target);
		AMateria* clone() const;
};

#endif
