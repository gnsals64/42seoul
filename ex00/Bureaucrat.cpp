#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name_("default"), grade_(0) {}
Bureaucrat::~Bureaucrat() {}
Bureaucrat::Bureaucrat(const std::string name, int grade): name_(name), grade_(grade) {}

std::string Bureaucrat::getName() {
	return this->name_;
}

int Bureaucrat::getGrade() {
	return this->grade_;
}

void	Bureaucrat::CheckArgument() {
	if (this->grade_ < 1)
		throw std::string("high");
	else if (this->grade_ > 150)
		throw std::string("low");
}

void	Bureaucrat::GradeTooHighException() {
	std::cerr << "Grade too high" << std::endl;
	exit(1);
}

void	Bureaucrat::GradeTooLowException() {
	std::cerr << "Grade too low" << std::endl;
	exit(1);
}

void	Bureaucrat::IncreasingGrade() {
	this->grade_--;
}

void	Bureaucrat::DecreasingGrade() {
	this->grade_++;
}