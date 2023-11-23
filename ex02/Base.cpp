#include "Base.hpp"

Base::~Base() {}

Base	*generate(void) {
		std::srand(time(NULL));
		int num = rand() % 9;
		
		if (num >= 0 && num <= 2)
			return new A();
		else if (num >= 3 && num <= 5)
			return new B();
		else if (num >= 6 && num <= 8)
			return new C();
		return NULL;
}

void	identify(Base* p) {
	if (dynamic_cast<A *>(p))
		std::cout << "this is A class" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "this is B class" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "this is C class" << std::endl;
}

void	identify(Base& p) {
	try {
		A &a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "this is A class" << std::endl;
	}
	catch (std::bad_cast) {}
	try {
		B &b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "this is B class" << std::endl;
	}
	catch (std::bad_cast) {}
	try {
		C &c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "this is C class" << std::endl;
	}
	catch (std::bad_cast) {}
}