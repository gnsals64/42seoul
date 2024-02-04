#ifndef BITCOINEXCHANGE_HPPBtc
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <ctime>
# include <cstring>

enum state{
	NORMAL,
	NOT_POSITIVE,
	BAD_INPUT,
	LARGE_NUM,
	FORMAT_ERROR,
};

class Btc {
private:
	std::map<std::string, float> _db;

public:
	Btc();
	~Btc();
	Btc(const Btc &cpy);
	Btc& operator=(const Btc &cpy);
	void	db_init();
	void	input_check(std::string input);
	void	output(std::string date, std::string num);
};

void	dataCheck(std::string date, std::string price);
state	inputDataCheck(std::string date, std::string price);

#endif
