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
				throw std::runtime_error("The format of the database was not followed1");
		}
		while (!db.eof()) {
			std::string str;
			getline(db, str);
			if (str == "")
				continue ;
			if (str.find(',') == std::string::npos) {
				throw std::runtime_error("The format of the database was not followed2");
			}
			std::string date = str.substr(0, str.find(','));
			std::string price = str.substr(str.find(',') + 1);
			dataCheck(date, price);
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
		if (i == 7) {
			if (isdigit(date[7]) == false || isdigit(date[8]) == false)
				throw std::runtime_error("The format of the database was not followed");
			std::string tmp = date.substr(7, 2);
			if (atoi(tmp.c_str()) > 31 && atoi(tmp.c_str()) < 1)
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
