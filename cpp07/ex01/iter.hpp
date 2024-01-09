#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>

template <typename A, typename B>
void	iter(A *arr, size_t len, B fun) {
	for (size_t i = 0; i < len; i++)
		fun(arr[i]);
	return ;
};

#endif