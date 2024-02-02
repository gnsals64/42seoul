#include "Pmergeme.hpp"

PmergemeV::PmergemeV() : _odd(false) , _lastnum(0) {}

PmergemeV::~PmergemeV() {}

PmergemeV::PmergemeV(int ac) {
	_odd = false;
	_lastnum = 0;
	_pair_num2.resize(ac);
}

PmergemeV::PmergemeV(const PmergemeV &cpy) {
	this->_pair_num1 = cpy._pair_num1;
	this->_pair_num2 = cpy._pair_num2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
}

PmergemeV& PmergemeV::operator=(const PmergemeV &cpy) {
	if (this == &cpy)
		return *this;
	this->_pair_num1 = cpy._pair_num1;
	this->_pair_num2 = cpy._pair_num2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
	return *this;
}

PmergemeDe::PmergemeDe() : _odd(false) , _lastnum(0) {}

PmergemeDe::~PmergemeDe() {}

PmergemeDe::PmergemeDe(int ac) {
	_odd = false;
	_lastnum = 0;
	_pair_num2.resize(ac);
}

PmergemeDe::PmergemeDe(const PmergemeDe &cpy) {
	this->_pair_num1 = cpy._pair_num1;
	this->_pair_num2 = cpy._pair_num2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
}

PmergemeDe& PmergemeDe::operator=(const PmergemeDe &cpy) {
	if (this == &cpy)
		return *this;
	this->_pair_num1 = cpy._pair_num1;
	this->_pair_num2 = cpy._pair_num2;
	this->_lastnum = cpy._lastnum;
	this->_odd = cpy._odd;
	return *this;
}

void	PmergemeV::init(int ac, char **av) {
	this->numCheck(ac, av);
	this->oddCheck(&ac, av);
	this->fillVector(ac, av);
	this->swapPair();
	this->mergesortPair();
}

void	PmergemeDe::init(int ac, char **av) {
	this->numCheck(ac, av);
	this->oddCheck(&ac, av);
	this->fillDeque(ac, av);
	this->swapPair();
	this->mergesortPair();
}

void	PmergemeV::numCheck(int ac, char **av) {


	for (int i = 1; i < ac; i++) {
		for (size_t j = 0; j < strlen(av[i]); j++) {
			if (isdigit(av[i][j]) == false)
				throw std::runtime_error("Error");
		}
		std::stringstream ss(av[i]);
		double tmp;
		ss >> tmp;
		if (tmp > 2147483647)
			throw std::runtime_error("Error");
		ss.str("");
	}
}

void	PmergemeDe::numCheck(int ac, char **av) {

	for (int i = 1; i < ac; i++) {
		for (size_t j = 0; j < strlen(av[i]); j++) {
			if (isdigit(av[i][j]) == false)
				throw std::runtime_error("Error");
		}
		std::stringstream ss(av[i]);
		double tmp;
		ss >> tmp;
		if (tmp > 2147483647)
			throw std::runtime_error("Error");
		ss.str("");
	}
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

int	PmergemeV::makeJacobnum(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return makeJacobnum(n - 1) + 2 * makeJacobnum(n - 2);
}

int	PmergemeDe::makeJacobnum(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return makeJacobnum(n - 1) + 2 * makeJacobnum(n - 2);
}

void	PmergemeV::fillVector(int ac,  char **av) {
	for (int i = 1; i < ac; i += 2) {
		this->_before_sort.push_back(atoi(av[i]));
		this->_before_sort.push_back(atoi(av[i + 1]));
		if (i + 2 == ac && _odd == true) {
			this->_before_sort.push_back(atoi(av[i + 2]));
		}
		this->_pair_num1.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
	}
}

void	PmergemeDe::fillDeque(int ac,  char **av) {
	for (int i = 1; i < ac; i += 2) {
		this->_before_sort.push_back(atoi(av[i]));
		this->_before_sort.push_back(atoi(av[i + 1]));
		if (i + 2 == ac && _odd == true) {
			this->_before_sort.push_back(atoi(av[i + 2]));
		}
		this->_pair_num1.push_back(std::make_pair(atoi(av[i]), atoi(av[i + 1])));
	}
}

void	PmergemeV::swapPair() {
	std::vector<std::pair<int, int> >::iterator it = _pair_num1.begin();

	while (it != _pair_num1.end()) {
		if (it->second > it->first) {
			swap(it->second, it->first);
		}
		it++;
	}
}

void	PmergemeDe::swapPair() {
	std::deque<std::pair<int, int> >::iterator it = _pair_num1.begin();

	while (it != _pair_num1.end()) {
		if (it->second > it->first) {
			swap(it->second, it->first);
		}
		it++;
	}
}

void	PmergemeV::mergesortPair() {
	this->partition(0, _pair_num1.size() - 1);
}

void	PmergemeDe::mergesortPair() {
	this->partition(0, _pair_num1.size() - 1);
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
		if (_pair_num1[i].first <= _pair_num1[j].first) {
			_pair_num2[k] = std::make_pair(_pair_num1[i].first, _pair_num1[i].second);
			k++;
			i++;
		}
		else {
			_pair_num2[k] = std::make_pair(_pair_num1[j].first, _pair_num1[j].second);
			k++;
			j++;
		}
	}
	int tmp = i > mid ? j : i;
	while (k <= right) {
		_pair_num2[k] = std::make_pair(_pair_num1[tmp].first, _pair_num1[tmp].second);
		k++;
		tmp++;
	}
	for (int i = left; i <= right; i++) {
		_pair_num1[i] = std::make_pair(_pair_num2[i].first, _pair_num2[i].second);
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
		if (_pair_num1[i].first <= _pair_num1[j].first) {
			_pair_num2[k] = std::make_pair(_pair_num1[i].first, _pair_num1[i].second);
			k++;
			i++;
		}
		else {
			_pair_num2[k] = std::make_pair(_pair_num1[j].first, _pair_num1[j].second);
			k++;
			j++;
		}
	}
	int tmp = i > mid ? j : i;
	while (k <= right) {
		_pair_num2[k] = std::make_pair(_pair_num1[tmp].first, _pair_num1[tmp].second);
		k++;
		tmp++;
	}
	for (int i = left; i <= right; i++) {
		_pair_num1[i] = std::make_pair(_pair_num2[i].first, _pair_num2[i].second);
	}
}

