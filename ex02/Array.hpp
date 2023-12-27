#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template<typename T>
class Array {
private:
	int *arr;

public:
	Array() { arr = new T };
	~Array() { del arr };
	Array(unsigned int n);
	Array(const Array &cpy);
	unsigned int size();
	T operator[] (int i) { return arr[i] };
};

#endif