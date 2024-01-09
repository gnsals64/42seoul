#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>

class Animal {
	protected:
		std::string type;
	public:
		Animal(void);
		Animal(const Animal& cpy);
		Animal& operator=(const Animal& cpy);
		virtual ~Animal(void);
		virtual void	makeSound(void) const = 0;
		virtual std::string	getType(void) const;
};

class Brain {
	private:
		std::string	ideas[100];
	public:
		Brain(void);
		Brain(const Brain& cpy);
		Brain& operator=(const Brain& cpy);
		~Brain(void);
};

class Cat : public Animal {
	private:
		Brain *brain;
	public:
		Cat(void);
		Cat(const Cat& cpy);
		Cat& operator=(const Cat& cpy);
		virtual ~Cat(void);
		virtual void	makeSound(void) const;
		virtual std::string	getType(void) const;
};

class Dog : public Animal {
	private:
		Brain *brain;
	public:
		Dog(void);
		Dog(const Dog& cpy);
		Dog& operator=(const Dog& cpy);
		virtual ~Dog(void);
		virtual void	makeSound(void) const;
		virtual std::string	getType(void) const;
};

#endif
