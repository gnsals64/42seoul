#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template<typename T>
class Array {
private:
	T		*arr;
	size_t	arr_size;

public:
	Array() : arr_size(0) { arr = new T[0]; };
	~Array() { delete arr; };
	Array(unsigned int n) : arr_size(n) { arr = new T[n](0); };
	Array(const Array &cpy) {
		arr = new T[cpy.size()];
		for (int i = 0; i < cpy.size(); i++) {
			this->arr[i] = cpy[i];
		}
	};
	Array& operator=(const Array &cpy) {
		if (this == &cpy)
			return *this;
		arr = new T[cpy.size()];
		for (int i = 0; i < cpy.size(); i++) {
			this->arr[i] = cpy[i];
		}
		return *this;
	}
	size_t size() { return arr_size; } const;
	T operator[] (size_t i) {
		if (i >= arr_size)
			throw Array<T>::indexoutofrange();
		return arr[i];
	};
	class indexoutofrange : public std::exception {
		public:
		    const char * what() const throw() {
				return "out of range";
			};
	};
};

#endif