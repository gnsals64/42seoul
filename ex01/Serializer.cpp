#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::~Serializer() {}

Serializer::Serializer(const Serializer& cpy) {
	(void)cpy;
}

Serializer& Serializer::operator=(const Serializer& cpy) {
	(void)cpy;
	return *this;
}

uintptr_t Serializer::serialize(Data* ptr) {
	return static_cast<uintptr_t>(ptr);
}