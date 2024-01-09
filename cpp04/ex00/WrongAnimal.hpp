#ifndef WRONGANIMAL_HPP
# define  WRONGANIMAL_HPP

#include <iostream>

class WrongAnimal {
	protected:
		std::string type;
	public:
		WrongAnimal(void);
		WrongAnimal(const WrongAnimal& cpy);
		WrongAnimal& operator=(const WrongAnimal& cpy);
		~WrongAnimal(void);
		void	makeSound(void) const;
		std::string	getType(void) const;
};

class WrongCat : public WrongAnimal {
	public:
		WrongCat(void);
		WrongCat(const WrongCat& cpy);
		WrongCat& operator=(const WrongCat& cpy);
		~WrongCat(void);
		void	makeSound(void) const;
		std::string	getType(void) const;
};


#endif
