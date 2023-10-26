#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <cstring>

class Bureaucrat {
	private:
		const std::string	name_;
		int					grade_;
	
	public:
		Bureaucrat();
		~Bureaucrat();
		Bureaucrat(const std::string name, int grade);
		std::string	getName(void) const;
		int			getGrade(void) const;
		void		CheckArgument(void);
		void		IncreasingGrade(void);
		void		DecreasingGrade(void);

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