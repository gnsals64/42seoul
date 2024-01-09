#ifndef FLAGTRAP_HPP
# define FLAGTRAP_HPP

# include "ClapTrap.hpp"

class FlagTrap : public ClapTrap {
	public:
		FlagTrap(void);
		FlagTrap(std::string name);
		FlagTrap(const FlagTrap& cpy);
		FlagTrap& operator=(const FlagTrap& cpy);
		~FlagTrap(void);
		void	attack(const std::string& target);
		void	highFivesGuys(void);
};

#endif
