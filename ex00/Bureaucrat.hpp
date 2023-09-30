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
		std::string	getName(void);
		int			getGrade(void);
		void		CheckArgument(void);
		void		GradeTooHighException(void);
		void		GradeTooLowException(void);
		void		IncreasingGrade(void);
		void		DecreasingGrade(void);
};



#endif