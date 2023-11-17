#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

Shrubberycreationform::Shrubberycreationform() : Form() {}

Shrubberycreationform::~Shrubberycreationform() {}

Shrubberycreationform::Shrubberycreationform(std::string name, int grade_to_sign, int grade_to_execute) : Form(name, grade_to_sign, grade_to_execute) {}

Shrubberycreationform::Shrubberycreationform(const Shrubberycreationform &cpy) : Form(cpy.getName(), cpy.getGradeToSign(), cpy.getGradeToExecute()) {}

Shrubberycreationform& Shrubberycreationform::operator=(const Shrubberycreationform &cpy) {
	if (this == &cpy)
		return *this;
	this->setIsSigned(cpy.getIsSigned());
	return *this;
}

void	Shrubberycreationform::execute(Bureaucrat const &executor) const {
	if (this->getIsSigned() == false)
		throw Shrubberycreationform::NotSigned();
	if (this->getGradeToExecute() <= 137 && this->getGradeToSign() <= 145) {
		std::string filename = executor.getName() + "_shrubbery";
		std::ofstream file(filename);
		if (file.is_open()) {
			file << "       _-_\n";
			file << "    /~~   ~~\\\n";
			file << " /~~         ~~\\\n";
			file << "{               }\n";
			file << " \\  _-     -_  /\n";
			file << "   ~  \\\\ //  ~\n";
			file << "   ~  \\\\ //  ~\n";
			file << "  _ -  | |   -_\n";
			file << "      // \\\\\n";
			file.close();
		}
	}
	else
		throw Shrubberycreationform::NotEnoughGrade();
}