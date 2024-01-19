#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>
# include <sstream>

enum state{
	NORMAL,
	NOT_POSITIVE,
	BAD_INPUT,
	LARGE_NUM,
	FORMAT_ERROR,
};

class btc {
private:
	std::map<std::string, float> _db;
	
public:
	btc();
	~btc();
	btc(const btc &cpy);
	btc& operator=(const btc &cpy);
	void	db_init();
	void	input_check(std::string input);
	void	output(std::string date, std::string num);
};

void	dataCheck(std::string date, std::string price);
state	inputDataCheck(std::string date, std::string price);

#endif