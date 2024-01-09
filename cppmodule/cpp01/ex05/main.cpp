#include "Harl.hpp"

int main()
{
	Harl	ha;

	ha.complain("DEBUG");
	ha.complain("INFO");
	ha.complain("WARNING");
	ha.complain("ERROR");
	ha.complain(NULL);
	return (0);
}
