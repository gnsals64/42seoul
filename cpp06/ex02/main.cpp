#include "Base.hpp"

int main() {
	Base *a = generate();
	C d;
	Base g;
	
	
	identify(a);
	identify(NULL);
	identify(d);
	identify(g);
}