void	PmergemeV::sort() {
	std::vector<std::pair<int, int> >::iterator it = _pair_num1.begin();

	if (_pair_num1.size() == 0) {
		_before_sort.push_back(_lastnum);
		_after_sort.push_back(_lastnum);
		return ;
	}
	makeOrder();
	_after_sort.push_back(_pair_num1[0].second);
	while (it != _pair_num1.end()) {
		_after_sort.push_back(it->first);
		it++;
	}

	std::vector<int>::iterator order_iter = _order.begin();
	while (order_iter != _order.end()) {
		int n = this->BinarySearch(_pair_num1[*order_iter].second);
		_after_sort.insert(_after_sort.begin() + n, (_pair_num1[*order_iter].second));
		order_iter++;
	}
	if (this->_odd == true) {
		int n = this->BinarySearch(this->_lastnum);
		_after_sort.insert(_after_sort.begin() + n, this->_lastnum);
	}
}

void	PmergemeDe::sort() {
	std::deque<std::pair<int, int> >::iterator it = _pair_num1.begin();

	if (_pair_num1.size() == 0) {
		_before_sort.push_back(_lastnum);
		_after_sort.push_back(_lastnum);
		return ;
	}
	makeOrder();
	_after_sort.push_back(_pair_num1[0].second);
	while (it != _pair_num1.end()) {
		_after_sort.push_back(it->first);
		it++;
	}

	std::deque<int>::iterator order_iter = _order.begin();
	while (order_iter != _order.end()) {
		int n = this->BinarySearch(_pair_num1[*order_iter].second);
		_after_sort.insert(_after_sort.begin() + n, (_pair_num1[*order_iter].second));
		order_iter++;
	}
	if (this->_odd == true) {
		int n = this->BinarySearch(this->_lastnum);
		_after_sort.insert(_after_sort.begin() + n, this->_lastnum);
	}
}

void	PmergemeV::makeOrder() {
	int n = 3;
	int start = 3;
	int end = 1;

	while (makeJacobnum(n) <= static_cast<int>(this->_pair_num1.size())) {
		while (end != start) {
			_order.push_back(start - 1);
			start--;
		}
		end = makeJacobnum(n);
		n++;
		start = makeJacobnum(n);
	}
	if (start != static_cast<int>(this->_pair_num1.size()) && this->_pair_num1.size() != 0) {

		start = this->_pair_num1.size();
		while (end != start) {
			_order.push_back(start - 1);
			start--;
		}
	}
}

void	PmergemeDe::makeOrder() {
	int n = 3;
	int start = 3;
	int end = 1;


	while (makeJacobnum(n) <= static_cast<int>(this->_pair_num1.size()) && this->_pair_num1.size() != 0) {
		while (end != start) {
			_order.push_back(start - 1);
			start--;
		}
		end = makeJacobnum(n);
		n++;
		start = makeJacobnum(n);
	}
	if (start != static_cast<int>(this->_pair_num1.size())) {
		start = this->_pair_num1.size();
		while (end != start) {
			_order.push_back(start - 1);
			start--;
		}
	}
}

int PmergemeV::BinarySearch(int target) {
    int low = 0;
    int high = _after_sort.size() - 1;
    int mid;

    while(low <= high) {
        mid = (low + high) / 2;

        if (_after_sort[mid] == target)
            return mid;
        else if (_after_sort[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (target > _after_sort[mid])
		return mid + 1;
	else
		return mid;
}

int PmergemeDe::BinarySearch(int target) {
    int low = 0;
    int high = _after_sort.size() - 1;
    int mid;

    while(low <= high) {
        mid = (low + high) / 2;

        if (_after_sort[mid] == target)
            return mid;
        else if (_after_sort[mid] > target)
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (target > _after_sort[mid])
		return mid + 1;
	else
		return mid;
}

void	PmergemeV::printBefore() {
	std::vector<int>::iterator it = _before_sort.begin();
	std::cout << "Before: ";
	while (it != _before_sort.end()) {
		std::cout << *it;
		it++;
		if (it != _before_sort.end())
			std::cout << " ";
		else
			std::cout << "\n";
	}
}

void	PmergemeV::printAfter() {
	std::vector<int>::iterator it = _after_sort.begin();
	std::cout << "After:  ";
	while (it != _after_sort.end()) {
		std::cout << *it;
		it++;
		if (it != _after_sort.end())
			std::cout << " ";
		else
			std::cout << "\n";
	}

}
