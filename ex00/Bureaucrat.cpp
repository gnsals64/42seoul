#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name_("default"), grade_(0) {}
Bureaucrat::~Bureaucrat() {}
Bureaucrat::Bureaucrat(const std::string name, int grade): name_(name), grade_(grade) {
	if (this->grade_ < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade_ > 150)
		throw Bureaucrat::GradeTooLowException();
}

std::string Bureaucrat::getName() {
	return this->name_;
}

int Bureaucrat::getGrade() {
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