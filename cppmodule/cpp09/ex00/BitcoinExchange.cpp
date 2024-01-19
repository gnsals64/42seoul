#include "BitcoinExchange.hpp"

btc::btc() {}

btc::~btc() {}

btc::btc(const btc &cpy) {
	(void)cpy;
}

btc& btc::operator=(const btc &cpy) {
	(void)cpy;
	return *this;
}

void	btc::db_init() {
	std::ifstream db;

	db.open("data.csv");

	if (db.is_open()) {
		if (!db.eof()) {
			std::string str;
			getline(db, str);
			if (str != "date,exchange_rate")
				throw std::runtime_error("The format of the database was not followed");
		}
		while (!db.eof()) {
			std::string str;
			getline(db, str);
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
			this->_db.insert(std::pair<std::string, float>(date, tmp));
		}
	}
	else
		throw std::runtime_error("There is no database");
}

void	dataCheck(std::string date, std::string price) {
	if (date.size() != 10)
		throw std::runtime_error("The format of the database was not followed");
	for (size_t i = 0; i < date.size(); i++){
		if (i >= 0 && i <= 3) {
			if (isdigit(date[i]) == false)
				throw std::runtime_error("The format of the database was not followed");
			continue ;
		}
		if (i == 4 || i == 7) {
			if (date[i] != '-')
				throw std::runtime_error("The format of the database was not followed");
			continue ;
		}
		if (i == 5) {
			if (isdigit(date[5]) == false || isdigit(date[6]) == false)
				throw std::runtime_error("The format of the database was not followed");
			std::string tmp = date.substr(5, 2);
			if (atoi(tmp.c_str()) > 12 && atoi(tmp.c_str()) < 1)
				throw std::runtime_error("The format of the database was not followed");
			i++;
			continue ;
		}
		if (i == 8) {
			if (isdigit(date[8]) == false || isdigit(date[9]) == false)
				throw std::runtime_error("The format of the database was not followed");
			std::string tmp = date.substr(8, 2);
			std::string mon = date.substr(5, 2);
			if (atoi(mon.c_str()) == 2) {
				if (atoi(tmp.c_str()) > 28 || atoi(tmp.c_str()) < 1)
					throw std::runtime_error("The format of the database was not followed");
			}
			else if (atoi(tmp.c_str()) > 31 || atoi(tmp.c_str()) < 1)
				throw std::runtime_error("The format of the database was not followed");
			continue ;
		}
	}
	int dot = 0;
	for (size_t i = 0; i < price.size(); i++) {
		if (price[i] == '.') {
			dot++;
			continue ;
		}
		if (dot > 1 || isdigit(price[i]) == false)
			throw std::runtime_error("The format of the database was not followed");
	}
} 

void btc::input_check(std::string input) {
	std::ifstream output;

	output.open(input);

	if (output.is_open()) {
		if (!output.eof()) {
			std::string str;
			getline(output, str);
			if (str != "date | value")
				throw std::runtime_error("The format of the database was not followed");
		}
		while (!output.eof()) {
			std::string str;
			getline(output, str);
			if (str == "")
				continue ;
			if (str.find('|') == std::string::npos) {
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
				default:
					btc::output(date, num);
					break ;
			}
		}
	}
	else
		throw std::runtime_error("not exist input file");
}

state	inputDataCheck(std::string date, std::string price) {
	if (date.size() != 10)
		return BAD_INPUT;
	for (size_t i = 0; i < date.size(); i++){
		if (i >= 0 && i <= 3) {
			if (isdigit(date[i]) == false)
				return BAD_INPUT;
			continue ;
		}
		if (i == 4 || i == 7) {
			if (date[i] != '-')
				return BAD_INPUT;
			continue ;
		}
		if (i == 5) {
			if (isdigit(date[5]) == false || isdigit(date[6]) == false)
				return BAD_INPUT;
			std::string tmp = date.substr(5, 2);
			if (atoi(tmp.c_str()) > 12 && atoi(tmp.c_str()) < 1)
				return BAD_INPUT;
			i++;
			continue ;
		}
		if (i == 8) {
			if (isdigit(date[8]) == false || isdigit(date[9]) == false)
				return BAD_INPUT;
			std::string tmp = date.substr(8, 2);
			std::string mon = date.substr(5, 2);
			if (atoi(mon.c_str()) == 2) {
				if (atoi(tmp.c_str()) > 28 || atoi(tmp.c_str()) < 1)
					return BAD_INPUT;
			}
			else if (atoi(tmp.c_str()) > 31 || atoi(tmp.c_str()) < 1)
				return BAD_INPUT;
			continue ;
		}
	}
	int dot = 0;
	for (size_t i = 0; i < price.size(); i++) {
		if (price[0] == '-')
			return NOT_POSITIVE;
		if (price[i] == '.') {
			dot++;
			continue ;
		}
		if (dot > 1 || isdigit(price[i]) == false)
			return FORMAT_ERROR;
	}
	std::stringstream ss(price);
	double ld;
	ss >> ld;
	if (ld > 2147483647)
		return LARGE_NUM;
	return NORMAL;
}

void	btc::output(std::string date, std::string num) {
	std::map<std::string, float>::iterator it = _db.find(date);
	bool finish = true;
	if (it == _db.end()) {
		while (finish) {
			while (date[9] >= '0') {
				date[9] = date[9] - 1;
				it = _db.find(date);
				if (it != _db.end()) {
					std::stringstream ss(num);
					float f;
					ss >> f;
					std::cout << date << " => " << num << " = " << _db[date] * f << std::endl;
					finish = false;
					break ;
				}
			}
			if (date[8] >= '0') {
				date[8] = date[8] - 1;
				date[9] = '9';
			}
			if (date[8] == '0' && date[9] == '0' && finish == true)
				finish = false;
		}
	}
	else {
		std::stringstream ss(num);
		float f;
		ss >> f;
		std::cout << date << " => " << num << " = " << _db[date] * f << std::endl;
	}
}