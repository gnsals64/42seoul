#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : Form() {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm::PresidentialPardonForm(std::string name, int grade_to_sign, int grade_to_execute) : Form(name, grade_to_sign, grade_to_execute) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& cpy) : Form(cpy.getName(), cpy.getGradeToSign(), cpy.getGradeToExecute()) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& cpy) {
	if (this == &cpy)
		return *this;
	this->setIsSigned(cpy.getIsSigned());
	return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	if (this->getIsSigned() == false)
		throw PresidentialPardonForm::NotSigned();
	if (this->getGradeToExecute() <= 5 && this->getGradeToSign() <= 25) {
		std::cout << executor.getName() << " has been pardoned" << std::endl;
	}
	else 
		throw PresidentialPardonForm::NotEnoughGrade();
}