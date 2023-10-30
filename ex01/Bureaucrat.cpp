#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name_("default"), grade_(0) {}
Bureaucrat::~Bureaucrat() {}
Bureaucrat::Bureaucrat(const std::string name, int grade): name_(name), grade_(grade) {
	if (this->grade_ < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade_ > 150)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat &cpy) : name_(cpy.getName()) {
	grade_ = cpy.getGrade();
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &cpy) {
	if (this == &cpy)
		return *this;
	grade_ = cpy.getGrade();
	return *this;
}

std::string Bureaucrat::getName() const{
	return this->name_;
}

int Bureaucrat::getGrade() const{
	return this->grade_;
}

void	Bureaucrat::CheckArgument() {
	if (this->grade_ < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade_ > 150)
		throw Bureaucrat::GradeTooLowException();
}

void	Bureaucrat::IncreasingGrade() {
	this->grade_--;
}

void	Bureaucrat::DecreasingGrade() {
	this->grade_++;
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade too row";
}

std::ostream& operator<<(std::ostream &out, const Bureaucrat &ref) {
	out << ref.getName() << ", bureaucrat grade " << ref.getGrade() << std::endl;
	return out;
}