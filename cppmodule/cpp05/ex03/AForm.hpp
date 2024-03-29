#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
	private:
		const std::string	name_;
		const int			grade_to_sign_;
		const int			grade_to_execute_;
		bool				is_signed_;
	
	public:
		Form();
		virtual ~Form();
		Form(std::string name, int grade_to_sign, int grade_to_execute);
		Form(const Form &cpy);
		Form& operator=(const Form &cpy);

		virtual void execute(Bureaucrat const &executor) const = 0;
		std::string	getName() const;
		bool		getIsSigned() const;
		int			getGradeToSign() const;
		int			getGradeToExecute() const;
		void		setIsSigned(bool is_signed);
		void		beSigned(Bureaucrat& bureaucrat);

		class NotSigned : public std::exception {
			public:
			    const char * what() const throw();
		};
		class NotEnoughGrade : public std::exception {
			public:
			    const char * what() const throw();
		};
};

#endif