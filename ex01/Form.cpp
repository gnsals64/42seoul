#include "Form.hpp"

Form::Form() : name_("default"), grade_to_sign_(0), grade_to_execute_(0), is_signed_(false) {}

Form::~Form() {}

Form::Form(std::string name, int grade_to_sign, int grade_to_execute) : name_(name), grade_to_sign_(grade_to_sign), grade_to_execute_(grade_to_execute), is_signed_(false) {
	if (this->grade_to_sign_ < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade_to_sign_ > 150)
		throw Bureaucrat::GradeTooLowException();
	if (this->grade_to_execute_ < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade_to_execute_ > 150)
		throw Bureaucrat::GradeTooLowException();
}

Form::Form(const Form &cpy) : name_(cpy.getName()),  grade_to_sign_(cpy.getGradeToSign()), grade_to_execute_(cpy.getGradeToExecute()), is_signed_(cpy.getIsSigned()){}

Form& Form::operator=(const Form &cpy) {
	if (this == &cpy)
		return *this;
	this->is_signed_ = cpy.is_signed_;
	return *this;
}

int	Form::getGradeToExecute() const {
	return this->grade_to_execute_;
}

int Form::getGradeToSign() const {
	return this->grade_to_sign_;
}

bool	Form::getIsSigned() const {
	return this->is_signed_;
}

std::string Form::getName() const {
	return this->name_;
}

void	Form::beSigned(Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() <= this->getGradeToSign())
		this->is_signed_ = true;
}