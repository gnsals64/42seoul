#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : Form() {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm::RobotomyRequestForm(std::string name, int grade_to_sign, int grade_to_execute) : Form(name, grade_to_sign, grade_to_execute) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& cpy) : Form(cpy.getName(), cpy.getGradeToSign(), cpy.getGradeToExecute()) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& cpy) {
	if (this == &cpy)
		return *this;
	this->setIsSigned(cpy.getIsSigned());
	return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	if (this->getIsSigned() == false)
		throw RobotomyRequestForm::NotSigned();
	if (this->getGradeToExecute() <= 45 && this->getGradeToSign() <= 72) {
		std::srand(time(NULL));
		int num = rand() % 10;
		
		if (num < 5)
			std::cout << executor.getName() << " has been robotomized" << std::endl;
		else
			std::cout << "robotomy failed." << std::endl;
	}
	else
		throw RobotomyRequestForm::NotEnoughGrade();
}
