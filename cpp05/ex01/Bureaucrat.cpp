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

void	Bureaucrat::signForm(Form &form) {
	if (form.getIsSigned() == true)
		std::cout << this->getName() << " signed " << form.getName() << std::endl;
	else if (this->getGrade() <= form.getGradeToSign())
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because grade too row" << std::endl;
	else
		std::cout << this->getName() << " couldn't sign " << form.getName() << " because The besigned function was not executed." << std::endl;
} 

const char *Bureaucrat::GradeTooHighException::what() const throw() {
	return "Bureaucrat's grade too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
	return "Bureaucrat's grade too row";
}

std::ostream& operator<<(std::ostream &out, const Bureaucrat &ref) {
	out << ref.getName() << ", bureaucrat grade " << ref.getGrade() << std::endl;
	return out;
}