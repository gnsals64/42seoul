#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <Bureaucrat.hpp>

class Bureaucrat;

class Form {
	private:
		const std::string	name_;
		bool				is_signed_;
		const int			grade_to_sign_;
		const int			grade_to_execute_;
	
	public:
		Form();
		~Form();
		Form(std::string name, int grade_to_sign, int grade_to_execute);
		Form(const Form &cpy);
		Form& operator=(const Form &cpy);

		std::string	getName() const;
		bool		getIsSigned() const;
		int			getGradeToSign() const;
		int			getGradeToExecute() const;		
		void		beSigned(Bureaucrat& bureaucrat);
		
		class GradeTooHighException : public std::exception {
			public:
			    const char * what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
			    const char * what() const throw();
		};


};

#endif