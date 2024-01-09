#include <stdio.h>
#include <unistd.h>
#include "ex00/ft_putchar.c"
#include "ex01/ft_print_alphabet.c"
#include "ex02/ft_print_reverse_alphabet.c"
#include "ex03/ft_print_numbers.c"
#include "ex04/ft_is_negative.c"
#include "ex05/ft_print_comb.c"
#include "ex07/ft_putnbr.c"

int main()
{
	// ex00
	printf("ex00\n");
	ft_putchar('a');
	printf("\n\n");

	//ex01
	printf("ex01\n");
	ft_print_alphabet();
	printf("\n\n");

	//ex02
	printf("ex02\n");
	ft_print_reverse_alphabet();
	printf("\n\n");

	//ex03
	printf("ex03\n");
	ft_print_numbers();
	printf("\n\n");

	//ex04
	printf("ex04\n");
	ft_is_negative(10);
	printf("\n");
	ft_is_negative(0);
	printf("\n");
	ft_is_negative(-14);
	printf("\n\n");

	//ex05
	printf("ex05\n");
	ft_print_comb();
	printf("\n\n");

	//ex07
	printf("ex07\n");
	ft_putnbr(-2147483648);
	printf("\n");
	ft_putnbr(2147483647);
	printf("\n");
	ft_putnbr(0);
	printf("\n");
	ft_putnbr(-124);
	printf("\n");
	ft_putnbr(2156);
	printf("\n");
}

