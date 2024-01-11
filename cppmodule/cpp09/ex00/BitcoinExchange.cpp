#include "BitcoinExchange.hpp"

btc::btc() {}

btc::~btc() {}

btc::btc(const btc &cpy) {}

btc& btc::operator=(const btc &cpy) {}

void	btc::db_init() {
	std::ifstream db;
	db.open("data.csv");

	if (db.is_open()) {
		while (!db.eof()) {
			std::string str;
			getline(db, str);
			
		}
	}
	else
		throw std::runtime_error("There is no database");
	

}

