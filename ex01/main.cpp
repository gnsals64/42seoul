#include "iter.hpp"

void	print_str(char a) {
	std::cout << a << std::endl;
}

void	print_int(int a) {
	std::cout << a << std::endl;
}

int main() {
	char	arr1[] = "Hello";
	int		arr2[] = {1, 2, 3};

	iter(arr1, 5, &print_str);
	iter(arr2, 3, &print_int);
	return 0;
}