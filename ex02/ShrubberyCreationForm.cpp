#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

Shrubberycreationform::Shrubberycreationform() : Form("Shrubbery", 145, 137) {}

Shrubberycreationform::~Shrubberycreationform() {}

Shrubberycreationform::Shrubberycreationform(std::string name) : Form(name, 145, 137) {}

Shrubberycreationform::Shrubberycreationform(const Shrubberycreationform &cpy) : Form(cpy.getName(), cpy.getGradeToSign(), cpy.getGradeToExecute()) {}

Shrubberycreationform& Shrubberycreationform::operator=(const Shrubberycreationform &cpy) {
	if (this == &cpy)
		return *this;
	this->setIsSigned(cpy.getIsSigned());
	return *this;
}

void	Shrubberycreationform::execute(Bureaucrat const &executor) const {
	if (this->getIsSigned() == false) {
		std::cout << this->getName();
		throw Shrubberycreationform::NotSigned();
	}
	if (executor.getGrade() <= this->getGradeToExecute()) {
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
	else {
		std::cout << this->getName();
		throw Shrubberycreationform::NotEnoughGrade();
	}
}