#include "Animal.hpp"
#include "WrongAnimal.hpp"


int main()
{
	std::cout << "Correct Animal class" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << "\n";
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();
	std::cout << "\n";
	delete meta;
	delete j;
	delete i;
	std::cout << "\n" << std::endl;
	std::cout << "Wrong Animal class" << std::endl;
	const WrongAnimal* wmeta = new WrongAnimal();
	const WrongAnimal* wi = new WrongCat();
	std::cout << "\n";
	std::cout << wi->getType() << " " << std::endl;
	wi->makeSound(); //will output the cat sound!
	wmeta->makeSound();
	std::cout << "\n";
	delete wmeta;
	delete wi;
	return (0);
}

