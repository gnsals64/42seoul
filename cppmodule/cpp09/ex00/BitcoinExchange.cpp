#include "BitcoinExchange.hpp"

Btc::Btc() {}

Btc::~Btc() {}

Btc::Btc(const Btc &cpy) {
	this->_db = cpy._db;
}

Btc& Btc::operator=(const Btc &cpy) {
	if (this == &cpy)
		return *this;
	this->_db = cpy._db;
	return *this;
}

void	Btc::db_init() {
	std::ifstream db;

	db.open("data.csv");

	if (db.is_open()) {
		if (!db.eof()) {
			std::string str;
			std::getline(db, str);
			if (str != "date,exchange_rate")
				throw std::runtime_error("The format of the database was not followed");
		}
		while (!db.eof()) {
			std::string str;
			std::getline(db, str);
			if (str == "")
				continue ;
			if (str.find(',') == std::string::npos) {
				throw std::runtime_error("The format of the database was not followed");
			}
			std::string date = str.substr(0, str.find(','));
			std::string price = str.substr(str.find(',') + 1);
			dataCheck(date, price);
			std::stringstream ss(price);
			float tmp;
			ss >> tmp;
			this->_db[date] = tmp;
		}
	}
	else
		throw std::runtime_error("There is no database");
}

void	dataCheck(std::string date, std::string price) {
	std::tm tm;

	std::memset(&tm, 0, sizeof(std::tm));
	if (date.size() != 10)
		throw std::runtime_error("The format of the database was not followed");
	for (size_t i = 0; i < date.size(); i++){
		if (i <= 3 || (i >= 5 && i <= 6) || (i >= 8 && i <= 9)) {
			if (std::isdigit(date[i]) == false)
				throw std::runtime_error("The format of the database was not followed");
			continue ;
		}
		if (i == 4 || i == 7) {
			if (date[i] != '-')
				throw std::runtime_error("The format of the database was not followed");
			continue ;
		}
	}
	tm.tm_year = std::atoi(date.substr(0, 4).c_str()) - 1900;
	tm.tm_mon = std::atoi(date.substr(5, 2).c_str()) - 1;
	tm.tm_mday = std::atoi(date.substr(8, 2).c_str());

	int year_tmp = tm.tm_year;
	int mon_tmp = tm.tm_mon;
	int day_tmp = tm.tm_mday;

	std::mktime(&tm);

	if (tm.tm_year != year_tmp || tm.tm_mon != mon_tmp || tm.tm_mday != day_tmp)
		throw std::runtime_error("The format of the database was not followed");

	int dot = 0;
	for (size_t i = 0; i < price.size(); i++) {
		if (price[i] == '.') {
			dot++;
			continue ;
		}
		if (dot > 1 || std::isdigit(price[i]) == false)
			throw std::runtime_error("The format of the database was not followed");
	}
}

void Btc::input_check(std::string input) {
	std::ifstream output;

	output.open(input.c_str());

	if (output.is_open()) {
		if (!output.eof()) {
			std::string str;
			std::getline(output, str);
			if (str != "date | value")
				throw std::runtime_error("The format of the database was not followed");
		}
		while (!output.eof()) {
			std::string str;
			std::getline(output, str);
			if (str == "")
				continue ;
			if (str.find('|') == std::string::npos || str.find('|') == str.size() - 1 || str.find('|') + 1 == str.size()) {
				std::cerr << "Error: bad input => " << str << std::endl;
					continue ;
			}
			std::string date = str.substr(0, str.find('|') - 1);
			std::string num = str.substr(str.find('|') + 2);

			switch(inputDataCheck(date, num)) {
				case NOT_POSITIVE:
					std::cerr << "Error: not a positive number." << std::endl;
					break ;
				case BAD_INPUT:
					std::cerr << "Error: bad input => " << date << std::endl;
					break ;
				case LARGE_NUM:
					std::cerr << "Error: too large a number." << std::endl;
					break ;
				case FORMAT_ERROR:
					std::cerr << "Error: invalid format." << std::endl;
					break ;
				default:
					Btc::output(date, num);
					break ;
			}
		}
	}
	else
		throw std::runtime_error("not exist input file");
}

state	inputDataCheck(std::string date, std::string price) {
	std::tm tm;

	std::memset(&tm, 0, sizeof(std::tm));
	if (date.size() != 10)
		return BAD_INPUT;
	for (size_t i = 0; i < date.size(); i++) {
		if (i <= 3 || (i >= 5 && i <= 6) || (i >= 8 && i <= 9)) {
			if (std::isdigit(date[i]) == false)
				return BAD_INPUT;
			continue ;
		}
		if (i == 4 || i == 7) {
			if (date[i] != '-')
				return BAD_INPUT;
			continue ;
		}
	}

	tm.tm_year = std::atoi(date.substr(0, 4).c_str()) - 1900;
	tm.tm_mon = std::atoi(date.substr(5, 2).c_str()) - 1;
	tm.tm_mday = std::atoi(date.substr(8, 2).c_str());

	int year_tmp = tm.tm_year;
	int mon_tmp = tm.tm_mon;
	int day_tmp = tm.tm_mday;

	std::mktime(&tm);
	if (tm.tm_year != year_tmp || tm.tm_mon != mon_tmp || tm.tm_mday != day_tmp)
		return BAD_INPUT;

	int dot = 0;
	for (size_t i = 0; i < price.size(); i++) {
		if (price[0] == '-')
			return NOT_POSITIVE;
		if (price[i] == '.') {
			dot++;
			continue ;
		}
		if (dot > 1 || std::isdigit(price[i]) == false)
			return FORMAT_ERROR;
	}
	std::stringstream ss(price);
	double ld;
	ss >> ld;
	if (ld > 1000)
		return LARGE_NUM;
	return NORMAL;
}

void	Btc::output(std::string date, std::string num) {
	std::map<std::string, float>::iterator it = _db.find(date);

	if (it == _db.end()) {
		it = _db.lower_bound(date);
		if (it == _db.begin()) {
			std::cout << "Error : invalid date." << std::endl;
			return;
		}
		--it;
		std::stringstream ss(num);
		float f;
		ss >> f;
		std::cout << date << " => " << num << " = " << it->second * f << std::endl;
	}
	else {
		std::stringstream ss(num);
		float f;
		ss >> f;
		std::cout << date << " => " << num << " = " << _db[date] * f << std::endl;
	}
}
