#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <sstream>

enum PseudoLiterals {
	PARAM_MINUS_INF,
	PARAM_INF,
	PARAM_NAN
};

class ScalarConverter {
	private:
		std::string flag_;
		double		num_;
		int			numcnt_;

	public:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& cpy);
		ScalarConverter& operator=(const ScalarConverter& cpy);
		std::string getFlag();
		double		getNum();
		int			getNumcnt();
		void		setFlag(std::string flag);
		void		setNum(double num);
		void		setNumcnt(int num_cnt);

		void		printChar();
		void		printInt();
		void		printFloat(std::string param);
		void		printDouble(std::string param);
		void		convert(std::string param);
};

#endif