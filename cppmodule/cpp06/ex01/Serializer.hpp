#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <iostream>

typedef struct s_data {
	int a;
	int b;
} Data;

class Serializer {
	private:

	public:
		Serializer();
		~Serializer();
		Serializer(const Serializer& cpy);
		Serializer& operator=(const Serializer& cpy);
		uintptr_t	serialize(Data* ptr);
		Data*		deserialize(uintptr_t raw);
};

#endif