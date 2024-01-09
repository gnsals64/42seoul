#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <vector>
# include <stack>
# include <list>

template<typename T>
class MutantStack : public std::stack<T> {
public:
	MutantStack() {};
	~MutantStack() {};
	MutantStack(const MutantStack<T> &cpy) {
		this->_size = cpy._size;
		this->std::stack<T>::c = cpy.std::stack<T>::c;
	}
	MutantStack& operator=(const MutantStack &cpy) {
		if (this == &cpy)
			return *this;
		this->_size = cpy._size;
		this->std::stack<T>::c = cpy.std::stack<T>::c;
		return *this;
	}
	typedef typename std::stack<T>::container_type::iterator iterator;
	void	push(T a) {std::stack<T>::c.push_back(a);};
	void	pop() {std::stack<T>::c.pop_back();};
	size_t	size() {return std::stack<T>::c.size();};
	T		top() {return *(std::stack<T>::c.end() - 1);};
	iterator begin() {return std::stack<T>::c.begin();}
	iterator end() {return std::stack<T>::c.end();}
};

#endif
