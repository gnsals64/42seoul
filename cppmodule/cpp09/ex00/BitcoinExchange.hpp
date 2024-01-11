#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <fstream>

class btc {
private:
	std::map<std::string, float> db;
	
public:
	btc();
	~btc();
	btc(const btc &cpy);
	btc& operator=(const btc &cpy);
	void	db_init();

};

#endif