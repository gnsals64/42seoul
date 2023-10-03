#ifndef BLOCKPARSER_HPP
# define BLOCKPARSER_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <cstring>

class ConfigParser {
	private:
		int		line_num_;
		int		error_bit_;
		int		error_line_;

		enum TokenType {
			TOKEN_TYPE_DEFAULT = 0,
			TOKEN_TYPE_NORMAL = 1,
			TOKEN_TYPE_START_BLOCK = 2,
			TOKEN_TYPE_END_BLOCK = 3,
			TOKEN_TYPE_NEWLINE = 4,
			TOKEN_TYPE_COMMENT = 5,
			TOKEN_TYPE_SEMICOLON = 6,
			TOKEN_TYPE_EOF = 7,
			TOKEN_TYPE_ERROR = 8
		};

		typedef struct s_check {
			bool	http_;
			bool	server_;
			bool	location_;
            bool    location_method_;

		}	t_check;

		t_check		check_;

		bool		IsCharTrue(char c);
		TokenType	Tokenization(std::istream *file, std::string *token);
		TokenType	setErrorbit(int errorcode);
		int			BlockTokenCheck(std::string token);
		void		PushBackLine(std::string token, std::string *line);

	public:
     	std::vector<std::string>				save_line_;
   		std::vector<std::string>				v_server_;
    	std::vector<std::vector<std::string> >	server_;
		void		StartParsing(std::istream *file);
		void		InitParserClass(void);
		int			get_errorbit(void);
		int			get_errorline(void);
		int			PrintParseError(std::string filename);
		std::vector<std::string>	get_directives(void);
		std::vector<std::string>	get_server_i(int i);
		std::vector<std::vector<std::string> >	getServer(void);
};

int		CheckExtension(std::string filename);
int		CheckBlock(std::string filename, ConfigParser *parser);

#endif
