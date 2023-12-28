#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "AForm.hpp"

class Bureaucrat;

class Shrubberycreationform : public Form {
	private:

	public:
		Shrubberycreationform();
		~Shrubberycreationform();
		Shrubberycreationform(std::string name);
		Shrubberycreationform(const Shrubberycreationform &cpy);
		Shrubberycreationform& operator=(const Shrubberycreationform &cpy);
		void execute(Bureaucrat const &executor) const;
};

#endif
