#include "Serializer.hpp"

int main() {
	Serializer s;
	Data *a;
	Data *tmp;
	uintptr_t t;

	a = new Data;
	a->a = 10;
	a->b = 20;
	t = s.serialize(a);
	tmp = s.deserialize(t);
	std::cout << "a = " << tmp->a << "\nb = " << tmp->b << std::endl;
	delete a;
	return 0;
}