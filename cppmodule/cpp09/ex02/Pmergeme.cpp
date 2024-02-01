#include "Pmergeme.hpp"

PmergemeV::PmergemeV() : _odd(false) , _lastnum(0) {}

PmergemeV::~PmergemeV() {}

PmergemeV::PmergemeV(int ac) {
	_odd = false;
	_lastnum = 0;
	_v2.resize(ac);
}

PmergemeV::PmergemeV(const PmergemeV &cpy) {
	this->_v1 = cpy._v1;
	this->_v2 = cpy._v2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
}

PmergemeV& PmergemeV::operator=(const PmergemeV &cpy) {
	if (this == &cpy)
		return *this;
	this->_v1 = cpy._v1;
	this->_v2 = cpy._v2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
	return *this;
}

PmergemeDe::PmergemeDe() : _odd(false) , _lastnum(0) {}

PmergemeDe::~PmergemeDe() {}

PmergemeDe::PmergemeDe(int ac) {
	_odd = false;
	_lastnum = 0;
	_de2.resize(ac);
}

PmergemeDe::PmergemeDe(const PmergemeDe &cpy) {
	this->_de1 = cpy._de1;
	this->_de2 = cpy._de2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
}

PmergemeDe& PmergemeDe::operator=(const PmergemeDe &cpy) {
	if (this == &cpy)
		return *this;
	this->_de1 = cpy._de1;
	this->_de2 = cpy._de2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
	return *this;
}

void	PmergemeV::init(int ac, char **av) {
	this->oddCheck(&ac, av);
	this->fillVector(ac, av);
	this->swapPair();
	this->mergesortPair();
}

void	PmergemeDe::init(int ac, char **av) {
	this->oddCheck(&ac, av);
	this->fillDeque(ac, av);
	this->swapPair();
	this->mergesortPair();
}

void	PmergemeV::oddCheck(int *ac, char **av) {
	if (*ac % 2 == 0) {
		this->_odd = true;
		this->_lastnum = atoi(av[*ac - 1]);
		(*ac)--;
	}
}

void	PmergemeDe::oddCheck(int *ac, char **av) {
	if (*ac % 2 == 0) {
		this->_odd = true;
		this->_lastnum = atoi(av[*ac - 1]);
		(*ac)--;
	}
}

void	PmergemeV::fillVector(int ac,  char **av) {
	for (int i = 1; i < ac; i += 2) {
		for (size_t j = 0; j < strlen(av[i]); j++) {
			if (isdigit(av[i][j]) == false)
				throw std::runtime_error("Error");
		}
		for (size_t j = 0; j < strlen(av[i + 1]); j++) {
			if (isdigit(av[i + 1][j]) == false)
				throw std::runtime_error("Error");
		}
		this->_v1.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
	}
}

void	PmergemeDe::fillDeque(int ac,  char **av) {
	for (int i = 1; i < ac; i += 2) {
		for (size_t j = 0; j < strlen(av[i]); j++) {
			if (isdigit(av[i][j]) == false)
				throw std::runtime_error("Error");
		}
		for (size_t j = 0; j < strlen(av[i + 1]); j++) {
			if (isdigit(av[i + 1][j]) == false)
				throw std::runtime_error("Error");
		}
		this->_de1.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
	}
}

void	PmergemeV::swapPair() {
	std::vector<std::pair<int, int> >::iterator it = _v1.begin();
	
	while (it != _v1.end()) {
		if (it->second > it->first) {
			swap(it->second, it->first);
		}
		it++;
	}
}

void	PmergemeDe::swapPair() {
	std::deque<std::pair<int, int> >::iterator it = _de1.begin();
	
	while (it != _de1.end()) {
		if (it->second > it->first) {
			swap(it->second, it->first);
		}
		it++;
	}
}

void	PmergemeV::mergesortPair() {
	this->partition(0, _v1.size() - 1);
}

void	PmergemeDe::mergesortPair() {
	this->partition(0, _de1.size() - 1);
}

void	swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void	PmergemeV::partition(int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		this->partition(left, mid);
		this->partition(mid + 1, right);
		this->merge(left, right);
	}
}

void	PmergemeV::merge(int left, int right) {
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right) {
		if (_v1[i].first <= _v1[j].first) {
			_v2[k] = std::make_pair(_v1[i].first, _v1[i].second);
			k++;
			i++;
		}
		else {
			_v2[k] = std::make_pair(_v1[j].first, _v1[j].second);
			k++;
			j++;
		}
	}
	int tmp = i > mid ? j : i;
	while (k <= right) {
		_v2[k] = std::make_pair(_v1[tmp].first, _v1[tmp].second);
		k++;
		tmp++;
	}
	for (int i = left; i <= right; i++) {
		_v1[i] = std::make_pair(_v2[i].first, _v2[i].second);
	}
}

void	PmergemeDe::partition(int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		this->partition(left, mid);
		this->partition(mid + 1, right);
		this->merge(left, right);
	}
}

void	PmergemeDe::merge(int left, int right) {
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right) {
		if (_de1[i].first <= _de1[j].first) {
			_de2[k] = std::make_pair(_de1[i].first, _de1[i].second);
			k++;
			i++;
		}
		else {
			_de2[k] = std::make_pair(_de1[j].first, _de1[j].second);
			k++;
			j++;
		}
	}
	int tmp = i > mid ? j : i;
	while (k <= right) {
		_de2[k] = std::make_pair(_de1[tmp].first, _de1[tmp].second);
		k++;
		tmp++;
	}
	for (int i = left; i <= right; i++) {
		_de1[i] = std::make_pair(_de2[i].first, _de2[i].second);
	}
}