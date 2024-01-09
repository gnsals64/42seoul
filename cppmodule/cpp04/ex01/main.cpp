#include "Animal.hpp"

int main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << "\n";
	delete j;
	delete i;
	return (0);
}
