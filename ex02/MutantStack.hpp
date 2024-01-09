#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <vector>
# include <stack>

template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
private:
	size_t _size;
	Container c;

public:
	MutantStack() : _size(0) {};
	~MutantStack() {};
	MutantStack(const MutantStack<T> &cpy) {
		this->_size = cpy._size;
		this->c = cpy.c;
	}
	MutantStack& operator=(const MutantStack &cpy) {
		if (this == &cpy)
			return *this;
		this->_size = cpy._size;
		this->c = cpy.c;
		return *this;
	}
	typedef typename Container::iterator iterator;
	void	push(T a) {c.push_back(a); _size++;};
	void	pop() {c.pop_back(); _size--;};
	size_t	size() {return _size;};
	T		top() {return *(c.end() - 1);};
	iterator begin() {return c.begin();}
	iterator end() {return c.end();}
};

#endif