#include "Pmergeme.hpp"

Pmergeme::Pmergeme() : _odd(false) , _lastnum(0) {}

Pmergeme::~Pmergeme() {}

Pmergeme::Pmergeme(const Pmergeme &cpy) {
	this->_v = cpy._v;
	this->_li = cpy._li;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
}

Pmergeme& Pmergeme::operator=(const Pmergeme &cpy) {
	if (this == &cpy)
		return *this;
	this->_v = cpy._v;
	this->_li = cpy._li;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
	return *this;
}

void	Pmergeme::init_v(int ac, char **av) {
	this->oddCheck(&ac, av);
	this->fillVector(ac, av);
	this->swapPairV();
	this->sortPairV();
}

void	Pmergeme::init_li(int ac, char **av) {
	this->oddCheck(&ac, av);
	this->fillList(ac, av);
	this->swapPairLi();
	this->sortPairLi();
}

void	Pmergeme::oddCheck(int *ac, char **av) {
	if (*ac % 2 == 0) {
		this->_odd = true;
		this->_lastnum = atoi(av[*ac - 1]);
		(*ac)--;
	}
}

void	Pmergeme::fillVector(int ac,  char **av) {
	for (int i = 1; i < ac; i += 2) {
		for (size_t j = 0; j < strlen(av[i]); j++) {
			if (isdigit(av[i][j]) == false)
				throw std::runtime_error("Error");
		}
		for (size_t j = 0; j < strlen(av[i + 1]); j++) {
			if (isdigit(av[i + 1][j]) == false)
				throw std::runtime_error("Error");
		}
		this->_v.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
	}
}

void	Pmergeme::fillList(int ac,  char **av) {
	for (int i = 1; i < ac; i += 2) {
		for (size_t j = 0; j < strlen(av[i]); j++) {
			if (isdigit(av[i][j]) == false)
				throw std::runtime_error("Error");
		}
		for (size_t j = 0; j < strlen(av[i + 1]); j++) {
			if (isdigit(av[i + 1][j]) == false)
				throw std::runtime_error("Error");
		}
		this->_li.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
	}
}

void	Pmergeme::swapPairV() {
	std::vector<std::pair<int, int> >::iterator it = _v.begin();
	
	while (it != _v.end()) {
		if (it->second > it->first) {
			swap(it->second, it->first);
		}
		it++;
	}
}

void	Pmergeme::swapPairLi() {
	std::list<std::pair<int, int> >::iterator it = _li.begin();
	
	while (it != _li.end()) {
		if (it->second > it->first) {
			swap(it->second, it->first);
		}
		it++;
	}
}

void	Pmergeme::sortPairV() {
	std::vector<std::pair<int, int> >::iterator it = _v.begin();

	while (it != _v.end()) {
		std::vector<std::pair<int, int> >::iterator it_move = it;
		std::vector<std::pair<int, int> >::iterator it_min = it;
		while (it_move != _v.end()) {
			if (it_min->first > it_move->first)
				it_min = it_move;
			it_move++;
		}
		if (it_min != it) {
			swap(it->first, it_min->first);
			swap(it->second, it_min->second);
		}
		it++;
	}
}

void	Pmergeme::sortPairLi() {
	std::list<std::pair<int, int> >::iterator it = _li.begin();

	while (it != _li.end()) {
		std::list<std::pair<int, int> >::iterator it_move = it;
		std::list<std::pair<int, int> >::iterator it_min = it;
		while (it_move != _li.end()) {
			if (it_min->first > it_move->first)
				it_min = it_move;
			it_move++;
		}
		if (it_min != it) {
			swap(it->first, it_min->first);
			swap(it->second, it_min->second);
		}
		it++;
	}
}

void	swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}