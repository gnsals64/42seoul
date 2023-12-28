#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : Form("presidential", 25, 5) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm::PresidentialPardonForm(std::string name) : Form(name, 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& cpy) : Form(cpy.getName(), cpy.getGradeToSign(), cpy.getGradeToExecute()) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& cpy) {
	if (this == &cpy)
		return *this;
	this->setIsSigned(cpy.getIsSigned());
	return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	if (this->getIsSigned() == false) {
		std::cout << this->getName();
		throw PresidentialPardonForm::NotSigned();
	}
	if (executor.getGrade() <= this->getGradeToExecute()) {
		std::cout << executor.getName() << " has been pardoned" << std::endl;
	}
	else {
		std::cout << this->getName();
		throw PresidentialPardonForm::NotEnoughGrade();
	}
}