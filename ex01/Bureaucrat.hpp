#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <cstring>
# include "Form.hpp"

class Form;

class Bureaucrat {
	private:
		const std::string	name_;
		int					grade_;
	
	public:
		Bureaucrat();
		~Bureaucrat();
		Bureaucrat(const std::string name, int grade);
		Bureaucrat(const Bureaucrat &cpy);
		Bureaucrat& operator=(const Bureaucrat &cpy);
		std::string	getName(void) const;
		int			getGrade(void) const;
		void		CheckArgument(void);
		void		IncreasingGrade(void);
		void		DecreasingGrade(void);
		void		signForm(Form &form);

		class GradeTooHighException : public std::exception {
			public:
			    const char * what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
			    const char * what() const throw();
		};
};

std::ostream& operator<<(std::ostream &os, const Bureaucrat &ref);


#endif