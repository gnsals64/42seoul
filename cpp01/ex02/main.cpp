#include <iostream>

int main()
{
	std::string	str = "HI THIS IS BRAIN";
	std::string	*ptr = &str;
	std::string	&ref = str;

	std::cout << "str address is : " << &str << std::endl;
	std::cout << "ptr address is : " << ptr << std::endl;
	std::cout << "ref address is : " << &ref << std::endl;
	std::cout << "str value is : " << str << std::endl;
	std::cout << "ptr value is : " << *ptr << std::endl;
	std::cout << "ref value is : " << ref << std::endl;
	return (0);
}
