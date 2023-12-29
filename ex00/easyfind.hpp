#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <vector>

template<typename T>
typename T::iterator easyfind(T& containers, int value) {
	typename T::iterator it = std::find(containers.begin(), containers.end(), value);
	if (it == containers.end())
		throw std::runtime_error("not found");
	return it;
}

#endif