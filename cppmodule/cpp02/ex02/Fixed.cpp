#include "Fixed.hpp"

Fixed::Fixed(){
	this->value = 0;
}

Fixed::Fixed(const int i){
	this->value = i << this->bits;
}

Fixed::Fixed(const float f){
	this->value = roundf(f * 256);
}

Fixed::~Fixed(){
}

Fixed::Fixed(const Fixed& obj){
	this->value = obj.getRawBits();
}

Fixed& Fixed::operator=(const Fixed& obj){
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

bool	Fixed::operator>(const Fixed& obj){
	if (this->toFloat() > obj.toFloat())
		return true;
	return false;
}

bool	Fixed::operator<(const Fixed& obj){
	if (this->toFloat() < obj.toFloat())
		return true;
	return false;
}
bool	Fixed::operator>=(const Fixed& obj){
	if (this->toFloat() >= obj.toFloat())
		return true;
	return false;
}

bool	Fixed::operator<=(const Fixed& obj){
	if (this->toFloat() <= obj.toFloat())
		return true;
	return false;
}

bool	Fixed::operator==(const Fixed& obj){
	if (this->toFloat() == obj.toFloat())
		return true;
	return false;
}

bool	Fixed::operator!=(const Fixed& obj){
	if (this->toFloat() != obj.toFloat())
		return true;
	return false;
}

Fixed	Fixed::operator+(const Fixed& obj){
	Fixed	tmp((this->toFloat() + obj.toFloat()));
	return tmp;
}

Fixed	Fixed::operator-(const Fixed& obj){
	Fixed	tmp((this->toFloat() - obj.toFloat()));
	return tmp;
}

Fixed	Fixed::operator*(const Fixed& obj){
	Fixed	tmp((this->toFloat() * obj.toFloat()));
	return tmp;
}

Fixed	Fixed::operator/(const Fixed& obj){
	Fixed	tmp((this->toFloat() / obj.toFloat()));
	return tmp;
}

Fixed&	Fixed::operator++(){
	value++;
	return *this;
}

Fixed	Fixed::operator++(int a){
	Fixed	tmp(this->toFloat());

	(void)a;
	this->value++;
	return (tmp);
}

Fixed	Fixed::max(Fixed &a, Fixed &b){
	if (a >= b)
		return a;
	return b;
}

Fixed	Fixed::max(const Fixed &a, const Fixed &b){
	if (a.value >= b.value)
		return a;
	return b;
}

Fixed	Fixed::min(Fixed &a, Fixed &b){
	if (a <= b)
		return a;
	return b;
}

Fixed	Fixed::min(const Fixed &a, const Fixed &b){
	if (a.value <= b.value)
		return a;
	return b;
}
