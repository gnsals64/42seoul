#include "../../inc/BlockParser.hpp"

ConfigParser::TokenType	ConfigParser::setErrorbit(int errorcode) {
	error_bit_ = errorcode;
	error_line_ = line_num_;
	return (TOKEN_TYPE_ERROR);
}

bool	ConfigParser::IsCharTrue(char c) {
	return (c == '\n' || c == ' ' || c == '\t' || c == '\r' ||
		c == '{' || c == '}' || c == ';' || c == EOF);
}

void	ConfigParser::InitParserClass(void) {
	memset(&check_, 0, sizeof(t_check));
	line_num_ = 0;
	error_bit_ = 0;
	error_line_ = 0;
}

int		ConfigParser::get_errorbit(void) {
	return error_bit_;
}

int		ConfigParser::get_errorline(void) {
	return error_line_;
}

std::vector<std::string> ConfigParser::get_directives(void) {
	return save_line_;
}

std::vector<std::vector<std::string> > ConfigParser::getServer(void) {
	return server_;
}
std::vector<std::string> ConfigParser::get_server_i(int i) {
	return server_[i];
}
