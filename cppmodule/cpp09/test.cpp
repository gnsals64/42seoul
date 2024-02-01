#include <iostream>
#include <fstream>
#include <vector>

int main() {
	std::vector<int> _v;
	std::vector<int>::iterator it = _v.begin();

	_v.push_back(1);
	_v.push_back(2);
	_v.push_back(3);
	_v.push_back(4);
	_v.push_back(5);
	_v.push_back(6);
	_v.push_back(7);
	_v.push_back(8);
	_v.push_back(9);
	_v.erase(_v.begin() + 2);

	for (int i = 0; i < _v.size(); i++) printf("%d ", _v[i]);
}