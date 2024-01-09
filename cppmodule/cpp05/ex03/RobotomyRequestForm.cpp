#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : Form("robotomy", 72, 45) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm::RobotomyRequestForm(std::string name) : Form(name, 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& cpy) : Form(cpy.getName(), cpy.getGradeToSign(), cpy.getGradeToExecute()) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& cpy) {
	if (this == &cpy)
		return *this;
	this->setIsSigned(cpy.getIsSigned());
	return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	if (this->getIsSigned() == false) {
		std::cout << this->getName();
		throw RobotomyRequestForm::NotSigned();
	}
	if (executor.getGrade() <= this->getGradeToExecute()) {
		std::srand(time(NULL));
		int num = rand() % 10;
		
		if (num < 5)
			std::cout << executor.getName() << " has been robotomized" << std::endl;
		else
			std::cout << "robotomy failed." << std::endl;
	}
	else {
		std::cout << this->getName();
		throw RobotomyRequestForm::NotEnoughGrade();
	}
}
