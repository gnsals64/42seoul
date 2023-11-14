#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "AForm.hpp"

class Bureaucrat;

class Shrubberycreationform : public Form {
	private:

	public:
		Shrubberycreationform();
		~Shrubberycreationform();
		Shrubberycreationform(std::string name, int grade_to_sign, int grade_to_execute);
		Shrubberycreationform(const Shrubberycreationform &cpy);
		Shrubberycreationform& operator=(const Shrubberycreationform &cpy);
		void execute(Bureaucrat const &executor) const;
};

#endif
