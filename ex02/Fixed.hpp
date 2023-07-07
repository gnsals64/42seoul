#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed{
	private:
		int					value;
		const static int	bits = 8;
	public:
		Fixed();
		Fixed(const int i);
		Fixed(const float f);
		~Fixed();
		Fixed(const Fixed& obj);
		Fixed&	operator=(const Fixed& obj);
		float	toFloat(void) const;
		int		toInt(void) const;
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		bool	operator>(const Fixed& obj);
		bool	operator<(const Fixed& obj);
		bool	operator<=(const Fixed& obj);
		bool	operator>=(const Fixed& obj);
		bool	operator==(const Fixed& obj);
		bool	operator!=(const Fixed& obj);
		Fixed	operator+(const Fixed& obj);
		Fixed	operator-(const Fixed& obj);
		Fixed	operator*(const Fixed& obj);
		Fixed	operator/(const Fixed& obj);
		Fixed&	operator++();
		Fixed	operator++(int a);
		Fixed	max(Fixed &a, Fixed &b);
		Fixed	max(const Fixed &a, const Fixed &b);
		Fixed	min(Fixed &a, Fixed &b);
		Fixed	min(const Fixed &a, const Fixed &b);
};

std::ostream& operator<<(std::ostream& out, const Fixed& obj);
#endif
