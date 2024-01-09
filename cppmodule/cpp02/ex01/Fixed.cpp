#include "Fixed.hpp"

Fixed::Fixed(){
	this->value = 0;
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int i){
	this->value = i << this->bits;
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float f){
	this->value = roundf(f * 256);
	std::cout << "Float constructor called" << std::endl;
}

Fixed::~Fixed(){
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed& obj){
	std::cout << "Copy constructor called" << std::endl;
	this->value = obj.getRawBits();
}

Fixed& Fixed::operator=(const Fixed& obj){
	std::cout << "Copy assignment operator called" << std::endl;
	if (this == &obj)
		return (*this);
	this->value = obj.getRawBits();
	return (*this);
}

int	Fixed::getRawBits(void) const{
	return (this->value);
}

void	Fixed::setRawBits(int const raw){
	this->value = raw;
}

std::ostream& operator<<(std::ostream& out, const Fixed & obj){
	out << obj.toFloat();
	return out;
}

float	Fixed::toFloat(void) const{
	return ((float)(this->value) / 256);
}

int		Fixed::toInt(void) const{
	return (this->value >> this->bits);
}
